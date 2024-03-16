import cv2 as cv
import numpy as np
from typing import TypeAlias
import math

COLOR_MIN = (0, 0, 0)
COLOR_MAX = (179, 255, 100)
MIN_CODE_RECT_AREA = 2500
CONTOURS_APPROX_EPSILON = 10
BIT_CHECK_NEIGHBOURS = 2
BIT_CHECK_THRESHOLD = 100

CODE_SIZE = 2

Point: TypeAlias = tuple[int, int]
Line: TypeAlias = tuple[Point, Point]


def _find_code_rect(hsv_image: cv.UMat,
                    min_area: float,
                    color_min: tuple[int, int, int],
                    color_max: tuple[int, int, int],
                    approx_epsilon: float) -> tuple[Point, Point, Point, Point] | None:

    mask = cv.inRange(hsv_image, color_min, color_max)
    contours, _ = cv.findContours(mask, cv.RETR_EXTERNAL, cv.CHAIN_APPROX_SIMPLE)

    biggest_area = 0
    biggest = None
    cv.drawContours(hsv_image, contours, -1, (50, 100, 100), 1)
    for cnt in contours:
        area = cv.contourArea(cnt)
        if area > biggest_area and area > min_area:
            approx: list[list[np.ndarray]] = cv.approxPolyDP(cnt, approx_epsilon, True)
            if len(approx) == 4:
                biggest = [(c[0][0], c[0][1]) for c in approx]
                biggest_area = area

    return biggest


def _put_points_between(p1: Point, p2: Point, count: int) -> list[Point]:
    points = []
    part_x = (p2[0] - p1[0]) / (count * 2)
    part_y = (p2[1] - p1[1]) / (count * 2)
    for i in range(0, count):
        point_x = int(p1[0] + part_x + part_x * i * 2)
        point_y = int(p1[1] + part_y + part_y * i * 2)
        points.append((point_x, point_y))
    return points


def _get_vertical_factor(p1: Point, p2: Point) -> float:
    x_delta = abs(p2[0] - p1[0])
    if x_delta == 0:
        return math.inf

    y_delta = abs(p2[1] - p1[1])
    return y_delta / x_delta


def _get_two_vertical_lines(*lines: Line) -> tuple[Line, Line]:
    srtd = sorted(lines, key=lambda t: _get_vertical_factor(t[0], t[1]), reverse=True)
    return srtd[0], srtd[1]


def _get_bit_positions(code_rect: tuple[Point, Point, Point, Point], code_size: int) -> list[Point]:
    line_1, line_2 = _get_two_vertical_lines(
        (code_rect[0], code_rect[1]),
        (code_rect[1], code_rect[2]),
        (code_rect[2], code_rect[3]),
        (code_rect[3], code_rect[0]))

    edge_points_1 = sorted(_put_points_between(line_1[0], line_1[1], code_size), key=lambda p: p[1])
    edge_points_2 = sorted(_put_points_between(line_2[0], line_2[1], code_size), key=lambda p: p[1])

    positions = []

    for i in range(code_size):
        positions += sorted(_put_points_between(edge_points_1[i], edge_points_2[i], code_size), key=lambda p: p[0])

    return positions


def _get_bit_value(image_hsv: cv.UMat, position: Point, neighbours: int) -> bool:
    min_x, max_x = position[0]-neighbours, position[0]+neighbours+1
    min_y, max_y = position[1]-neighbours, position[1]+neighbours+1
    points = image_hsv[min_y:max_y, min_x:max_x]

    average_color_value = np.mean(points, axis=0)[2][2]

    return average_color_value < BIT_CHECK_THRESHOLD


def read_code(image_hsv: cv.UMat) -> tuple[list[bool] | None, tuple[Point, Point, Point, Point] | None, list[Point] | None]:
    code_rect = _find_code_rect(image_hsv, MIN_CODE_RECT_AREA, COLOR_MIN, COLOR_MAX, CONTOURS_APPROX_EPSILON)
    if code_rect is None:
        return None, None, None

    bit_positions = _get_bit_positions(code_rect, CODE_SIZE)

    values = []
    for pos in bit_positions:
        values.append(_get_bit_value(image_hsv, pos, BIT_CHECK_NEIGHBOURS))

    return values, tuple(code_rect), bit_positions


def test():
    for ind in range(1, 2):
        img = cv.imread(f"test_images/scanner/real_camera_{ind}.png")
        hsv_img = cv.cvtColor(img, cv.COLOR_BGR2HSV)

        code_rect = _find_code_rect(hsv_img, MIN_CODE_RECT_AREA, COLOR_MIN, COLOR_MAX, CONTOURS_APPROX_EPSILON)

        if code_rect is not None:

            bit_positions = _get_bit_positions(code_rect, CODE_SIZE)

            values = []
            for pos in bit_positions:
                values.append(_get_bit_value(hsv_img, pos, BIT_CHECK_NEIGHBOURS))

            for i, p in enumerate(bit_positions):
                color = (0, 255, 0) if values[i] else (0, 0, 255)
                cv.putText(img, str(i), (p[0], p[1] - 15), cv.FONT_HERSHEY_SIMPLEX, 0.9, (255, 0, 0), 2)
                cv.circle(img, p, 2, color, 3)
                cv.imshow(f"Test {ind}", img)
        else:
            print("Code rect not found")
            cv.imshow(f"Test {ind} (failed)", cv.cvtColor(hsv_img, cv.COLOR_HSV2BGR))

    cv.waitKey(0)


if __name__ == "__main__":
    test()



