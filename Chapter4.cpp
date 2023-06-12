#include <opencv2/opencv.hpp>		// OpenCV에서 지원하는 모든 기능
#include <opencv2/videoio.hpp>		// 비디오 추적 및 배경 segmentation과 관련된 루틴
#include <opencv2/imgcodecs.hpp>	// 기본 데이터 타입이 선언 (Mat 이나 Point가 선언, 행렬 연산 혹은 벡터 연산)
#include <opencv2/highgui.hpp>		// 윈도우 화면, UI처리(슬라이더, 버튼 등) 및 마우스 제어 가능
#include <iostream>
#include <stdio.h>

using namespace cv;
using namespace std;

// #4. Drawing shapes and text
void main() {
	// Mat은 이미지를 담을 객체이다. 행렬 구성
	Mat img(512, 512, CV_8UC3, Scalar(255, 0, 100));		// Blank image
	
	// circle( img, Point(x, y), radius, Scalar(b,g,r), thickness, lineType, shift )
	circle(img, Point(256, 256), 155, Scalar(0, 69, 255), 10);
	// rectangle( img , Rect , Scalar(b, g, r), thickness, lineType, shift )
	rectangle(img, Point(130, 226), Point(382, 286), Scalar(255, 255, 0), FILLED);
	// line( Input Output Array, pt1, pt2, scalar(b,g,r), thickness, lineType,  shift ) 
	line(img, Point(130, 296), Point(382, 454), Scalar(255, 12, 4), 3);

	// putText( img, string, Point(x,y), font face, font scale, color, thickness, line type, bottom left origin )
	putText(img, "gani hello", Point(147, 242), FONT_HERSHEY_DUPLEX, 2, Scalar(0, 34, 255), 2);

	imshow("Image", img);
	waitKey(0);
}