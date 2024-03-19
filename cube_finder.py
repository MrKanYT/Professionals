import cv2

GRABBER_COLOR_0_MIN = (130, 100, 100)
GRABBER_COLOR_0_MAX = (180, 255, 255)

GRABBER_COLOR_1_MIN = (0, 100, 100)
GRABBER_COLOR_1_MAX = (20, 255, 255)


def find_grabber_center(image_hsv: cv2.UMat) -> tuple[int, int]:
    mask = cv2.inRange(image_hsv, GRABBER_COLOR_0_MIN, GRABBER_COLOR_0_MAX) + cv2.inRange(image_hsv, GRABBER_COLOR_1_MIN, GRABBER_COLOR_1_MAX)

    contours = cv2.findContours()

    return 0, 0


if __name__ == "__main__":
    image = cv2.imread("test_images/grabber/find_grabber.jpg")
    image_hsv = cv2.cvtColor(image, cv2.COLOR_BGR2HSV)

    x, y = find_grabber_center(image_hsv)

    cv2.imshow("Find grabber", cv2.cvtColor(image_hsv, cv2.COLOR_HSV2BGR))
    cv2.waitKey(0)