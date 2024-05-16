# RPI OS
## Bluetooth � Serial ����

�� ������ �������� BT ��� ������� ���������������� Serial ����� � GPIO (https://www.abelectronics.co.uk/kb/article/1035/serial-port-setup-in-raspberry-pi-os, ������ "Notes for the Raspberry Pi 3 Model B, B+, 4 and Raspberry Pi Zero W")

��� ���������:
- `sudo nano /boot/firmware/config.txt`
- ������� � ����� `dtoverlay=disable-bt` � ���������
- `sudo systemctl enable hciuart`
- `sudo reboot`

Serial port GPIO: `/dev/ttyAMA0`<br>
Serial port USB: `/dev/ttyUSB0`<br>
List ports: `python -m serial.tools.list_ports`<br>
Mini-terminal: `python -m serial.tools.miniterm <port>`