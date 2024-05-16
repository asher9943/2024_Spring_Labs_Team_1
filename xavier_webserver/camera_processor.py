import cv2
import numpy as np
import imutils

# https://medium.com/@sardorabdirayimov/colors-detection-using-masks-contours-in-opencv-72d127f0797e

# may need to fine tune these for our camera(s)
COLORS = {
    "blue": [np.array([90, 175, 20]), np.array([130, 255, 255])],
    "red": [np.array([160, 165, 20]), np.array([180, 255, 255])],
    "green": [np.array([35, 40, 20]), np.array([70, 255, 255])],
}

# For documentation: Height: 480, width: 640
# Area threshold avoids noise
THRESHOLD = 1000

# Bounding box constants
BOX_START = (250, 150)
BOX_END = (400, 400)


def is_block():
    cap = cv2.VideoCapture(0)

    # if inconsistent run this 5 times or something
    ret, image = cap.read()

    # colorspace correction
    image = cv2.cvtColor(image, cv2.COLOR_BGR2HSV)

    # check if there is a colored box for each of them
    for color in COLORS:
        # a binary image with only that color as white
        mask = cv2.inRange(image, COLORS[color][0], COLORS[color][1])

        # contours based on that binary image
        cnts, heirarchy = cv2.findContours(mask, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)

        # trim the contours to only be those greater than threshold area
        cnts_filt_area = [cnt for cnt in cnts if cv2.contourArea(cnt) > THRESHOLD]

        # also trim the contours to only be those inside bounding box
        cnts_filt_pos = []

        for cnt in cnts_filt_area:
            M = cv2.moments(cnt)

            cx = int(M["m10"] / M["m00"])
            cy = int(M["m01"] / M["m00"])

            if (
                cx > BOX_START[0]
                and cx < BOX_END[0]
                and cy > BOX_START[1]
                and cy < BOX_END[1]
            ):
                cnts_filt_pos.append(cnt)

        if len(cnts_filt_pos) > 0:
            return b"Block present"

    return b"Block absent"
