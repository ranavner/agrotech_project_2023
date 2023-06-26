# Agrotech Project - 2023

In our agrotech project we have decided to make a smart watering system.
We seperated our 'grass field' into 4 areas, each one is controlled by it's own humidity sensor and a valve.
Furthermore, we added a camera that takes a photo of the whole field and sends it to the cloud.
Also, a motion sensor is located above the crops so it can notify the user of any movements that occures in the area.

All the data is sent real-time into a streamlit app that can be accessed from all over the world.
## The app includes: 
1. Humidity values
2. Valve status (open or close)
3. Temperture
4. VPD 
5. Motion alert
6. Photo of the field (5 minutes intervals)
7. Analyzed photo (showing yellow areas that may require special attention)
8. Full raw data for self user analysis

## Dashboard presentation
!['alt text'](/images/for_readme/GUI1.png)

The app platform was created using the Streamlit library, full code can be found in the code/streamlit_app.py

## Full system
!['alt text'](/images/for_readme/IMG_6625.jpg)

The self irrigation system is opperated by one ESP32, it is connected to 4 moisture sensors and 4 valves, and 1 sensor + RH sensor.
Full code can be found in [some label](code/irrigation_esp.ino)

## Moisture sensors

!['alt text'](/images/for_readme/IMG_6624.jpg)

