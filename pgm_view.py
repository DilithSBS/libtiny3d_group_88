from matplotlib import pyplot as plt
import numpy as np

# Read the PGM file
img = np.loadtxt("output.pgm", skiprows=3)
plt.imshow(img, cmap='gray')
plt.show()
