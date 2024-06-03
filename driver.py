import math

import numpy

from serial_robot import SerialRobot
from navigation import Navigator
import time
from typing import Callable
from camera import Camera
import grab_helper

import cv2

class BTDriver:

    COMMANDS = {
        "Wc": lambda robot, dst: robot.go(0, wall_distance=dst, correct=True),
        "W": lambda robot, dst: robot.go(0, wall_distance=dst),
        "Fc": lambda robot, dst: robot.go(dst, correct=True),
        "F": lambda robot, dst: robot.go(dst),
        "R": lambda robot, degrees: robot.rotate(degrees),
    }
    COMMAND_ARGS_SEPARATOR = ","

    HAND_DEFAULT_ANGLE = 125
    HAND_ITEM_LEVEL = 125

    SHELF_1 = 92
    SHELF_2 = 40
    SHELF_DISTANCE = 25

    robot: SerialRobot
    navigator: Navigator
    camera: Camera

    def __init__(self, robot: SerialRobot, navigator: Navigator, camera: Camera):
        self.robot = robot
        self.navigator = navigator
        self.camera = camera

    @staticmethod
    def _parse_command(command: str) -> tuple[str, list[int | float]]:
        for cmd_key, action in BTDriver.COMMANDS.items():
            if command.startswith(cmd_key):
                args = []
                str_args = command[len(cmd_key):].split(BTDriver.COMMAND_ARGS_SEPARATOR)
                for arg in str_args:
                    if not arg:
                        continue

                    v = float(arg)
                    if v % 1 == 0:
                        v = int(v)
                    args.append(v)
                return cmd_key, args
        raise NotImplementedError(f"Unknown command key: '{command}'")

    def execute(self, command: str | tuple[str, list[int | float]]):
        if isinstance(command, str):
            cmd_key, cmd_args = self._parse_command(command)
        else:
            cmd_key, cmd_args = command

        self.COMMANDS[cmd_key](self.robot, *cmd_args)

    @staticmethod
    def _merge_rot_commands(commands: list[str]) -> list[tuple[str, list[int | float]]]:
        result = []
        l = len(commands)
        i = 0
        while i < l:
            cmd_key, cmd_args = BTDriver._parse_command(commands[i])
            if cmd_key != "R":
                result.append((cmd_key, cmd_args))
                i += 1
                continue
            angle = cmd_args[0]
            j = i + 1
            while j < l:
                next_cmd_key, next_cmd_args = BTDriver._parse_command(commands[j])
                if next_cmd_key != "R":
                    break
                j += 1
                angle += next_cmd_args[0]

            angle = math.copysign(abs(angle) % 360, angle)

            if angle != 0:
                if angle > 180:
                    angle = 180 - angle
                elif angle < -180:
                    angle = -180 - angle

                result.append((cmd_key, [angle, ]))
            i = j

        return result

    @staticmethod
    def _merge_wall_commands(commands: list[tuple[str, list[int | float]]]) -> list[tuple[str, list[int | float]]]:
        result = []
        l = len(commands)
        i = 0
        while i < l:
            cmd_key, cmd_args = commands[i]
            if cmd_key != "F" and cmd_key != "Fc":
                result.append((cmd_key, cmd_args))
                i += 1
                continue
            wall_dist = 0
            j = i + 1
            c = ""
            while j < l:
                next_cmd_key, next_cmd_args = commands[j]
                if next_cmd_key != "W" and next_cmd_key != "Wc":
                    break
                c = next_cmd_key
                j += 1
                wall_dist = next_cmd_args[0]

            if wall_dist > 0:
                result.append((c, [wall_dist]))
            else:
                result.append((cmd_key, cmd_args))

            i = j
        return result

    def execute_many(self, commands: list[str]):
        print(f"EXECUTE MANY: {commands}")
        merged = BTDriver._merge_rot_commands(commands)
        print(f"MERGED ROT: {merged}")
        merged = BTDriver._merge_wall_commands(merged)
        print(f"EXECUTE WALL: {merged}")
        for cmd in merged:
            self.execute(cmd)
            time.sleep(0.2)
            self.robot.reset_position()
            time.sleep(0.2)

    def go_to(self, wp_name: str):
        if not wp_name:
            raise NameError(f"Unknown waypoint: '{wp_name}'")

        if self.navigator.current_waypoint.name == wp_name:
            return

        print(f"Going to te point {wp_name}...")

        path = self.navigator.find_path(wp_name)
        self.execute_many(path)
        self.navigator.set_current_waypoint(wp_name)
        print(f"Arrived to the point {wp_name}")

    def _get_grabber_center(self) -> tuple[int, int]:
        sum_x = sum_y = 0
        n = 0

        find_area = grab_helper.get_area(self.camera.image_size[0], self.camera.image_size[1], grab_helper.GRABBER_FIND_AREA)

        for i in range(5):
            cx, cy = grab_helper.find_grabber_center(self.camera.current_image_hsv, find_area)
            if cx != -1 and cy != -1:
                n += 1
                sum_x += cx
                sum_y += cy
            time.sleep(0.2)

        if n == 0:
            return -1, -1

        return int(sum_x / n), int(sum_y / n)

    def rotate_to_object(self):
        find_area = grab_helper.get_area(self.camera.image_size[0], self.camera.image_size[1],
                                         grab_helper.CUBE_FIND_AREA)

        f = 10
        while True:
            cx, cy, rot = grab_helper.find_cube(self.camera.current_image_hsv, find_area)
            if None not in (cx, cy, rot):
                f -= 1
                if f <= 0:
                    return
            else:
                f = 10
                self.robot.rotate(15)


    def take_item(self, color: str):
        self.robot.set_hand_angle(self.HAND_ITEM_LEVEL)

        self.robot.open_grabber()

        grabber_center = self._get_grabber_center()
        self.camera.draw_grabber_pos(grabber_center)


        cube_find_area = grab_helper.get_area(self.camera.image_size[0], self.camera.image_size[1],
                                         grab_helper.CUBE_FIND_AREA)
        prev_image_time = 0
        not_found = 10
        while True:

            hsv = self.camera.current_image_hsv
            image_time = self.camera.image_time

            if image_time == prev_image_time:
                time.sleep(0.05)
                continue
            prev_image_time = image_time

            cx, cy, rot = grab_helper.find_cube(hsv, cube_find_area, color)

            if None not in (cx, cy, rot):
                not_found = 10
                self.camera.draw_object_pos((cx, cy))

                rot_delta = grabber_center[0] - cx
                dist_delta = grabber_center[1] - cy

                if rot_delta > 10:
                    self.robot.rotate(-3)
                    continue
                elif rot_delta < -10:
                    self.robot.rotate(3)
                    continue

                
                if dist_delta > 300:
                    self.robot.go(15)
                elif dist_delta > 200:
                    self.robot.go(4)
                elif dist_delta > 28:
                  
                    self.robot.go(2)
                else:
                    break


            else:
                self.camera.draw_object_pos(None)
                
                time.sleep(0.5)
                not_found -= 1
                if not_found <= 0:
                    raise TimeoutError

            time.sleep(0.05)

        self.robot.close_grabber()

        self.camera.draw_object_pos(None)
        self.camera.draw_grabber_pos(None)
        time.sleep(1)
        self.robot.set_hand_angle(self.HAND_DEFAULT_ANGLE)
        self.robot.go(-15)

        time.sleep(1)

    def put(self, shelf: int):
        print(f"Putting cube to the shelf {shelf}")

        shelf_angle = self.SHELF_1 if shelf == 1 else self.SHELF_2
        self.robot.set_hand_angle(shelf_angle)

        self.robot.go(0, correct=True, wall_distance=self.SHELF_DISTANCE)

        time.sleep(1)
        self.robot.open_grabber()

        time.sleep(1)
        self.robot.go(-10)

        time.sleep(1)

        


if __name__ == "__main__":
    res = BTDriver._merge_wall_commands([('R', [180.0]), ('Fc', [70]), ('Wc', [40]), ('R', [90.0]), ('Wc', [100]), ('R', [90.0]), ('F', [65])])
    print(res)