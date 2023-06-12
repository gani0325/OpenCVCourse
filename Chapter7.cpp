#include <opencv2/opencv.hpp>		// OpenCV에서 지원하는 모든 기능
#include <opencv2/videoio.hpp>		// 비디오 추적 및 배경 segmentation과 관련된 루틴
#include <opencv2/imgcodecs.hpp>	// 기본 데이터 타입이 선언 (Mat 이나 Point가 선언, 행렬 연산 혹은 벡터 연산)
#include <opencv2/highgui.hpp>		// 윈도우 화면, UI처리(슬라이더, 버튼 등) 및 마우스 제어 가능
#include <iostream>
#include <stdio.h>

using namespace cv;
using namespace std;

// #7. Shapes/Contour Detection
Mat imgGray, imgBlur, imgCanny, imgDil, imgErode;

void getContours(Mat imgDil, Mat img) {

	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	
	// findContours(image, mode, method, contours=None, hierarchy=None, offset=None) 
	// : 외곽선 검출이란 객체의 외곽선 좌표를 모두 추출하는 작업
	findContours(imgDil, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	
	// drawContours(image, contours, contourIdx, color, thickness=None, lineType=No)
	// : 검출한 외곽선을 확인하기 위해 이 함수를 이용하여 외곽선을 화면에 그리기
	drawContours(img, contours, -1, Scalar(255, 0, 255), 2);

}

void main() {
	string path = "Resources/shapes.png";
	Mat img = imread(path);

	// Preprocessing
	cvtColor(img, imgGray, COLOR_BGR2GRAY);
	GaussianBlur(imgGray, imgBlur, Size(3, 3), 3, 0);
	Canny(imgBlur, imgCanny, 25, 75);

	// getStructuringElement(shape, ksize, anchor=None) 
	// : 크기와 모양을 설정하고 고정점 위치도 임의대로 결정
	Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
	dilate(imgCanny, imgDil, kernel);

	getContours(imgDil, img);

	imshow("Image", img);
	//imshow("Image Gray", imgGray);
	//imshow("Image Blur", imgBlur);
	//imshow("Image Canny", imgCanny);
	//imshow("Image Dil", imgDil);

	waitKey(0);

}