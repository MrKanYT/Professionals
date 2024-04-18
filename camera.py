import time
import urllib.request

import numpy as np
import cv2

import multiprocessing
from multiprocessing.shared_memory import SharedMemory
from multiprocessing import Value, Manager
import ctypes

import scanner


class WebCamera:

    low_quality_url: str
    medium_quality_url: str
    high_quality_url: str

    image_size: tuple[int, int, int]

    _child_process: multiprocessing.Process
    _shared_image_memory: SharedMemory
    _shared_image_data: np.ndarray
    _shared_hsv_memory: SharedMemory
    _shared_hsv_data: np.ndarray
    _shared_image_time: Value

    _shared_memory_manager: Manager
    _shared_is_releasing: Value

    def __init__(self,
                 low_qual_url: str,
                 med_qual__url: str,
                 high_qual_url: str):

        self.low_quality_url = low_qual_url
        self.medium_quality_url = med_qual__url
        self.high_quality_url = high_qual_url

        image = WebCamera.get_image(self.medium_quality_url)
        self.image_size = image.shape[1], image.shape[0], image.shape[2]

        self._shared_image_memory = SharedMemory("Image", create=True,
                                                 size=self.image_size[0] * self.image_size[1] * self.image_size[2] * 8)
        self._shared_hsv_memory = SharedMemory("HSV", create=True,
                                                 size=self.image_size[0] * self.image_size[1] * self.image_size[2] * 8)
        self._shared_image_data = np.ndarray(image.shape, dtype=np.uint8, buffer=self._shared_image_memory.buf)
        self._shared_hsv_data = np.ndarray(image.shape, dtype=np.uint8, buffer=self._shared_hsv_memory.buf)



        self._shared_memory_manager = Manager()
        self._shared_is_releasing = self._shared_memory_manager.Value(ctypes.c_bool, False)

        self._shared_grabber_x = self._shared_memory_manager.Value(ctypes.c_uint16, 0)
        self._shared_grabber_y = self._shared_memory_manager.Value(ctypes.c_uint16, 0)

        self._shared_object_x = self._shared_memory_manager.Value(ctypes.c_uint16, 0)
        self._shared_object_y = self._shared_memory_manager.Value(ctypes.c_uint16, 0)

        self._shared_text = self._shared_memory_manager.Value(ctypes.c_char_p, "")

        self._shared_image_time = self._shared_memory_manager.Value(ctypes.c_uint64, 0)

        self._child_process = multiprocessing.Process(target=WebCamera.screen_updater, args=(
            self.medium_quality_url,
            image.shape,
            self._shared_image_time,
            self._shared_is_releasing,
            self._shared_grabber_x,
            self._shared_grabber_y,
            self._shared_object_x,
            self._shared_object_y,
            self._shared_text
        ))
        self._child_process.start()

    @staticmethod
    def get_image(url: str) -> cv2.Mat:
        img_response = urllib.request.urlopen(url)
        imgnp = np.array(bytearray(img_response.read()), dtype=np.uint8)
        return cv2.imdecode(imgnp, -1)

    @staticmethod
    def screen_updater(imgae_url: str,
                       shape: tuple[int, int, int],
                       image_time: Value,
                       is_releasing: Value,
                       grabber_x: Value,
                       graber_y: Value,
                       object_x: Value,
                       object_y: Value,
                       text: Value):
        shared_memory = SharedMemory("Image")
        shared_memory_hsv = SharedMemory("HSV")
        shared_image = np.ndarray(shape, dtype=np.uint8, buffer=shared_memory.buf)
        shared_hsv = np.ndarray(shape, dtype=np.uint8, buffer=shared_memory_hsv.buf)
        while True:
            img_response = urllib.request.urlopen(imgae_url)
            t = time.time()
            image_time.value = int(t * 1000)

            if is_releasing.value:
                break

            imgnp = np.array(bytearray(img_response.read()), dtype=np.uint8)
            decoded = cv2.imdecode(imgnp, -1)
            hsv = cv2.cvtColor(decoded, cv2.COLOR_BGR2HSV)
            np.copyto(shared_image, decoded)
            np.copyto(shared_hsv, hsv)

            if grabber_x.value > 0 and graber_y.value > 0:
                decoded = cv2.rectangle(decoded, (grabber_x.value - 5, graber_y.value - 5), (grabber_x.value + 5, graber_y.value + 5), (255, 255, 0), 2)

            if object_x.value > 0 and object_y.value > 0:
                decoded = cv2.rectangle(decoded, (object_x.value - 5, object_y.value - 5), (object_x.value + 5, object_y.value + 5), (255, 0, 255), 2)

            decoded = cv2.putText(decoded, text.value, (5, 25), cv2.FONT_HERSHEY_SIMPLEX, 0.6, (255, 255, 0), 1)

            cv2.imshow("Robot", decoded)
            cv2.waitKey(1)

        shared_memory.close()
        cv2.destroyAllWindows()

    def release(self):
        self._shared_is_releasing.value = True

    @property
    def current_image(self) -> np.ndarray:
        return self._shared_image_data

    @property
    def image_time(self) -> int:
        return self._shared_image_time.value

    @property
    def current_image_hsv(self) -> np.ndarray:
        return self._shared_hsv_data

    def draw_grabber_pos(self, pos: tuple[int, int] | None):
        self._shared_grabber_x.value = 0 if pos is None else pos[0]
        self._shared_grabber_y.value = 0 if pos is None else pos[1]

    def draw_object_pos(self, pos: tuple[int, int] | None):
        self._shared_object_x.value = 0 if pos is None else pos[0]
        self._shared_object_y.value = 0 if pos is None else pos[1]

    def set_text(self, text: str):
        self._shared_text.value = text


if __name__ == "__main__":
    print("Connect")
    camera = WebCamera(
        "http://192.168.137.43/cam-lo.jpg",
        "http://192.168.137.43/cam-mid.jpg",
        "http://192.168.137.43/cam-hi.jpg"
    )
    print("Connected")

    import grab_helper

    while True:
        image = camera.current_image.copy()
        image_hsv = camera.current_image_hsv.copy()

        grabber_find_area = grab_helper.get_area(image.shape[1], image.shape[0], grab_helper.GRABBER_FIND_AREA)

        grabber_x, grabber_y = grab_helper.find_grabber_center(image_hsv, grabber_find_area)
        camera.draw_grabber_pos((grabber_x, grabber_y))

        cube_find_area = grab_helper.get_area(image.shape[1], image.shape[0], grab_helper.CUBE_FIND_AREA)
        cube_x, cube_y, rotated = grab_helper.find_cube(image_hsv, cube_find_area, "blue")

        if None not in (cube_x, cube_y, rotated):
            camera.draw_object_pos((cube_x, cube_y))

        #cv2.imshow("Cam", image)

        cv2.waitKey(1)