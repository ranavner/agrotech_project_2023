import cv2
import numpy as np
import os
import glob
from datetime import datetime

try:
    os.mkdir('Analyzed_image/')
except:
    pass

path_to_image_directory = glob.glob('images/ESP32-CAM/*')
latest_image_directory = glob.glob(max(path_to_image_directory, key=os.path.getctime))[0]
path_to_image = glob.glob(latest_image_directory + '/*')
image_now = glob.glob(max(path_to_image, key=os.path.getctime))[0]

def detect_color_difference(image):
    # Convert the image to the HSV color space
    hsv_image = cv2.cvtColor(image, cv2.COLOR_BGR2HSV)

    # Define the color range you want to detect (here we use red as an example)
    lower_color = np.array([22, 93, 0])
    upper_color = np.array([28, 255, 255])

    # Create a mask for pixels within the color range
    mask = cv2.inRange(hsv_image, lower_color, upper_color)

    # Apply morphological operations to remove noise
    kernel = cv2.getStructuringElement(cv2.MORPH_ELLIPSE, (5, 5))
    mask = cv2.morphologyEx(mask, cv2.MORPH_OPEN, kernel)

    # Find contours of the color regions
    contours, _ = cv2.findContours(mask, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

    # Draw circles around color regions
    for contour in contours:
        (x, y), radius = cv2.minEnclosingCircle(contour)
        center = (int(x), int(y))
        radius = int(radius)
        cv2.circle(image, center, radius, (0, 0, 255), 5)

    return image

# Load the image
image_path = image_now
image = cv2.imread(image_path)

# Detect and draw circles around color regions
result = detect_color_difference(image)
# output_path = "/Analyzed_images/" + str(datetime.now()) + '.jpg'
output_path = 'Analyzed_image/' + str(datetime.now()) + '.jpg'
cv2.imwrite(output_path, result)

# Display the result
# cv2.imshow("Color Detection", result)
# cv2.waitKey(0)
# cv2.destroyAllWindows()
