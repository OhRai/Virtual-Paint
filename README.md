# Virtual-Paint
A Virtual Webcam Painter made using the OpenCV library.

## How it Works
In order to use this program, you need to have the colour values of the marker (Hue, Sat, and Lum) so that the program can mask the marker.
OpenCV detects the masked object and creates contours for the object. It then places circles (the paint) at the top most and center of the marker, acting as the tip of a marker.

Currently I am adding hand detection so that when the hand is open, the marker will paint on the screen, and when it is closed, it will stop. 
