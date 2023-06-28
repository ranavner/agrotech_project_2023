import gdown
import time
import subprocess

def download_image_repository_from_drive():
    url = "https://drive.google.com/drive/folders/1Ct5QfEFchW4f0ejEFRlJ4ahySA_rOqvj?usp=sharing"
    gdown.download_folder(url,output='images/', quiet=True, use_cookies=False, remaining_ok=True)

def analyze_image():
    subprocess.Popen(["python", "code/image_color_seperation.py"])

def create_timelapse():
    subprocess.Popen(["python", "code/timelapse_generator.py"])


def main():
    while True:
        download_image_repository_from_drive()
        analyze_image()
        create_timelapse()
        time.sleep(300)

if __name__ == "__main__":
    main()