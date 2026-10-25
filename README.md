<h3>Processing the video file</h3>
1) Open a CMD terminal and set the current directory as the directory with the video2frames.py file and your video file.
2) Run the following command <b>python video2frames.py video.mp4 width length fps</b> 
Here video.mp4 is the name of your video file, width and length are your display's specifications and fps is the number of frames per second(I have kept 2 as more frames means more memory used)
<h3>Displaying the video on the display</h3>
The previous command line command will generate a file "frames.h" in the same directory. Move the file to the directory with "plyaer.ino" and run it.
You may need to modify the INITR parameter(commented in code) and you may rotate the video as per your liking (also in code)
<b>ENJOY!!</b>
