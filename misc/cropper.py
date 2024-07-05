# Import necessary libraries
from PIL import Image
import os

def crop_images_in_folder(folder_path):
    # Check if the folder exists
    if not os.path.exists(folder_path):
        print("Folder does not exist.")
        return

    # Iterate over all files in the folder
    for filename in os.listdir(folder_path):
        if filename.endswith(".png"):
            # Construct the full file path
            file_path = os.path.join(folder_path, filename)
            
            try:
                # Open the image
                with Image.open(file_path) as img:
                    # Calculate dimensions to crop
                    width, height = img.size
                    left = width / 4
                    top = height / 4
                    right = width - left
                    bottom = height - top
                    
                    # Perform the crop
                    cropped_img = img.crop((left, top, right, bottom))
                    
                    # Save the cropped image back to disk
                    cropped_img.save(file_path)
                    print(f"Cropped {filename} successfully.")
            except Exception as e:
                print(f"Failed to crop {filename}: {e}")

# Example usage
folder_path = "explosion"
crop_images_in_folder(folder_path)