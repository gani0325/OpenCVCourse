#include <opencv2/opencv.hpp>		// OpenCV에서 지원하는 모든 기능
#include <opencv2/videoio.hpp>		// 비디오 추적 및 배경 segmentation과 관련된 루틴
#include <opencv2/imgcodecs.hpp>	// 기본 데이터 타입이 선언 (Mat 이나 Point가 선언, 행렬 연산 혹은 벡터 연산)
#include <opencv2/highgui.hpp>		// 윈도우 화면, UI처리(슬라이더, 버튼 등) 및 마우스 제어 가능
#include <iostream>
#include <stdio.h>

using namespace cv;
using namespace std;

// #6. Color Detection
Mat imgHSV, mask;
int hmin = 0, smin = 110, vmin = 153;
int hmax = 19, smax = 240, vmax = 255;

void main() {

	string path = "Resources/shapes.png";
	Mat img = imread(path);

	cvtColor(img, imgHSV, COLOR_BGR2HSV);

	namedWindow("Trackbars", (640, 200));
	createTrackbar("Hue Min", "Trackbars", &hmin, 179);
	createTrackbar("Hue Max", "Trackbars", &hmax, 179);
	createTrackbar("Sat Min", "Trackbars", &smin, 255);
	createTrackbar("Sat Max", "Trackbars", &smax, 255);
	createTrackbar("Val Min", "Trackbars", &vmin, 255);
	createTrackbar("Val Max", "Trackbars", &vmax, 255);

	while (true) {

		Scalar lower(hmin, smin, vmin);
		Scalar upper(hmax, smax, vmax);
		// inRange(src, lower range, upper range, dst) 
		// : 특정 색상을 추출할 때 사용되는 inRange를 이용해 차선을 추출
		inRange(imgHSV, lower, upper, mask);

		imshow("Image", img);
		imshow("Image HSV", imgHSV);
		imshow("Image Mask", mask);
		waitKey(1);
	}
}