#include <iostream>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

// Declarations
std::vector<std::vector<int>> findColour(cv::Mat img);
void drawOnCanvas(std::vector<std::vector<int>> newPoints);
cv::Point getContours(cv::Mat img);
int main();


cv::Mat img, flipped;

std::vector<std::vector<int>> newPoints;
std::vector<std::vector<int>> MyColours{ {50, 50, 25, 150, 200, 255}, 
										 {165, 77, 39, 172, 255, 255},
										 {34, 38, 11, 83, 166, 255} }; // hmin, smin, vmin, hmax, smax, vmax
std::vector<cv::Scalar> ColourValues{ {255, 0, 0}, 
								      {0, 0, 0},
									  {0, 255, 0} }; // BGR colour values

// Functions

cv::Point getContours(cv::Mat imgDial) {
	std::vector<std::vector<cv::Point>> contours;
	std::vector<cv::Vec4i> hiearchy;

	cv::findContours(imgDial, contours, hiearchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

	std::vector<std::vector<cv::Point>> conPoly(contours.size());
	std::vector<cv::Rect> boundRect(contours.size());

	cv::Point myPoint(0, 0);

	for (int i = 0; i < contours.size(); i++) {

		int area = cv::contourArea(contours[i]);
		std::cout << area << std::endl;

		if (area > 1000) {

			float peri = cv::arcLength(contours[i], true);
			cv::approxPolyDP(contours[i], conPoly[i], 0.02 * peri, true);

			std::cout << conPoly[i].size() << std::endl;

			boundRect[i] = cv::boundingRect(conPoly[i]);
			
			myPoint.x = boundRect[i].x + boundRect[i].width / 2; // Finds the center point of the top 
			myPoint.y = boundRect[i].y; // Finds the y point for the marker

			cv::drawContours(flipped, conPoly, i, cv::Scalar(255, 0, 255), 2);
		}
	}

	return myPoint;
}

// Finds the color of the marker
std::vector<std::vector<int>> findColour(cv::Mat img) {

	cv::Mat imgHSV, mask;

	cv::cvtColor(img, imgHSV, cv::COLOR_BGR2HSV);
	
	for (int i{ 0 }; i < MyColours.size(); i++) {
		cv::Scalar lower(MyColours[i][0], MyColours[i][1], MyColours[i][2]);
		cv::Scalar upper(MyColours[i][3], MyColours[i][4], MyColours[i][5]);
		cv::inRange(imgHSV, lower, upper, mask);

		cv::imshow("Mask", mask);

		cv::Point myPoint{ getContours(mask) };

		if (myPoint.x != 0 && myPoint.y != 0) {
			newPoints.push_back({ myPoint.x, myPoint.y, i });
		}
	}

	return newPoints;
}

void drawOnCanvas(std::vector<std::vector<int>> newPoints, std::vector<cv::Scalar> ColourValues) {

	for (int i{ 0 }; i < newPoints.size(); i++) {
		cv::circle(flipped, cv::Point(newPoints[i][0], newPoints[i][1]), 10, ColourValues[newPoints[i][2]], cv::FILLED);
	}
}

int main() {

	cv::VideoCapture cap(0);

	while (true) {
		cap.read(img);
		cv::flip(img, flipped, 1); // Flips the webcam

		// Functions
		newPoints = findColour(flipped);
		drawOnCanvas(newPoints, ColourValues);

		cv::imshow("Image", flipped);
		cv::waitKey(1);
	}

	return 0;

}