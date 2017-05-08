using ZenFab
using SerialPorts

f = open("test.gcode")
s = SerialPort("/dev/ttyUSB0", 115200)

ZenFab.serialsend(s, f)
