import numpy as np
import cv2 as cv

cap = cv.VideoCapture(0)
haar_cascade = cv.CascadeClassifier('Haarcascade_frontalface_default.xml') 

if not cap.isOpened():
    print("Cannot open camera")
    exit()

while True:
    # Capture frame-by-frame
    ret, frame = cap.read()

    # if frame is read correctly ret is True
    if not ret:
        print("Can't receive frame (stream end?). Exiting ...")
        break

    flip = cv.flip(frame, 1)
    faces_rect = haar_cascade.detectMultiScale(flip, 1.1, 9) 
  
    # Iterating through rectangles of detected faces 
    for (x, y, w, h) in faces_rect: 
        cv.rectangle(flip, (x, y), (x+w, y+h), (0, 255, 0), 2)

    # Display the resulting frame
    cv.imshow('frame', flip)
    if cv.waitKey(1) == ord('q'):
        break

# When everything done, release the capture
cap.release()
cv.destroyAllWindows()

