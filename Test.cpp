#include <opencv2/imgcodecs.hpp>	// OpenCV에서 지원하는 모든 기능
#include <opencv2/videoio.hpp>		// 비디오 추적 및 배경 segmentation과 관련된 루틴
#include <opencv2/highgui.hpp>		// 윈도우 화면, UI처리(슬라이더, 버튼 등) 및 마우스 제어 가능

#include <iostream>
#include <stdio.h>

using namespace cv;
using namespace std;

// OpenCV 로 이미지 띄우기
int main(int ac, char** av) {
	// Mat은 이미지를 담을 객체이다. 행렬 구성
	string path = "Resources/alpaca.jpg";
	Mat img = imread(path);
	imshow("img", img);
	waitKey(0);

	return 0;
}