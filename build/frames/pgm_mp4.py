from matplotlib import pyplot as plt
import numpy as np

# Read the PGM file
for i in range(10):
    img = np.loadtxt(f"frame_00{i}.pgm", skiprows=3)
    plt.imshow(img, cmap='gray')
    plt.show()

for i in range(10,60):
    img = np.loadtxt(f"frame_0{i}.pgm", skiprows=3)
    plt.imshow(img, cmap='gray')
    plt.show()