# Virtual-Paint
A Virtual Webcam Painter made using the OpenCV library.

## How it Works
OpenCV detects the masked object and creates contours for the object. It then places circles (the paint) at the top most and center of the marker, acting as the tip of a marker.

Colour_Grabber.cpp can detect the colour of your marker so it can be used in the virtual paint. You will need to grab the Hue, Sat, and Lum values.

Currently I am adding hand detection so that when the hand is open, the marker will paint on the screen, and when it is closed, it will stop. 
