#include <opencv2/opencv.hpp>		// OpenCV에서 지원하는 모든 기능
#include <opencv2/videoio.hpp>		// 비디오 추적 및 배경 segmentation과 관련된 루틴
#include <opencv2/imgcodecs.hpp>	// 기본 데이터 타입이 선언 (Mat 이나 Point가 선언, 행렬 연산 혹은 벡터 연산)
#include <opencv2/highgui.hpp>		// 윈도우 화면, UI처리(슬라이더, 버튼 등) 및 마우스 제어 가능
#include <iostream>
#include <stdio.h>

using namespace cv;
using namespace std;

// #3. Resize and Crop
// 1) Importing Images
void main() {
	// Mat은 이미지를 담을 객체이다. 행렬 구성
	string path = "Resources/alpaca.jpg";
	Mat img = imread(path);
	Mat imgResize;

	cout << img.size() << endl;		// [612 X 536]
	resize(img, imgResize, Size(300, 300));

	imshow("Image", img);
	imshow("Image Resize", imgResize);
	waitKey(0);
}