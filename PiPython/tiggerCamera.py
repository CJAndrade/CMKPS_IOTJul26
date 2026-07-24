import subprocess
import datetime

# Create a unique filename using the current timestamp
timestamp = datetime.datetime.now().strftime("%Y-%m-%d_%H-%M-%S")
image_name = f"/home/pi/Pictures/picsCarmelito/image_{timestamp}.jpg"

# Command to trigger raspistill with a 500ms delay and no preview
cmd = ["raspistill", "-o", image_name, "-t", "500", "-n"]

try:
    # Run the subprocess and wait for it to complete
    subprocess.run(cmd, check=True)
    print(f"Successfully captured image: {image_name}")
except subprocess.CalledProcessError as e:
    print(f"Error capturing image: {e}")
