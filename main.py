# -*- coding: utf-8 -*-

import time
import random

import cv2
from bluetooth_robot import BTRobot
from camera import WebCamera
from navigation import Navigator
from driver import BTDriver
import scanner


url = ''


def test_distance_stop(tryings: int, robot: BTRobot, min_distance: int, max_distance: int, start_distance: int):
    for trying in range(1, tryings + 1):

        distance = random.randint(min_distance, max_distance)
        print(f"Trying #{trying}: Distance - {distance};")

        robot.back(distance_to_wall=start_distance)
        print(f"Trying #{trying}: Start - {robot.forward_distance};")

        time.sleep(3)

        robot.forward(distance_to_wall=distance)
        print(f"Trying #{trying}: Finish - {robot.forward_distance}; Error - {robot.forward_distance - distance}")

        time.sleep(3)


def main(robot: BTRobot):

    camera = WebCamera(
        "http://192.168.137.31/cam-lo.jpg",
        "http://192.168.137.31/cam-mid.jpg",
        "http://192.168.137.31/cam-hi.jpg"
    )

    navigator = Navigator("locations/test_loc.json")

    driver = BTDriver(robot, navigator)

    driver.go_to("qr_code")

    driver.go_to("cube0")
    robot.take_item()

    driver.go_to("spawn")
    robot.drop_item()

    driver.go_to("cube1")
    robot.take_item()

    driver.go_to("spawn")
    robot.drop_item()


if __name__ == "__main__":

    _robot = BTRobot("COM10")
    time.sleep(1)

    try:
        main(_robot)
    finally:
        _robot.release()


    '''while True:
        image = camera.high_image
        image_hsv = cv2.cvtColor(image, cv2.COLOR_BGR2HSV)

        code_values, rect, bit_positions = scanner.read_code(image_hsv)
        if None not in (code_values, rect, bit_positions):

            for i, point in enumerate(bit_positions):
                color = (0, 255, 0) if code_values[i] else (0, 0, 255)
                image = cv2.circle(image, point, 2, color, 3)

        image = cv2.putText(image, f"Перед: {robot.forward_distance}", (15, 30), cv2.FONT_HERSHEY_COMPLEX, 0.6, (0, 200, 0), 1)
        image = cv2.putText(image, f"Лево: {robot.left_distance}", (15, 50), cv2.FONT_HERSHEY_COMPLEX, 0.6, (0, 200, 0), 1)
        image = cv2.putText(image, f"Право: {robot.right_distance}", (15, 70), cv2.FONT_HERSHEY_COMPLEX, 0.6, (0, 200, 0), 1)

        cv2.imshow('gotcha', image)
        key = cv2.waitKey(5)

        if key == ord('q'):
            break

        if key == ord("w"):
            robot.forward()

        if key == ord("s"):
            robot.back()

        if key == ord(" "):
            robot.stop()

        if key == ord("a"):
            robot.left()

        if key == ord("d"):
            robot.right()

    cv2.destroyAllWindows()'''





