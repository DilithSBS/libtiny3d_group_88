import imageio.v2 as imageio
import glob

filenames = sorted(glob.glob("frames/frame_*.pgm"))
with imageio.get_writer("frames/rotation.gif", mode="I", fps=10) as writer:
    for file in filenames:
        img = imageio.imread(file)
        writer.append_data(img)
