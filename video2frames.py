#!/usr/bin/env python3
"""
This Python script will convert a .MP4 file into a C Header file of RGB565 frames to use with a TFT Display
How to use:Open terminal->Type ->python video2frames.py input.mp4 [width] [height] [fps]
Example: python video2frames.py clip.mp4 128 128 10
Prerequisite:  ffmpeg on PATH, and `pip install numpy`
Output: frames.h  (drop it next to the .ino sketch)
"""
import subprocess
import sys

import numpy as np

src = sys.argv[1]
W = int(sys.argv[2]) if len(sys.argv) > 2 else 128
H = int(sys.argv[3]) if len(sys.argv) > 3 else 128
FPS = int(sys.argv[4]) if len(sys.argv) > 4 else 10

# One ffmpeg call: resample fps, resize (keep aspect, letterbox), emit raw RGB565
vf = (f"fps={FPS},scale={W}:{H}:force_original_aspect_ratio=decrease,"
      f"pad={W}:{H}:(ow-iw)/2:(oh-ih)/2:black")
cmd = ["ffmpeg", "-v", "error", "-i", src, "-vf", vf,
       "-pix_fmt", "rgb565le", "-f", "rawvideo", "-"]
raw = subprocess.run(cmd, capture_output=True, check=True).stdout

px = np.frombuffer(raw, dtype="<u2")
n = len(px) // (W * H)
px = px[: n * W * H].reshape(n, W * H)

with open("frames.h", "w") as f:
    f.write("#pragma once\n#include <Arduino.h>\n")
    f.write(f"#define FRAME_W {W}\n#define FRAME_H {H}\n")
    f.write(f"#define FRAME_COUNT {n}\n#define FRAME_FPS {FPS}\n")
    f.write("const uint16_t frames[FRAME_COUNT][FRAME_W * FRAME_H] PROGMEM = {\n")
    for frame in px:
        f.write("{" + ",".join(f"0x{v:04X}" for v in frame) + "},\n")
    f.write("};\n")

kb = n * W * H * 2 / 1024
print(f"{n} frames, {W}x{H}, {kb:.0f} KB of flash (ESP32 usually has ~1.3 MB free for data in the default partition)")
