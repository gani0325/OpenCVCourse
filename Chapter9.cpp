#include <opencv2/opencv.hpp>		// OpenCV에서 지원하는 모든 기능
#include <opencv2/videoio.hpp>		// 비디오 추적 및 배경 segmentation과 관련된 루틴
#include <opencv2/imgcodecs.hpp>	// 기본 데이터 타입이 선언 (Mat 이나 Point가 선언, 행렬 연산 혹은 벡터 연산)
#include <opencv2/highgui.hpp>		// 윈도우 화면, UI처리(슬라이더, 버튼 등) 및 마우스 제어 가능
#include <opencv2/objdetect.hpp>
#include <iostream>
#include <stdio.h>

using namespace cv;
using namespace std;

// #9. Project1 - Virtual Painter
////////////////////  COLOR VALUES ////////////////////////////////
// hmin, smin, vmin, hmax, smax, vmax
vector<vector<int>> myColors{ {124,48,117,143,170,255},		// Purple
							   {68,72,156,102,126,255} };	// Green
vector<Scalar> myColorValues{ {255,0,255},		// Purple
							  {0,255,0} };		// Green 	

void findColor(Mat img) {
	Mat imgHSV;
	cvtColor(img, imgHSV, COLOR_BGR2HSV);

	for (int i = 0; i < myColors.size(); i++) {
		Scalar lower(myColors[i][0], myColors[i][1], myColors[i][2]);
		Scalar upper(myColors[i][3], myColors[i][4], myColors[i][5]);
		Mat mask;
		inRange(imgHSV, lower, upper, mask);
		imshow(to_string(i), mask);
	}
}

int main() {
	Mat img;
	VideoCapture cap(0);

	while (true) {
		cap.read(img);
		findColor(img);

		imshow("image", img);
		waitKey(1);
	}
}