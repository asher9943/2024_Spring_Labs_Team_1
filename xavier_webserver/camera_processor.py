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

    while cap.isOpened():
        ret, image = cap.read()
