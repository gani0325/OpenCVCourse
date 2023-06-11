#include <opencv2/imgcodecs.hpp>	// OpenCV에서 지원하는 모든 기능
#include <opencv2/videoio.hpp>		// 비디오 추적 및 배경 segmentation과 관련된 루틴
#include <opencv2/imgcodecs.hpp>	// 기본 데이터 타입이 선언 (Mat 이나 Point가 선언, 행렬 연산 혹은 벡터 연산)
#include <opencv2/highgui.hpp>		// 윈도우 화면, UI처리(슬라이더, 버튼 등) 및 마우스 제어 가능

#include <iostream>
#include <stdio.h>

using namespace cv;
using namespace std;

// #1. Read Images Videos and Webcams
// 1) Importing Images
//void main() {
//	// Mat은 이미지를 담을 객체이다. 행렬 구성
//	string path = "Resources/alpaca.jpg";
//	Mat img = imread(path);
//	imshow("img", img);
//	waitKey(0);
//}

// 2) Importing Video
void main() {
	string path = "Resources/eddy.mp4";
	// VideoCapture '변수 이름'( "동영상 이름" ) : 동영상 화면(frame)을 읽음
	VideoCapture cap(path);
	Mat video;

	while (true) {
		cap.read(video);
		imshow("Video", video);
		// 키 입력을 기다리는 대기 함수
		// 0 : 무한 대기
		// ms(밀리세컨) 단위의 시간 : 해당 시간만큼 대기 (1000ms = 1초)
		waitKey(20);
	}
}