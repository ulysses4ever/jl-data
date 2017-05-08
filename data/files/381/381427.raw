using PyCall

@pyimport serial

s = serial.Serial("/dev/ttyACM1", 250000)
s[:flushOutput]()
s[:flushInput]()
s[:setDTR](0)
sleep(1)
s[:setDTR](1)
sleep(2)
s[:write]("G91\n")
s[:write]("G1 X100 F1000\n")
