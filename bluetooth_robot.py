import serial
from serial.serialutil import SerialException

import time
import math

import multiprocessing
from multiprocessing.managers import SharedMemoryManager
from multiprocessing.shared_memory import ShareableList
from multiprocessing import Value, Manager, Event
import ctypes


class BTRobot:

    _telemetry_len: int

    _shared_memory_manager: Manager
    _shared_telemetry: ShareableList
    _shared_command: Value
    _shared_confirmations: Value

    _on_bluetooth_ready: Event
    _on_command_sent: Event
    _on_command_completed: Event
    _on_releasing: Event

    _bt_io: multiprocessing.Process

    def __init__(self, port):
        self._telemetry_len = 7

        self._shared_memory_manager = Manager()
        self._shared_telemetry = ShareableList([0] * self._telemetry_len)
        self._shared_command = self._shared_memory_manager.Value(ctypes.c_char_p, "")
        self._shared_confirmations = self._shared_memory_manager.Value(ctypes.c_uint8, 1)

        self._on_bluetooth_ready = Event()
        self._on_command_sent = Event()
        self._on_command_completed = Event()
        self._on_releasing = Event()

        self._bt_io = multiprocessing.Process(target=BTRobot.bluetooth_io, args=(
            port,
            self._shared_telemetry,
            self._shared_command,
            self._shared_confirmations,
            self._on_bluetooth_ready,
            self._on_command_sent,
            self._on_command_completed,
            self._on_releasing))

        self._bt_io.start()

        self._on_bluetooth_ready.wait()

        #self.reset_position()
        print("Robot BT ready")

    @staticmethod
    def bluetooth_io(port: str,
                     shared_telemetry: ShareableList,
                     shared_command: Value,
                     shared_confirmations: Value,
                     on_bluetooth_ready: Event,
                     on_command_sent: Event,
                     on_command_completed: Event,
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

        on_bluetooth_ready.set()
        confirmations_left = shared_confirmations.value
        while ser.is_open:
            try:
                bdata = ser.readline()
                data = bdata.decode().strip()

                if on_releasing.is_set():
                    break

                if data == "OK":
                    confirmations_left -= 1
                    #print(f"BT CONFIRMED >>> {confirmations_left} LEFT")
                    if confirmations_left <= 0:
                        on_command_completed.set()
                        shared_confirmations.value = 1
                else:
                    splitted = data[1:].split(" ")
                    if any(splitted):
                        for i in range(len(splitted)):
                            if splitted[i].isdigit():
                                shared_telemetry[i] = int(splitted[i])
                            else:
                                break

                if shared_command.value:
                    #print(f"SEND BT >>> {shared_command.value}")
                    ser.write(shared_command.value.encode("ascii"))
                    #print(f"SET CONFIRMATIONS: {shared_confirmations.value}")
                    confirmations_left = shared_confirmations.value
                    shared_command.value = ""
                    on_command_sent.set()
            except KeyboardInterrupt:
                break

        ser.close()

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

    def send_command(self, command: str,
                     await_sending: bool = True,
                     await_completion: bool = False,
                     await_completion_timeout: float = 3,
                     required_confirmations: int = 1):
        self._on_command_sent.clear()
        self._on_command_completed.clear()
        self._shared_confirmations.value = required_confirmations
        self._shared_command.value = command

        if await_sending and not await_completion:
            self._on_command_sent.wait()

        if await_completion:
            self._on_command_completed.wait(timeout=await_completion_timeout)

    def go(self, distance: int):
        print(f"Going {distance}")
        self.send_command(f"F{distance * 10}", await_completion=True, required_confirmations=1)

    def rotate(self, degrees: int):
        print(f"Rotating: {degrees}")
        if abs(degrees) == 90:
            degrees = math.copysign(101, degrees)

        if abs(degrees) == 180:
            degrees = math.copysign(185, degrees)

        self.send_command(f"R{degrees}", await_completion=True, required_confirmations=1)

    def reset_position(self):
        self.send_command("N")

    def close_grabber(self):
        self.send_command("H0", await_completion=True, required_confirmations=2)

    def open_grabber(self):
        self.send_command("H2", await_completion=True, required_confirmations=2)

    def release(self):
        self.reset_position()
        self._on_releasing.set()


if __name__ == "__main__":
    robot = BTRobot("COM10")

    for i in range(8):
        robot.rotate(180)

    robot.release()
