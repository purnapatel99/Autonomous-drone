import serial
import cv2
import numpy as np

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
    elif value == 'track': #object tracking loop

        cap = cv2.VideoCapture(0)
        # Createsomerandomcolors
        color = np.random.randint(0, 255, (100, 3))
        n = 1
        while n < 30:
            ret, prev_frame = cap.read()
            n = n + 1
        roi = cv2.selectROI(windowName="ROI", img=prev_frame, showCrosshair=True, fromCenter=False)
        x, y, w, h = roi
        prev_frame = prev_frame[y:y + h, x:x + w]
        cv2.destroyAllWindows()

        while True:
            ret, old_frame = cap.read()
            frame = old_frame
            res = cv2.matchTemplate(frame, prev_frame, cv2.TM_SQDIFF)
            min_val, max_val, min_loc, max_loc = cv2.minMaxLoc(res)
            top_left = min_loc
            bottom_right = (top_left[0] + w, top_left[1] + h)
            cv2.rectangle(frame, top_left, bottom_right, (0, 0, 225), 2)
            # print(np.shape(frame))
            mx = (bottom_right[0] + top_left[0]) / 2
            my = (bottom_right[1] + top_left[1]) / 2
            if mx < 290:
                Yaw = 96
            elif mx > 350:
                Yaw = 90
            else:
                Yaw = 93
            if my < 190:
                Pitch = 95
            elif my > 290:
                Pitch = 91
            else:
                Pitch = 93
            data = str(Throttle + 1000) + str(Roll + 2000) + str(Yaw + 3000) + str(Pitch + 4000) + str(
                Aux1 + 5000) + str(Aux2 + 6000) + '\n'
            ser.write(data.encode("utf-8"))
            print(data)
            # print("coordinates", a, b)
            cv2.imshow("img", frame)
            if cv2.waitKey(1) & 0xff == ord('q'):
                break
        cap.release()
        cv2.destroyAllWindows()
        Yaw = 93
        Pitch = 93
    elif value == "end":
        break
    else:
        print("Invalid data")
    if 20 <= Throttle <= 150 and 40 <= Roll <= 150 and 40 <= Yaw <= 150 and 40 <= Pitch <= 150 and 40 <= Aux1 <= 150 and 40 <= Aux2 <= 150:
        data = str(Throttle + 1000) + str(Roll + 2000) + str(Yaw + 3000) + str(Pitch + 4000) + str(Aux1 + 5000) + str(
            Aux2 + 6000) + '\n'
    else:
        print("Value out of range:")
    ser.write(data.encode("utf-8"))
    print(data)
ser.close()
