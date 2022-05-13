import serial

Throttle = 40
Roll = 93
Yaw = 93
Pitch = 93
Aux1 = 40
Aux2 = 40
data = str(Throttle + 1000) + str(Roll + 2000) + str(Yaw + 3000) + str(Pitch + 4000) + str(Aux1 + 5000) + str(
    Aux2 + 6000) + '\n'
#ser = serial.Serial('/dev/ttyUSB0')
ser = serial.Serial()
ser.baudrate = 115200
ser.port = "COM5"
ser.open()

while True:
    print("Entre the control value:")
    value = input()
    if value == 'w':
        Throttle = Throttle + 1
    elif value == 's':
        Throttle = Throttle - 1
    elif value == 'a':
        Yaw = Yaw - 1
    elif value == 'd':
        Yaw = Yaw + 1
    elif value == 'i':
        Pitch = Pitch + 1
    elif value == 'k':
        Pitch = Pitch - 1
    elif value == 'j':
        Roll = Roll - 1
    elif value == 'l':
        Roll = Roll + 1
    elif value[0:2] == 'th':
        Throttle = int(value[2:])
    elif value[0:2] == 'ya':
        Yaw = int(value[2:])
    elif value[0:2] == 'ro':
        Roll = int(value[2:])
    elif value[0:2] == 'pi':
        Pitch = int(value[2:])
    elif value[0:2] == 'a1':
        Aux1 = int(value[2:])
    elif value[0:2] == 'a2':
        Aux2 = int(value[2:])
    elif value == 'arm':
        Throttle = 40
        Yaw = 93
        Roll = 93
        Pitch = 93
        Aux1 = 140
        Aux2 = 40
    elif value == "end":
        break
    else:
        print("Invalid data:\n")
    if 40 <= Throttle <= 150 and 40 <= Roll <= 150 and 40 <= Yaw <= 150 and 40 <= Pitch <= 150 and 40 <= Aux1 <= 150 and 40 <= Aux2 <= 150:
        data = str(Throttle + 1000) + str(Roll + 2000) + str(Yaw + 3000) + str(Pitch + 4000) + str(Aux1 + 5000) + str(
            Aux2 + 6000) + '\n'
    else:
        print("Value out of range:")
    ser.write(data.encode("utf-8"))
    print(data)
ser.close()
