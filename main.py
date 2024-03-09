import time
import urllib.request
import cv2
import numpy as np
import serial
import scanner
import multiprocessing
from multiprocessing.managers import SharedMemoryManager
from multiprocessing.shared_memory import ShareableList
from multiprocessing import Value, Manager
import ctypes

url = 'http://192.168.137.130/cam-lo.jpg'

yellow = ((18, 60, 100), (32, 255, 255))
red = ((-8, 60, 100), (5, 255, 255))
green = ((50, 60, 100), (80, 255, 255))
blue = ((90, 60, 100), (130, 255, 255))
black = ((0, 0, 0), (360, 100, 30))


def findObject(img, limits):
    cx = 0
    cy = 0

    hsv = cv2.cvtColor(img, cv2.COLOR_BGR2HSV)
    binary = cv2.inRange(hsv, limits[0], limits[1])
    cv2.imshow('mask', binary)
    contours, _ = cv2.findContours(binary, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_NONE)
    if len(contours) > 0:

        maxc = max(contours, key=cv2.contourArea)
        moments = cv2.moments(maxc)
        if moments['m00'] > 200:
            cx = int(moments['m10'] / moments['m00'])
            cy = int(moments['m01'] / moments['m00'])

            print(cx, cy)
        else:
            print('small')
            return 0
    else:
        print('none')
        return 0
    return 1


class BTRobot:

    command_interval: float

    shared_memory_manager: Manager
    shared_telemetry: ShareableList
    shared_command: multiprocessing.Value
    shared_reset_command: multiprocessing.Value

    bt_io: multiprocessing.Process

    def __init__(self, port):
        super().__init__()

        self.shared_memory_manager = Manager()
        self.shared_command = self.shared_memory_manager.Value(ctypes.c_char_p, "")
        self.shared_telemetry = ShareableList([0, 0, 0])
        self.shared_reset_command = self.shared_memory_manager.Value(ctypes.c_bool, False)

        self.command_interval = 0.1

        self.bt_io = multiprocessing.Process(target=BTRobot.bt_connector, args=(
            port,
            self.command_interval,
            self.shared_telemetry,
            self.shared_command,
            self.shared_reset_command))

        self.bt_io.start()

    @staticmethod
    def bt_connector(port: str,
                     command_interval: float,
                     shared_telemetry: ShareableList,
                     shared_command: Value,
                     shared_reset_command: Value):
        ser = serial.Serial(port, 9600, timeout=1)
        last_send = 0
        while True:
            bdata = ser.readline()
            data = bdata.decode().strip()
            splitted = data[1:].split(", ")

            for i in range(len(splitted)):
                shared_telemetry[i] = int(splitted[i])

            if shared_command.value:
                t = time.time()
                if t - last_send > command_interval:
                    last_send = t
                    ser.write(shared_command.value.encode("ascii"))
                    if shared_reset_command.value:
                        shared_command.value = ""
                        shared_reset_command.value = False

    def forward(self):
        self.shared_command.value = "F"

    def stop(self):
        self.shared_command.value = "S"
        self.shared_reset_command.value = True

    @property
    def telemetry(self) -> list[int]:
        return list(self.shared_telemetry)


if __name__ == "__main__":
    bt_robot = BTRobot("COM11")
    while True:
        print(bt_robot.telemetry)

'''time.sleep(5)
bt_robot.forward()
time.sleep(5)
bt_robot.stop()'''

'''while True:
    imgResponse = urllib.request.urlopen(url)
    imgnp = np.array(bytearray(imgResponse.read()), dtype=np.uint8)
    image = cv2.imdecode(imgnp, -1)
    image_hsv = cv2.cvtColor(image, cv2.COLOR_BGR2HSV)

    code_values, rect, bit_positions = scanner.read_code(image_hsv)
    if None not in (code_values, rect, bit_positions):
        print(f"Read values from code: {code_values}")
        for i, point in enumerate(bit_positions):
            color = (0, 255, 0) if code_values[i] else (0, 0, 255)
            image = cv2.circle(image, point, 2, color, 3)

    #image = cv2.circle(image, findObject(image, green), radius=10, color=red[1], thickness=-1)

    cv2.imshow('gotcha', image)
    key = cv2.waitKey(5)
    if key == ord('q'): break

cv2.destroyAllWindows()
'''