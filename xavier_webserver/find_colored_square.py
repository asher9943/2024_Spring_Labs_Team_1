import cv2
import numpy as np
import imutils

# https://medium.com/@sardorabdirayimov/colors-detection-using-masks-contours-in-opencv-72d127f0797e

color = (255, 255, 255)
# I have defined lower and upper boundaries for each color for my camera
# Strongly recommended finding for your own camera.
colors = {
    "blue": [np.array([95, 255, 85]), np.array([120, 255, 255])],
    "red": [np.array([161, 165, 127]), np.array([178, 255, 255])],
    "yellow": [np.array([16, 0, 99]), np.array([39, 255, 255])],
    "green": [np.array([33, 19, 105]), np.array([77, 255, 255])],
}


def is_colored_region(frame, points):
    mask = cv2.inRange(frame, points[0], points[1])  # create mask with boundaries
    cnts = cv2.findContours(
        mask, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE
    )  # find contours from mask
    cnts = imutils.grab_contours(cnts)
    for c in cnts:
        area = cv2.contourArea(c)  # find how big countour is
        if area > 5000:
            return True

    return False


def main():
    image = cv2.imread("nothing.jpg")

    print(is_colored_region(cv2.cvtColor(image, cv2.COLOR_BGR2HSV), colors["red"]))

    image = cv2.imread("something.jpg")

    print(is_colored_region(cv2.cvtColor(image, cv2.COLOR_BGR2HSV), colors["red"]))


if __name__ == "__main__":
    main()
