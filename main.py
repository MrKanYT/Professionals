import urllib.request
import cv2
import numpy as np
import scanner


url = 'http://192.168.137.61/cam-hi.jpg'

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


while True:
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
