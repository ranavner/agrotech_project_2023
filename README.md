# Agrotech Project - 2023

In our agrotech project, we have decided to make a smart watering system.
We separated our 'grass field' into 4 areas, each controlled by its own humidity sensor and a valve.
Furthermore, we added a camera that takes a photo of the whole field and sends it to the cloud, modified into a timelapse video.
Also, a motion sensor is located above the crops so it can notify the user of any movements that occur in the area.

All the data is sent in real-time into a Streamlit app that can be accessed from all over the world, transferring the data through Serveo.net.
## The app includes: 
1. Humidity values
2. Valve status (open or closed)
3. Temperature
4. VPD 
5. Motion alert
6. Photo of the field (5 minutes intervals)
7. Analyzed photo (showing yellow areas that may require special attention)
8. Timelapse video of the growth from the last day (not supported on Google Chrome operated by Macos, Safari is recommended)
9. Full raw data for self-user analysis

## Dashboard presentation
!['alt text'](/images/for_readme/GUI1.png)

The app platform was created using the Streamlit library, the full code can be found [here](code/streamlit_app.py)

## Full system
!['alt text'](/images/for_readme/IMG_6651.jpg)

The self-irrigation system is operated by one ESP32, it is connected to 4 moisture sensors and 4 valves, and 1 sensor + RH sensor.
Full code can be found in [here](code/irrigation_esp.ino)

## Camera and Motion sensor

Above the field, the camera module and the motion sensor are positioned such that they can give a 'drone-like' view of the whole growth.

!['alt text'](/images/for_readme/IMG_6638.jpg)

The camera module and the motion sensor are operated by 2 different esp, code for camera module can be found [here](code/ESP32_CAM_Send_Photo_to_Google_Drive.ino) and code for the motion sensor esp can be found [here](code/Motion_Sensor.ino)
and the timelapse creation code can be found [here](code/timelapse_generator.py)

Example video of the timelapse:
['alt text'] (videos/2023-06-28 11:24:14.591807.mp4)

## Moisture sensors

!['alt text'](/images/for_readme/IMG_6624.jpg)

