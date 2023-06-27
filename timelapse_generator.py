
import cv2
import glob
import re
import os
from datetime import datetime

img_array = []
numbers = re.compile(r"(\d+)")
path_to_image_directory = glob.glob('images/ESP32-CAM/*')
latest_image_directory = glob.glob(max(path_to_image_directory, key=os.path.getctime))[0]

def numericalSort(value):
    parts = numbers.split(value)
    parts[1::2] = map(int, parts[1::2])
    return parts

for filename in sorted(glob.glob(latest_image_directory + "/*.jpg") , key=numericalSort):
    img = cv2.imread(filename)
    height, width, layers = img.shape
    size = (width,height)
    img_array.append(img)

out = cv2.VideoWriter("videos/"+ str(datetime.now()) + ".mp4",cv2.VideoWriter_fourcc(*"DIVX"), 15, size)

for i in range(len(img_array)):
    out.write(img_array[i])

out.release()