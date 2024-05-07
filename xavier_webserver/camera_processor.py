import cv2
import numpy as np
import imutils

# https://medium.com/@sardorabdirayimov/colors-detection-using-masks-contours-in-opencv-72d127f0797e

# may need to fine tune these for our camera(s)
COLORS = {
    "blue": [np.array([95, 255, 85]), np.array([120, 255, 255])],
    "red": [np.array([161, 165, 127]), np.array([178, 255, 255])],
    "yellow": [np.array([16, 0, 99]), np.array([39, 255, 255])],
    "green": [np.array([33, 19, 105]), np.array([77, 255, 255])],
}

# definitely need to finetune this through map testing
AREA_THRESHOLD = 5000


def is_colored_region(camera):
    cap = cv2.VideoCapture(camera)

    frame = cv2.cvtColor(cap, cv2.COLOR_BGR2HSV)

    for color in COLORS:
        # create mask with boundaries
        mask = cv2.inRange(frame, color[0], color[1])

        # find contours from mask
        cnts = cv2.findContours(mask, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)
        cnts = imutils.grab_contours(cnts)

        for c in cnts:
            area = cv2.contourArea(c)
            if area > AREA_THRESHOLD:
                return b"true"

    return b"false"
