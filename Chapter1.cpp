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
void main() {
	// Mat은 이미지를 담을 객체이다. 행렬 구성
	string path = "Resources/alpaca.jpg";
	Mat img = imread(path);
	imshow("img", img);
	waitKey(0);
}

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

// 3) Importing Webcam
int main(int argv, char** argc) {
	// 내장 웹캠이 있고, 활성화가 되어있는 경우 내장 웹캠의 카메라 번호는 '0' 
	// 웹캠을 추가할 경우 카메라 번호는 '1' 
	VideoCapture cap(0);
	
	// 카메라의 이미지를 읽어서 모두 Mat형태로 변환하는데, RGB가 아닌 BGR로 읽어옴
	Mat webcam;

	while (1) {
		// 재생되는 비디오의 한 frame씩 읽어서 true 반환
		cap.read(webcam);
		// Read를 통해 읽어온 프레임을 화면에 Display하는 함수.
		imshow("Webcam", webcam);
		// 키 입력을 기다리는 대기 함수
		// 0 : 무한 대기
		// ms(밀리세컨) 단위의 시간 : 해당 시간만큼 대기 (1000ms = 1초)
		waitKey(1);
	}
	return 0;
}

// 3) Importing Webcam
int main(int, char**)
{
	Mat frame; // OpenCV에서 가장 기본이 되는 Matrix 구조체(이미지를 읽어 해당 정보를 Mat형태로 변환)
	VideoCapture cap; // 동영상 불러오기
	cap.open(0); // 동영상 열기(Camera 열기) + 카메라번호(0(내장 우선))
	if (!cap.isOpened())
	{
		cout << "Error! Cannot open the camera" << endl;
		return -1;
	}
	while (1)
	{
		cap.read(frame); // 비디오의 한 프레임씩 read
		imshow("LIVE", frame); // 프레임을 화면에 display
		if (waitKey(5) >= 0) // 5만큼 키입력을 대기하고, 발생시 반환
			break;
	}
	return 0;
}