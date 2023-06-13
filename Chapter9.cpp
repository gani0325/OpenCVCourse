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
Mat img;
////////////////////  COLOR VALUES ////////////////////////////////
// hmin, smin, vmin, hmax, smax, vmax
vector<vector<int>> myColors{ {124,48,117,143,170,255},		// Purple
							   {68,72,156,102,126,255} };	// Green
vector<Scalar> myColorValues{ {255,0,255},		// Purple
							  {0,255,0} };		// Green 	

void getContours(Mat imgDil) {
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;

	// findContours(image, mode, method, contours=None, hierarchy=None, offset=None) 
	// : 외곽선 검출이란 객체의 외곽선 좌표를 모두 추출하는 작업
	findContours(imgDil, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

	for (int i = 0; i < contours.size(); i++) {
		int area = contourArea(contours[i]);
		cout << area << endl;

		vector<vector<Point>> conPoly(contours.size());
		vector<Rect> boundRect(contours.size());
		string objectType;

		if (area > 1000) {
			float peri = arcLength(contours[i], true);

			// approxPolyDP(윤곽선, 근사치 정확도, 폐곡선)
			// : 윤곽선들의 윤곽점들로 근사해 근사 다각형으로 반환
			approxPolyDP(contours[i], conPoly[i], 0.02 * peri, true);

			cout << conPoly[i].size() << endl;
			boundRect[i] = boundingRect(conPoly[i]);

			int objCor = (int)conPoly[i].size();

			// 산술 계산을 통해 직사각형 or 정사각형 구분하기
			if (objCor == 3) { objectType = "Tri"; }
			else if (objCor == 4)
			{
				float aspRatio = (float)boundRect[i].width / (float)boundRect[i].height;
				cout << aspRatio << endl;
				if (aspRatio > 0.95 && aspRatio < 1.05) { objectType = "Square"; }
				else { objectType = "Rect"; }
			}
			else if (objCor > 4) { objectType = "Circle"; }

			// drawContours(image, contours, contourIdx, color, thickness=None, lineType=No)
			// : 검출한 외곽선을 확인하기 위해 이 함수를 이용하여 외곽선을 화면에 그리기
			drawContours(img, conPoly, i, Scalar(255, 0, 255), 2);
		}
	}
}

void findColor(Mat img) {
	Mat imgHSV;
	cvtColor(img, imgHSV, COLOR_BGR2HSV);

	for (int i = 0; i < myColors.size(); i++) {
		Scalar lower(myColors[i][0], myColors[i][1], myColors[i][2]);
		Scalar upper(myColors[i][3], myColors[i][4], myColors[i][5]);
		Mat mask;
		inRange(imgHSV, lower, upper, mask);
		//imshow(to_string(i), mask);
		getContours(mask);
	}
}

int main() {
	VideoCapture cap(0);

	while (true) {
		cap.read(img);
		findColor(img);

		imshow("image", img);
		waitKey(1);
	}
}