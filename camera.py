import urllib.request
import numpy as np
import cv2


class WebCamera:

    low_quality_url: str
    medium_quality_url: str
    high_quality_url: str

    def __init__(self,
                 low_qual_url: str,
                 med_qual__url: str,
                 high_qual_url: str):

        self.low_quality_url = low_qual_url
        self.medium_quality_url = med_qual__url
        self.high_quality_url = high_qual_url

    @staticmethod
    def get_image(url: str) -> cv2.Mat:
        img_response = urllib.request.urlopen(url)
        imgnp = np.array(bytearray(img_response.read()), dtype=np.uint8)
        return cv2.imdecode(imgnp, -1)

    @property
    def low_image(self) -> cv2.Mat:
        return WebCamera.get_image(self.low_quality_url)

    @property
    def medium_image(self) -> cv2.Mat:
        return WebCamera.get_image(self.medium_quality_url)

    @property
    def high_image(self) -> cv2.Mat:
        return WebCamera.get_image(self.high_quality_url)


if __name__ == "__main__":
    camera = WebCamera(
        "http://192.168.137.31/cam-lo.jpg",
        "http://192.168.137.31/cam-mid.jpg",
        "http://192.168.137.31/cam-hi.jpg"
    )


    image = camera.high_image

    cv2.imshow("Cam", image)
    cv2.imwrite("test_images/grabber/find_grabber.jpg", image)

    cv2.waitKey(1)