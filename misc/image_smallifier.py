from PIL import Image

def triple_image_size(image_path: str, output_path: str, position: str = "center"): #center, bottom
	# Load the image
	original_image = Image.open(image_path).convert("RGBA")
	original_width, original_height = original_image.size

	# Calculate new dimensions
	new_width = original_width * 3
	new_height = original_height * 3

	# Create a new image with the new dimensions and a transparent background
	new_image = Image.new("RGBA", (new_width, new_height), (255, 255, 255, 0))

	# Calculate the position to paste the original image
	if position == "center":
		paste_position = ((new_width - original_width) // 2, (new_height - original_height) // 2)
	elif position == "bottom":
		paste_position = ((new_width - original_width) // 2, new_height - original_height)

	# Paste the original image into the new image
	new_image.paste(original_image, paste_position, original_image)

	# Save the new image
	new_image.save(output_path)

# Example usage
triple_image_size("water.png", "water_floor.png", position="bottom")
