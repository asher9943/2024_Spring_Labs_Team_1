import cv2 


#------------------------[Part 1]------------------------#

# Load the input image 
imageO = cv2.imread('/home/paint/Documents/School/asdasd/2024_Spring_Labs_Team_1_DonaldFork/Tutorial_2/young_man_portrait_beard_young_man_male_handsome_young_man_handsome-1046502-728629612.jpg') 
cv2.imshow('Original', imageO) 
cv2.waitKey(0) 
  
# Use the cvtColor() function to grayscale the image 
gray_image = cv2.cvtColor(imageO, cv2.COLOR_BGR2GRAY) 
  
cv2.imshow('Grayscale', gray_image) 
cv2.waitKey(0)   


#------------------------[Part 2]------------------------#
# Display Sobel Edge Detection Images
edges = cv2.Canny(image=imageO, threshold1=100, threshold2=180)

cv2.imshow('Sobel XY', edges)
cv2.waitKey(0)


# Window shown waits for any key pressing event 
cv2.destroyAllWindows()


#------------------------[Part 3]------------------------#
image_path = "/home/paint/Documents/School/asdasd/2024_Spring_Labs_Team_1_DonaldFork/Tutorial_2/young_man_portrait_beard_young_man_male_handsome_young_man_handsome-1046502-728629612.jpg"
window_name = f"Detected Objects in {image_path}"
original_image = cv2.imread(image_path)

# Convert the image to grayscale for easier computation
image_grey = cv2.cvtColor(original_image, cv2.COLOR_RGB2GRAY)

cascade_classifier = cv2.CascadeClassifier(
    f"{cv2.data.haarcascades}haarcascade_eye.xml")

face_classifier = cv2.CascadeClassifier(
    f"{cv2.data.haarcascades}haarcascade_frontalface_alt.xml")

detected_objects = cascade_classifier.detectMultiScale(image_grey, minSize=(50, 50))
detected_face = face_classifier.detectMultiScale(image_grey, minSize=(50, 50))

# Draw rectangles on the detected objects
if len(detected_objects) != 0:
    for (x, y, width, height) in detected_objects:
        cv2.rectangle(original_image, (x, y),
                      (x + height, y + width),
                      (0, 255, 0), 2)

if len(detected_face) != 0:
    for (x, y, width, height) in detected_face:
        cv2.rectangle(original_image, (x, y),
                      (x + height, y + width),
                      (255, 0, 0), 2)

cv2.namedWindow(window_name, cv2.WINDOW_KEEPRATIO)
cv2.imshow(window_name, original_image)
cv2.resizeWindow(window_name, 400, 400)
cv2.waitKey(0)
cv2.destroyAllWindows()