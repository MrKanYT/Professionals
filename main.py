# -*- coding: utf-8 -*-

import time
import random

from serial_robot import SerialRobot
from camera import Camera
from navigation import Navigator
from driver import BTDriver
import scanner
import grab_helper
import numpy as np
import traceback


def e1(driver: BTDriver):
    hsv = driver.camera.current_image_hsv

    cube_area = grab_helper.get_area(hsv.shape[1], hsv.shape[0], grab_helper.CUBE_FIND_AREA)

    shelf = 2

    points = ("cube0", )#, "cube1")
    colors = ("blue", "black")
    i = 0
    for point in points:

        driver.go_to(point)

        #driver.robot.set_servo_angle(130)

        cx, cy, r = grab_helper.find_cube(hsv, cube_area, colors[i])
        if None in (cx, cy):
            continue

        driver.take_item("blue")

        driver.go_to("storage")

        time.sleep(1)

        driver.put(shelf)
        time.sleep(2)

        time.sleep(2)

        i += 1

    driver.go_to("spawn")


def main(robot: SerialRobot, camera: Camera):

    navigator = Navigator("locations/test_loc.json")

    driver = BTDriver(robot, navigator, camera)

    driver.go_to("cube0")

    driver.take_item("green")

    driver.go_to("finish")

    robot.set_hand_angle(driver.HAND_ITEM_LEVEL)

    robot.open_grabber()

    time.sleep(10)


if __name__ == "__main__":

    _robot = SerialRobot("/dev/ttyAMA0")

    _camera = Camera(0, _robot._shared_telemetry)
    
    try:
        _robot.set_led_freq(60000)
        _robot.set_red_led(True)
        _robot.set_green_led(True)
        _robot.set_hand_angle(BTDriver.HAND_DEFAULT_ANGLE)
        _robot.switch_rangefinder(SerialRobot.RANGEFINDER_FORWARD, True)

        main(_robot, _camera)

        _robot.set_red_led(False)
        _robot.set_green_led(False)
    finally:
        _robot.release()
        _camera.release()

