# RPI OS
## Bluetooth и Serial порт

На роботе отключен BT для лучшего функционирования Serial порта в GPIO (https://www.abelectronics.co.uk/kb/article/1035/serial-port-setup-in-raspberry-pi-os, раздел "Notes for the Raspberry Pi 3 Model B, B+, 4 and Raspberry Pi Zero W")

Для включения:
- `sudo nano /boot/firmware/config.txt`
- удалить в конце `dtoverlay=disable-bt` и сохранить
- `sudo systemctl enable hciuart`
- `sudo reboot`

Serial port GPIO: `/dev/ttyAMA0`<br>
Serial port USB: `/dev/ttyUSB0`<br>
List ports: `python -m serial.tools.list_ports`<br>
Mini-terminal: `python -m serial.tools.miniterm <port>`