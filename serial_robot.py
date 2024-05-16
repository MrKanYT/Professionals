import serial
from serial.serialutil import SerialException

import time
import math

import multiprocessing
from multiprocessing.managers import SharedMemoryManager
from multiprocessing.shared_memory import ShareableList
from multiprocessing import Value, Manager, Event
import ctypes


class SerialRobot:

    _telemetry_len: int

    _shared_memory_manager: Manager
    _shared_telemetry: ShareableList
    _shared_command: Value
    _shared_confirmations: Value

    _on_serial_ready: Event
    _on_command_sent: Event
    _on_command_completed: Event
    _on_releasing: Event
    _on_telemetry_updated: Event

    _serial_io: multiprocessing.Process

    _watcher: multiprocessing.Process
    _watcher_emergency_stop_distance: Value

    def __init__(self, port):
        self._telemetry_len = 7
        self._speed = 24.7436

        self._shared_memory_manager = Manager()
        self._shared_telemetry = ShareableList([0] * self._telemetry_len)
        self._shared_command = self._shared_memory_manager.Value(ctypes.c_char_p, "")
        self._shared_confirmations = self._shared_memory_manager.Value(ctypes.c_uint8, 1)

        self._on_serial_ready = Event()
        self._on_command_sent = Event()
        self._on_command_completed = Event()
        self._on_releasing = Event()
        self._on_telemetry_updated = Event()

        self._serial_io = multiprocessing.Process(target=SerialRobot.serial_io, args=(
            port,
            self._shared_telemetry,
            self._shared_command,
            self._shared_confirmations,
            self._on_serial_ready,
            self._on_command_sent,
            self._on_command_completed,
            self._on_releasing,
            self._on_telemetry_updated))

        self._serial_io.start()

        self._on_serial_ready.wait()

        self._watcher_status = self._shared_memory_manager.Value(ctypes.c_uint8, 0)
        self._watcher_left_correct_min = self._shared_memory_manager.Value(ctypes.c_uint16, 0)
        self._watcher_left_correct_max = self._shared_memory_manager.Value(ctypes.c_uint16, 0)
        self._watcher_target_distance = self._shared_memory_manager.Value(ctypes.c_uint16, 0)
        self._watcher_command = self._shared_memory_manager.Value(ctypes.c_char_p, "")

        self._watcher = multiprocessing.Process(target=SerialRobot.watcher, args=(
            self._speed,
            self._on_releasing,
            self._on_telemetry_updated,
            self._on_command_completed,
            self._on_command_sent,
            self._shared_telemetry,
            self._shared_command,
            self._shared_confirmations,
            self._watcher_status,
            self._watcher_left_correct_min,
            self._watcher_left_correct_max,
            self._watcher_target_distance,
            self._watcher_command
        ))
        #self._watcher.start()

        print("Serial robot is ready")

    @staticmethod
    def serial_io(port: str,
                  shared_telemetry: ShareableList,
                  shared_command: Value,
                  shared_confirmations: Value,
                  on_serial_ready: Event,
                  on_command_sent: Event,
                  on_command_completed: Event,
                  on_releasing: Event,
                  on_telemetry_updated: Event):
        trying = 3
        while trying > 0:
            try:
                ser = serial.Serial(port, 115200, timeout=5)
                break
            except SerialException:
                print("Connecting to serial failed")
            time.sleep(2)
            trying -= 1

        if trying <= 0:
            print("Failed to connect to serial")
            return

        on_serial_ready.set()
        confirmations_left = shared_confirmations.value
        while ser.is_open:
            try:
                bdata = ser.readline()
                data = bdata.decode().strip()

                #print(f"SERIAL >>> {data}")

                if on_releasing.is_set():
                    break

                if data == "OK":
                    confirmations_left -= 1
                    #print(f"SERIAL CONFIRMED >>> {confirmations_left} LEFT")
                    if confirmations_left <= 0:
                        on_command_completed.set()
                        shared_confirmations.value = 1
                else:
                    splitted = data.split(" ")
                    if any(splitted):
                        bad_packet = False
                        for i in range(len(splitted)):
                            if splitted[i].isdigit():
                                shared_telemetry[i] = int(splitted[i])
                            else:
                                bad_packet = True
                                break
                        if not bad_packet:
                            on_telemetry_updated.set()

                if shared_command.value:
                    print(f"SEND SERIAL >>> {shared_command.value}")
                    ser.write(shared_command.value.encode("ascii"))
                    #print(f"SET CONFIRMATIONS: {shared_confirmations.value}")
                    confirmations_left = shared_confirmations.value
                    shared_command.value = ""
                    on_command_sent.set()
            except KeyboardInterrupt:
                break

        ser.close()

    @staticmethod
    def watcher(
            speed: float,
            on_releasing: Event,
            on_telemetry_updated: Event,
            on_command_completed: Event,
            on_command_sent: Event,
            telemetry: ShareableList,
            shared_command: Value,
            shared_confirms: Value,
            status: Value,
            left_correct_min: Value,
            left_correct_max: Value,
            target_distance: Value,
            last_command: Value,
    ):

        is_correcting = False
        left_distance_buffer = []
        left_distance_history = []
        previous_speed_correction = 0
        block_correcting = False

        while not on_releasing.is_set():
            on_telemetry_updated.wait()
            on_telemetry_updated.clear()

            t = time.time()

            is_correcting = status.value == 0 and (left_correct_min.value != 0 or left_correct_max.value != 0)
            if not is_correcting:
                left_distance_buffer.clear()
                left_distance_history.clear()
                previous_speed_correction = 0
            
            if is_correcting:
                left_distance_buffer.append(telemetry[1])
                if len(left_distance_buffer) > 6:
                    del left_distance_buffer[0]

                if len(left_distance_buffer) >= 6:
                    average_left_distance = sum(left_distance_buffer) / len(left_distance_buffer)
                    left_distance_history.append(average_left_distance)

                    if average_left_distance > 40 and previous_speed_correction != 0:
                        on_command_sent.clear()
                        shared_command.value = f"J0"
                        on_command_sent.wait()
                        previous_speed_correction = 0
                    else:

                        if len(left_distance_history) > 10:
                            del left_distance_history[0]

                            sign = 1 if left_distance_history[-1] - left_distance_history[0] > 0 else -1
                            delta = abs(left_distance_history[-1] - left_distance_history[0])
                            speed_correction = 0

                            if delta > 1.5:
                                speed_correction = 20
                            elif delta > 0.8:
                                speed_correction = 10

                            speed_correction *= sign

                            if speed_correction != previous_speed_correction:
                                on_command_sent.clear()
                                shared_command.value = f"V{speed_correction}"
                                on_command_sent.wait()
                            previous_speed_correction = speed_correction

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
                     await_completion_timeout: float = 20,
                     required_confirmations: int = 1):
        self._on_command_sent.clear()
        self._on_command_completed.clear()
        self._shared_confirmations.value = required_confirmations
        self._shared_command.value = command

        if await_sending and not await_completion:
            self._on_command_sent.wait()

        if await_completion:
            self._on_command_completed.wait(timeout=await_completion_timeout)

    def go(self, distance: int, correct: bool = False, *args, wall_distance: int = 0):
        print(f"Going {distance if wall_distance == 0 else 'to wall ' + str(wall_distance)} {'(correction)' if correct else ''}")

        if wall_distance == 0:
            cmd = f"F{distance * 10}"
        else:
            cmd = f"W{wall_distance * 10}"

        if correct:
            self._watcher_left_correct_min.value = -5
            self._watcher_left_correct_max.value = 5
            self._watcher_target_distance.value = distance
            self._watcher_command.value = cmd

        self.send_command(cmd, await_completion=True, required_confirmations=1)

        while self._watcher_status.value == 2:
            self._on_command_completed.wait()

        self._watcher_left_correct_min.value = 0
        self._watcher_left_correct_max.value = 0
        self._watcher_target_distance.value = 0

        if wall_distance > 0 and self.forward_distance - wall_distance > 10:
            self.go(distance, correct=correct, wall_distance=wall_distance)

    def rotate(self, degrees: int, wait: bool = True):
        print(f"Rotating: {degrees}")

        self.send_command(f"R{degrees}", await_completion=wait, required_confirmations=1)

    def reset_position(self):
        self.send_command("N")

    def close_grabber(self):
        self.send_command("H2", await_completion=False, required_confirmations=1)
        time.sleep(4)

    def open_grabber(self):
        self.send_command("H0", await_completion=False, required_confirmations=1)
        time.sleep(4)

    def set_red_led(self, status: bool):
        self.send_command(f"G{int(status)}")

    def set_green_led(self, status: bool):
        self.send_command(f"L{int(status)}")

    def set_led_freq(self, millis: int):
        self.send_command(f"Q{millis}")

    def set_servo_angle(self, degrees: int):
        self.send_command(f"S{degrees}", await_completion=True)

    def release(self):
        self.set_servo_angle(129)
        self.reset_position()
        self._on_releasing.set()


if __name__ == "__main__":
    robot = SerialRobot("/dev/ttyUSB0")

    while True:
        print(robot.forward_distance)

    robot.release()
