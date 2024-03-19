import math

from bluetooth_robot import BTRobot
from navigation import Navigator
import time
from typing import Callable


class BTDriver:

    COMMANDS = {
        "F": lambda robot, dst: robot.go(dst),
        "R": lambda robot, degrees: robot.rotate(degrees),
    }
    COMMAND_ARGS_SEPARATOR = ","

    robot: BTRobot
    navigator: Navigator

    def __init__(self, robot: BTRobot, navigator: Navigator):
        self.robot = robot
        self.navigator = navigator

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
    def _merge_commands(commands: list[str]) -> list[tuple[str, list[int | float]]]:
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

    def execute_many(self, commands: list[str]):
        merged = BTDriver._merge_commands(commands)
        for cmd in merged:
            self.execute(cmd)

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


if __name__ == "__main__":
    res = BTDriver._merge_commands(["R90", "F50", "R-180", "R-180", "F40"])
    print(res)