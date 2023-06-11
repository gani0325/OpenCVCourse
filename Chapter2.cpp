#include <opencv2/opencv.hpp>		// OpenCV에서 지원하는 모든 기능
#include <opencv2/videoio.hpp>		// 비디오 추적 및 배경 segmentation과 관련된 루틴
#include <opencv2/imgcodecs.hpp>	// 기본 데이터 타입이 선언 (Mat 이나 Point가 선언, 행렬 연산 혹은 벡터 연산)
#include <opencv2/highgui.hpp>		// 윈도우 화면, UI처리(슬라이더, 버튼 등) 및 마우스 제어 가능
#include <iostream>
#include <stdio.h>

using namespace cv;
using namespace std;

// #2. Basic Functions (cvtColor, GaussianBlur, Edge detection, dilate, erode)
void main() {
	// Mat은 이미지를 담을 객체이다. 행렬 구성
	string path = "Resources/alpaca.jpg";
	Mat img = imread(path);
	Mat imgGray;
	Mat imgBlur;
	Mat imgCanny;
	Mat imgDil;
	Mat imgErode;

	// cvtColor( input Array,  output Array, flag)
	// : input Array를 입력받아 flag 에 대한 옵션으로 이미지 색채널을 변경
	cvtColor(img, imgGray, COLOR_BGR2GRAY);
	// GaussianBlur( src, dst, kernel_size, sigma_x, sigma_y, borderType) 
	// : 중앙값에 가중치를 더 주고 주변은 더 흐리게
	GaussianBlur(img, imgBlur, Size(3, 3), 3, 0);
	// Canny( src, dst, threshold1, threshold2)
	// : 경계선 검출
	Canny(imgBlur, imgCanny, 50, 150);
	Mat kernel = getStructuringElement(MORPH_RECT, Size(5, 5));
	// Morphology 
	// For Erosion : erode( src, dst, kernel, anchor, iteration, borderType, borderValue)
	// : 흰색 픽셀을 늘리는 역할
	erode(imgCanny, imgErode, kernel, Point(-1, -1), 1);
	// For Dilation : dilate( src, dst, kernel, anchor, iteration, borderType, borderValue)
	// : 흰색 픽셀을 줄이는 역할
	dilate(imgCanny, imgDil, kernel, Point(-1, -1), 1);

	imshow("img", img);
	imshow("Gray img", imgGray);
	imshow("Gray Blur", imgBlur);
	imshow("Canny", imgCanny);
	imshow("Dilation", imgDil);
	imshow("Erode", imgErode);

	waitKey(0);
}