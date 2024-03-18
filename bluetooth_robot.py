import serial
from serial.serialutil import SerialException

import time

import multiprocessing
from multiprocessing.managers import SharedMemoryManager
from multiprocessing.shared_memory import ShareableList
from multiprocessing import Value, Manager, Event
import ctypes


class BTRobot:

    _command_interval: float
    _telemetry_len: int
    _stop_path: int
    _right_rotate_period: float
    _left_rotate_period: float

    _shared_memory_manager: Manager
    _shared_telemetry: ShareableList
    _shared_command: Value
    _shared_reset_command: Value

    _on_bluetooth_ready: Event
    _on_command_sent: Event
    _on_releasing: Event

    _bt_io: multiprocessing.Process

    def __init__(self, port):
        self._command_interval = 0.1
        self._telemetry_len = 3
        self._stop_path = 2
        self._right_rotate_period = 3.7
        self._left_rotate_period = 3.8

        self._shared_memory_manager = Manager()
        self._shared_telemetry = ShareableList([0] * self._telemetry_len)
        self._shared_command = self._shared_memory_manager.Value(ctypes.c_char_p, "")
        self._shared_reset_command = self._shared_memory_manager.Value(ctypes.c_bool, False)

        self._on_bluetooth_ready = Event()
        self._on_command_sent = Event()
        self._on_releasing = Event()

        self._bt_io = multiprocessing.Process(target=BTRobot.bluetooth_io, args=(
            port,
            self._command_interval,
            self._shared_telemetry,
            self._shared_command,
            self._shared_reset_command,
            self._on_bluetooth_ready,
            self._on_command_sent,
            self._on_releasing))

        self._bt_io.start()

        self._on_bluetooth_ready.wait()
        print("Robot BT ready")

    def release(self):
        self.stop()
        self._on_releasing.set()

    @property
    def telemetry(self) -> list[int]:
        return list(self._shared_telemetry)

    @property
    def forward_distance(self) -> int:
        return self._shared_telemetry[0]

    @property
    def left_distance(self) -> int:
        return self._shared_telemetry[1]

    @property
    def right_distance(self) -> int:
        return self._shared_telemetry[2]

    @staticmethod
    def bluetooth_io(port: str,
                     command_interval: float,
                     shared_telemetry: ShareableList,
                     shared_command: Value,
                     shared_reset_command: Value,
                     on_bluetooth_ready: Event,
                     on_command_sent: Event,
                     on_releasing: Event):
        trying = 3
        while trying > 0:
            try:
                ser = serial.Serial(port, 9600, timeout=5)
                break
            except SerialException:
                print("Connecting to BT failed")
            time.sleep(2)
            trying -= 1

        if trying <= 0:
            print("Failed to connect to BT")
            return

        last_send = 0

        on_bluetooth_ready.set()

        while ser.is_open:
            try:
                bdata = ser.readline()
                data = bdata.decode().strip()
                splitted = data[1:].split(", ")

                if not any(splitted):
                    continue

                bad_packet = False
                for i in range(len(splitted)):
                    if splitted[i].isdigit():
                        shared_telemetry[i] = int(splitted[i])
                    else:
                        bad_packet = True
                        break
                if bad_packet:
                    continue

                if on_releasing.is_set():
                    break

                if shared_command.value:
                    t = time.time()
                    if on_command_sent.is_set() or t - last_send > command_interval:
                        last_send = t
                        ser.write(shared_command.value.encode("ascii"))
                        if shared_reset_command.value:
                            shared_command.value = ""
                            shared_reset_command.value = False

                        on_command_sent.set()
            except KeyboardInterrupt:
                break

        ser.close()

    def send_command(self, command: str, send_once: bool = False, wait: bool = True):
        self._on_command_sent.clear()
        self._shared_reset_command.value = send_once
        self._shared_command.value = command

        if wait:
            self._on_command_sent.wait()

    def wait_for_forward_distance(self, distance: int, inversed: bool = False):
        anti_noise = 3
        while True:
            if (not inversed and self.forward_distance <= distance) or (inversed and self.forward_distance >= distance):
                anti_noise -= 1
                if anti_noise <= 0:
                    return
            else:
                anti_noise = 3

    def forward(self, *args, distance_to_wall: int = 0):
        self.send_command("f")

        if distance_to_wall <= 0:
            return

        stop_distance = distance_to_wall + self._stop_path
        self.wait_for_forward_distance(stop_distance)

        self.stop()

    def back(self, *args, distance_to_wall: int = 0):
        self.send_command("B")

        if distance_to_wall <= 0:
            return

        stop_distance = distance_to_wall - self._stop_path
        self.wait_for_forward_distance(stop_distance, True)

        self.stop()

    def stop(self):
        self.send_command("s", send_once=True)

    def left(self, degrees: int = 0):
        self.send_command("l")

        if degrees == 0:
            return

        t = self._left_rotate_period * (degrees / 360)
        time.sleep(t)

        self.stop()

    def right(self, degrees: int = 0):
        self.send_command("r")

        if degrees == 0:
            return

        t = self._right_rotate_period * (degrees / 360)
        time.sleep(t)

        self.stop()

    def stab_forward_distance(self, distance: int, max_error: int = 3):

        while abs(self.forward_distance - distance) > max_error:
            if self.forward_distance > distance:
                self.forward(distance_to_wall=distance)
            else:
                self.back(distance_to_wall=distance)

    def rotate(self, degrees=0):
        pass


