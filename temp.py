import cv2
import numpy as np
cap = cv2.VideoCapture(0)
# Createsomerandomcolors
color = np.random.randint(0, 255, (100, 3))
n = 1
while n<30:
    ret, prev_frame = cap.read()
    n=n+1
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
    a = (bottom_right[0]+top_left[0])/2
    b = (bottom_right[1]+top_left[1])/2
    #print("coordinates",a,b)
    cv2.imshow("img", frame)
    #cv2.waitKey(10)
    if cv2.waitKey(1) & 0xff == ord('q'):
        break

cap.release()
cv2.destroyAllWindows()