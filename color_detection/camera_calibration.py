import cv2
import numpy as np
import imutils

# https://medium.com/@sardorabdirayimov/colors-detection-using-masks-contours-in-opencv-72d127f0797e

THRESHOLD = 3000

colors = {
    "blue": [np.array([90, 175, 20]), np.array([130, 255, 255])],
    "red": [np.array([160, 165, 20]), np.array([180, 255, 255])],
    "green": [np.array([35, 80, 20]), np.array([70, 255, 255])],
}


# To be used for calibrating color ranges
def show_mask(frame, points):
    return cv2.inRange(frame, points[0], points[1])  # create mask with boundaries


# To be used for calibrating area theshold
def show_contours(frame, points):
    mask = show_mask(frame, points)

    cnts, heirarchy = cv2.findContours(mask, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)

    cnts = [cnt for cnt in cnts if cv2.contourArea(cnt) > THRESHOLD]

    mask = cv2.cvtColor(mask, cv2.COLOR_GRAY2BGR)

    return cv2.drawContours(mask, cnts, -1, (0, 255, 0), -1)


def main():
    cap = cv2.VideoCapture(0)

    while cap.isOpened():
        ret, image = cap.read()

        # cv2.imshow(
        #     "Masked img",
        #     show_mask(cv2.cvtColor(image, cv2.COLOR_BGR2HSV), colors["green"]),
        # )

        cv2.imshow(
            "Contour filtered img",
            show_contours(cv2.cvtColor(image, cv2.COLOR_BGR2HSV), colors["green"]),
        )

        cv2.waitKey(25)


if __name__ == "__main__":
    main()
