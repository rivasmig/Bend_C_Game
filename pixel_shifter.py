import sys
import random
import json

def generate_blue_noise(width, height):
    """Generate a random noise array with shades of blue."""
    pixels = []
    for _ in range(width * height):
        r = 0
        g = 0
        b = random.randint(100, 255)  # Shades of blue
        pixels.append((r, g, b))
    return pixels

def shift_pixels(pixels):
    """Shift pixels to the right, wrapping around."""
    if pixels:
        last_pixel = pixels.pop()
        pixels.insert(0, last_pixel)
    return pixels

def main():
    if len(sys.argv) != 5:
        print("Usage: python pixel_shifter.py <width> <height> <frame_count> <gpu_type>")
        return

    width = int(sys.argv[1])
    height = int(sys.argv[2])
    frame_count = int(sys.argv[3])
    gpu_type = sys.argv[4]

    # Initialize or shift pixels
    if frame_count == 0:
        pixels = generate_blue_noise(width, height)
    else:
        with open('pixels.json', 'r') as file:
            pixels = json.load(file)
        pixels = shift_pixels(pixels)

    # Save the current pixel state for the next frame
    with open('pixels.json', 'w') as file:
        json.dump(pixels, file)

    # Output the pixel array
    for r, g, b in pixels:
        print(f"{r} {g} {b}")

if __name__ == "__main__":
    main()
