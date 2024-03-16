from bluetooth_robot import BTRobot
from navigation import Navigator
import time


class BTDriver:

    COMMANDS = {
        "W": lambda robot, dst: robot.stab_forward_distance(distance=dst),
        "Ld": lambda robot, degrees: robot.left(degrees=degrees),
        "L": lambda robot: robot.left(degrees=90),
        "Rd": lambda robot, degrees: robot.right(degrees=degrees),
        "R": lambda robot: robot.right(degrees=90),
    }
    COMMAND_ARGS_SEPARATOR = ","

    robot: BTRobot
    navigator: Navigator

    def __init__(self, robot: BTRobot, navigator: Navigator):
        self.robot = robot
        self.navigator = navigator

    def execute(self, command: str):

        for cmd_key, action in self.COMMANDS.items():
            if command.startswith(cmd_key):
                cmd_args = command[len(cmd_key):].split(self.COMMAND_ARGS_SEPARATOR)
                action_args = [self.robot, ]
                for arg in cmd_args:
                    if not arg:
                        continue

                    v = float(arg)
                    if v % 1 == 0:
                        v = int(v)
                    action_args.append(v)

                action(*action_args)
                return

        raise NotImplementedError(f"Unknown command key: '{command}'")

    def execute_many(self, commands: list[str]):
        for cmd in commands:
            self.execute(cmd)
            time.sleep(1.5)

    def go_to(self, wp_name: str):
        if not wp_name:
            raise NameError(f"Unknown waypoint: '{wp_name}'")

        if self.navigator.current_waypoint.name == wp_name:
            return

        path = self.navigator.find_path(wp_name)
        self.execute_many(path)
        self.navigator.set_current_waypoint(wp_name)

