import cv2 as cv

img = cv.imread("faces.jpg")
gray_img = cv.cvtColor(img, cv.COLOR_BGR2GRAY)
edge_img = cv.Canny(gray_img, 100, 200)

haar_cascade = cv.CascadeClassifier("haarcascade_frontalface_default.xml")
faces_rect = haar_cascade.detectMultiScale(gray_img, 1.1, 9)
for x, y, w, h in faces_rect:
    cv.rectangle(img, (x, y), (x + w, y + h), (0, 255, 0), 2)


cv.imshow("Img", img)
cv.imshow("Gray Img", gray_img)
cv.imshow("Edge Img", edge_img)

cv.waitKey(0)
cv.destroyAllWindows()
