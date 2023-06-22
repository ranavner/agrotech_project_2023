import gdown
import time
import subprocess

def download_image_repository_from_drive():
    url = "https://drive.google.com/drive/folders/1Ct5QfEFchW4f0ejEFRlJ4ahySA_rOqvj?usp=sharing"
    gdown.download_folder(url,output='image/', quiet=True, use_cookies=False)

def analyze_image():
    subprocess.Popen(["python", "image_color_seperation.py"])


def main():
    download_image_repository_from_drive()
    analyze_image()
    time.sleep(600)

if __name__ == "__main__":
    main()