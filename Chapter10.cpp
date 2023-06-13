#include <opencv2/opencv.hpp>		// OpenCV에서 지원하는 모든 기능
#include <opencv2/videoio.hpp>		// 비디오 추적 및 배경 segmentation과 관련된 루틴
#include <opencv2/imgcodecs.hpp>	// 기본 데이터 타입이 선언 (Mat 이나 Point가 선언, 행렬 연산 혹은 벡터 연산)
#include <opencv2/highgui.hpp>		// 윈도우 화면, UI처리(슬라이더, 버튼 등) 및 마우스 제어 가능
#include <opencv2/objdetect.hpp>
#include <iostream>
#include <stdio.h>

using namespace cv;
using namespace std;

// #10. Document Scanner
Mat imgOriginal, imgGray, imgCanny, imgThre, imgBlur, imgErode, imgDil;
vector<Point> initialPoints;

Mat preProcessing(Mat img) {
	// cvtColor( input Array,  output Array, flag)
	// : input Array를 입력받아 flag 에 대한 옵션으로 이미지 색채널을 변경
	cvtColor(img, imgGray, COLOR_BGR2GRAY);
	// GaussianBlur( src, dst, kernel_size, sigma_x, sigma_y, borderType) 
	// : 중앙값에 가중치를 더 주고 주변은 더 흐리게
	GaussianBlur(img, imgBlur, Size(3, 3), 3, 0);
	// Canny( src, dst, threshold1, threshold2)
	// : 경계선 검출
	Canny(imgBlur, imgCanny, 25, 75);
	Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
	// Morphology 
	// For Erosion : erode( src, dst, kernel, anchor, iteration, borderType, borderValue)
	// : 흰색 픽셀을 늘리는 역할
	//erode(imgCanny, imgErode, kernel);
	// For Dilation : dilate( src, dst, kernel, anchor, iteration, borderType, borderValue)
	// : 흰색 픽셀을 줄이는 역할
	dilate(imgCanny, imgDil, kernel);
	return imgDil;
}

vector<Point> getContours(Mat imgDil) {
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;

	// findContours(image, mode, method, contours=None, hierarchy=None, offset=None) 
	// : 외곽선 검출이란 객체의 외곽선 좌표를 모두 추출하는 작업
	findContours(imgDil, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	vector<vector<Point>> conPoly(contours.size());
	vector<Rect> boundRect(contours.size());
	vector<Point> biggest;
	int maxArea = 0;

	for (int i = 0; i < contours.size(); i++) {
		int area = contourArea(contours[i]);
		cout << area << endl;

		string objectType;

		if (area > 1000) {
			float peri = arcLength(contours[i], true);
			// approxPolyDP(윤곽선, 근사치 정확도, 폐곡선)
			// : 윤곽선들의 윤곽점들로 근사해 근사 다각형으로 반환
			approxPolyDP(contours[i], conPoly[i], 0.02 * peri, true);

			if (area > maxArea && conPoly[i].size() == 4) {
				drawContours(imgOriginal, conPoly, i, Scalar(255, 0, 255), 5);
				biggest = { conPoly[i][0], conPoly[i][1], conPoly[i][2], conPoly[i][3] };
				maxArea = area;
			}
			// drawContours(image, contours, contourIdx, color, thickness=None, lineType=No)
			// : 검출한 외곽선을 확인하기 위해 이 함수를 이용하여 외곽선을 화면에 그리기
			//drawContours(imgOriginal, conPoly, i, Scalar(255, 0, 255), 2);
			//rectangle(imgOriginal, boundRect[i].tl(), boundRect[i].br(), Scalar(0, 255, 0), 5);
		}
	}
	return biggest;
}

void drawPoints(vector<Point> points, Scalar color) {
	for (int i = 0; i < points.size(); i++) {
		circle(imgOriginal, points[i], 30, color, FILLED);
		putText(imgOriginal, to_string(i), points[i], FONT_HERSHEY_PLAIN, 2, color, 2);
	}
}

int main() {
	string path = "Resources/paper.jpg";
	imgOriginal = imread(path);
	resize(imgOriginal, imgOriginal, Size(), 0.5, 0.5);

	// Preprocessing
	imgThre = preProcessing(imgOriginal);
	// Get contours - Biggest
	initialPoints = getContours(imgThre);
	drawPoints(initialPoints, Scalar(0, 0, 255));
	// Warp
	imshow("image", imgOriginal);
	imshow("image Dial", imgDil);

	waitKey(0);
}