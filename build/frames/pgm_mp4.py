import imageio.v2 as imageio
import glob

with imageio.get_writer("output.mp4", fps=20) as writer:
    for filename in sorted(glob.glob("build/frames/frame_*.pgm")):
        image = imageio.imread(filename)
        writer.append_data(image)
