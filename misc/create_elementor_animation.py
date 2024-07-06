from PIL import Image

def create_color_shift_image(width, height, offset):
    image = Image.new("RGB", (width, height))
    pixels = image.load()
    
    # Define colors
    colors = [(255, 0, 0), (0, 255, 0), (0, 0, 255)]  # Red, Green, Blue
    
    # Calculate segment width
    segment_width = width // 3
    
    # Assign colors to the first row with the given offset
    for x in range(width):
        color_index = (x // segment_width + offset) % 3
        pixels[x, 0] = colors[color_index % len(colors)]
    
    # Fill the rest of the rows with shifted colors
    for y in range(1, height):
        for x in range(width):
            pixels[x, y] = pixels[(x + 1) % width, y - 1]
    
    return image

def save_images_for_animation(width, height, directory="frames"):
    import os
    
    # Create directory if it doesn't exist
    if not os.path.exists(directory):
        os.makedirs(directory)
    
    # Generate and save each frame
    for offset in range(width):
        image = create_color_shift_image(width, height, offset)
        image.save(f"{directory}/frame_{offset:03d}.png")

save_images_for_animation(29, 29, "animation")
