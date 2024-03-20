import cv2
import random

GRABBER_COLOR_0_MIN = (170, 50, 50)
GRABBER_COLOR_0_MAX = (180, 255, 255)

GRABBER_COLOR_1_MIN = (0, 50, 50)
GRABBER_COLOR_1_MAX = (10, 255, 255)

GRABBER_FIND_AREA = (0, 1), (0.7, 1)

CUBE_COLOR_HUE_WINDOW_START = -15
CUBE_COLOR_HUE_WINDOW_SIZE = 30
CUBE_COLOR_SATURATION_LIMITS = (40, 255)
CUBE_COLOR_VALUE_LIMITS = (40, 255)
CUBE_MIN_AREA = 2000
CUBE_MAX_AREA = 30000

CUBE_FIND_AREA = (0, 1), (0, 1)

CAMERA_DISTANCE = 740


def get_area(img_size_x: int, img_size_y: int, relative_size: tuple[tuple[float, float], tuple[float, float]]) -> tuple[tuple[int, int], tuple[int, int]]:
    min_x, max_x = int(img_size_x * relative_size[0][0]), int(img_size_x * relative_size[0][1])
    min_y, max_y = int(img_size_y * relative_size[1][0]), int(img_size_y * relative_size[1][1])
    return (min_x, max_x), (min_y, max_y)


def find_grabber_center(image_hsv: cv2.UMat, area: tuple[tuple[int, int], tuple[int, int]]) -> tuple[int, int]:
    image_hsv = image_hsv[area[1][0]:area[1][1], area[0][0]:area[0][1]]

    mask = cv2.inRange(image_hsv, GRABBER_COLOR_0_MIN, GRABBER_COLOR_0_MAX) + cv2.inRange(image_hsv, GRABBER_COLOR_1_MIN, GRABBER_COLOR_1_MAX)

    contours, _ = cv2.findContours(mask, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
    if len(contours) < 2:
        return -1, -1

    cnt0, cnt1 = sorted(contours, key=lambda c: cv2.contourArea(c), reverse=True)[:2]
    moments0, moments1 = cv2.moments(cnt0), cv2.moments(cnt1)

    try:
        center0_x, center0_y = int(moments0["m10"] / moments0["m00"]), int(moments0["m01"] / moments0["m00"])
        center1_x, center1_y = int(moments1["m10"] / moments1["m00"]), int(moments1["m01"] / moments1["m00"])
    except ZeroDivisionError:
        return -1, -1

    center = (int((center0_x + center1_x) / 2) + area[0][0], int((center0_y + center1_y) / 2) + area[1][0])

    return center


def find_cube(image_hsv: cv2.UMat, area: tuple[tuple[int, int]]) -> tuple[int | None, int | None, bool | None]:
    image_hsv = image_hsv[area[1][0]:area[1][1], area[0][0]:area[0][1]]

    contours = []
    for i in range(1): #'''CUBE_COLOR_HUE_WINDOW_START, 181, CUBE_COLOR_HUE_WINDOW_SIZE'''):
        if i + CUBE_COLOR_HUE_WINDOW_SIZE < 0:
            continue

        if i < 0:
            mask = cv2.inRange(image_hsv,
                               (180 + i, CUBE_COLOR_SATURATION_LIMITS[0], CUBE_COLOR_VALUE_LIMITS[0]),
                               (180, CUBE_COLOR_SATURATION_LIMITS[1], CUBE_COLOR_VALUE_LIMITS[1])) +\
                   cv2.inRange(image_hsv,
                               (0, CUBE_COLOR_SATURATION_LIMITS[0], CUBE_COLOR_VALUE_LIMITS[0]),
                               (CUBE_COLOR_HUE_WINDOW_SIZE + i, CUBE_COLOR_SATURATION_LIMITS[1], CUBE_COLOR_VALUE_LIMITS[1]))
        else:
            '''mask = cv2.inRange(image_hsv, (i, CUBE_COLOR_SATURATION_LIMITS[0], CUBE_COLOR_VALUE_LIMITS[0]),
                               (i + CUBE_COLOR_HUE_WINDOW_SIZE, CUBE_COLOR_SATURATION_LIMITS[1], CUBE_COLOR_VALUE_LIMITS[1]))'''
            mask = cv2.inRange(image_hsv, GRABBER_COLOR_0_MIN, GRABBER_COLOR_0_MAX) + cv2.inRange(image_hsv,
                                                                                                  GRABBER_COLOR_1_MIN,
                                                                                                  GRABBER_COLOR_1_MAX)

        biggest_area = 0
        biggest = None
        cnts, _ = cv2.findContours(mask, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

        for cnt in cnts:
            a = cv2.contourArea(cnt)
            if a < CUBE_MIN_AREA or a > CUBE_MAX_AREA:
                continue
            if a > biggest_area:
                biggest_area = a
                biggest = cnt

        if biggest is not None:
            contours.append(biggest)

    #cv2.imshow(f"Cnt {random.randint(0, 100)}", cv2.drawContours(img.copy(), contours, -1, (0, 255, 255), 1))
    #cv2.waitKey(0)

    center_x, center_y = int(image_hsv.shape[1] // 2), int(image_hsv.shape[0] // 2)

    closest_center = None
    closest_distance = -1
    closest_rotated = False
    for cnt in contours:
        #approx = cv2.approxPolyDP(cnt, 15, True)
        #if not (4 <= len(approx) <= 6):
            #continue

        moments = cv2.moments(cnt)
        cx, cy = int(moments["m10"] / moments["m00"]), int(moments["m01"] / moments["m00"])
        dst = ((center_x - cx) ** 2 + (center_y - cy) ** 2) ** 0.5
        if closest_distance == -1 or dst < closest_distance:
            closest_distance = dst
            closest_center = (cx, cy)
            closest_rotated = len(cnt) > 4

    if closest_center is None:
        return None, None, None

    return closest_center[0] + area[0][0], closest_center[1] + area[1][0], closest_rotated


def calculate_distance(grabber_y: int, object_y: int) -> int:
    return int((1 - object_y / grabber_y) * CAMERA_DISTANCE)


if __name__ == "__main__":

    '''for name in ("front", "45", "rot0", "rot1"):

        image = cv2.imread(f"test_images/grabber/cube_red_{name}.jpg")

        hsv = cv2.cvtColor(image, cv2.COLOR_BGR2HSV)

        grabber_find_area = get_area(image.shape[1], image.shape[0], GRABBER_FIND_AREA)

        grabber_x, grabber_y = find_grabber_center(hsv, grabber_find_area)
        cv2.rectangle(image, (grabber_x-10, grabber_y-10), (grabber_x+10, grabber_y+10), (255, 255, 0), 1)

        cube_x, cube_y, rotated = find_cube(hsv, grabber_find_area)
        cv2.rectangle(image, (cube_x - 10, cube_y - 10), (cube_x + 10, cube_y + 10), (255 * rotated, 255 * (not rotated), 255), 1)

        cv2.imshow(f"CUBE {name}", image)
    cv2.waitKey(0)'''




