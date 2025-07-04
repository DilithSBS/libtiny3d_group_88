from matplotlib import pyplot as plt
import numpy as np

# Read the PGM file
img = np.loadtxt("cube_frames/frame_90.pgm", skiprows=4)
plt.imshow(img, cmap='gray')
plt.show()

