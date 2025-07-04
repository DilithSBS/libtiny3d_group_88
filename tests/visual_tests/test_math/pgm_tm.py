from matplotlib import pyplot as plt
import numpy as np
from PIL import Image

filename = "frame_30_0_60"

# # Read the PGM file
# img = np.loadtxt(f"{filename}.pgm", skiprows=4)
# plt.imshow(img, cmap='gray')
# plt.show()


def convert_pgm_to_png(pgm_path, png_path):
    # Open the PGM image
    with Image.open(pgm_path) as img:
        # Ensure it's in grayscale mode
        img = img.convert('L')
        # Save it as PNG
        img.save(png_path)
        print(f"Converted {pgm_path} to {png_path}")

# Example usage
convert_pgm_to_png(f'{filename}.pgm', f'{filename}.png')
