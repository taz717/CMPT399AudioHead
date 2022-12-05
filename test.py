import serial
import time

ser = serial.Serial("COM3", 9600, timeout=1)

ser.write(b"f")

time.sleep(5)

ser.write(b"p")

time.sleep(1)
# ser.write(b"b")

# ser.write(b"l")

# ser.write(b"r")

# ser.write(b"s")

# ser.write(b"p")

# ser.write(b"x")
