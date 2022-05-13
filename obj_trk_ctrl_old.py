import serial
import cv2

def drawBox(img,bbox):
    x,y,w,h = int(bbox[0]),int(bbox[1]),int(bbox[2]),int(bbox[3])
    cv2.rectangle(img,(x,y),((x+w),(y+h)),(255,0,255),3,1)
    cv2.putText(img, "Tracking", (75, 75), cv2.FONT_HERSHEY_SIMPLEX, 0.7, (0, 255, 0), 2)

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
        tracker = cv2.TrackerMIL_create()
        success, img = cap.read()
        bbox = cv2.selectROI("Tracking", img, False)
        tracker.init(img, bbox)
        while True:
            timer = cv2.getTickCount()
            success, img = cap.read()
            success, bbox = tracker.update(img)
            if success:
                drawBox(img, bbox)
            else:
                cv2.putText(img, "Lost", (75, 75), cv2.FONT_HERSHEY_SIMPLEX, 0.7, (0, 0, 255), 2)

            fps = cv2.getTickFrequency() / (cv2.getTickCount() - timer)
            cv2.putText(img, str(int(fps)), (75, 50), cv2.FONT_HERSHEY_SIMPLEX, 0.7, (0, 0, 255), 2)
            cv2.imshow("tracking", img)
            mx = int(bbox[0]) + (int(bbox[2]) / 2)
            my = int(bbox[1]) + (int(bbox[3]) / 2)
            if mx < 290:
                Yaw = 96
            elif mx > 350:
                Yaw = 90
            else:
                Yaw = 93
            if my < 190:
                Pitch = 95
            elif my > 285:
                Pitch = 91
            else:
                Pitch = 93
            data = str(Throttle + 1000) + str(Roll + 2000) + str(Yaw + 3000) + str(Pitch + 4000) + str(
                Aux1 + 5000) + str(Aux2 + 6000) + '\n'
            ser.write(data.encode("utf-8"))
            print(data)
            if cv2.waitKey(1) & 0xff == ord('q'):
                break
        Yaw = 93
        Pitch = 93
    elif value == "end":
        break
    else:
        print("Invalid data:\n")
    if 20 <= Throttle <= 150 and 40 <= Roll <= 150 and 40 <= Yaw <= 150 and 40 <= Pitch <= 150 and 40 <= Aux1 <= 150 and 40 <= Aux2 <= 150:
        data = str(Throttle + 1000) + str(Roll + 2000) + str(Yaw + 3000) + str(Pitch + 4000) + str(Aux1 + 5000) + str(
            Aux2 + 6000) + '\n'
    else:
        print("Value out of range:")
    ser.write(data.encode("utf-8"))
    print(data)
ser.close()
