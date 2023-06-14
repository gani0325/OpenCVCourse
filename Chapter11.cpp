#include <opencv2/opencv.hpp>		// OpenCV에서 지원하는 모든 기능
#include <opencv2/videoio.hpp>		// 비디오 추적 및 배경 segmentation과 관련된 루틴
#include <opencv2/imgcodecs.hpp>	// 기본 데이터 타입이 선언 (Mat 이나 Point가 선언, 행렬 연산 혹은 벡터 연산)
#include <opencv2/highgui.hpp>		// 윈도우 화면, UI처리(슬라이더, 버튼 등) 및 마우스 제어 가능
#include <opencv2/objdetect.hpp>
#include <iostream>
#include <stdio.h>

using namespace cv;
using namespace std;

// #11. License Plate Detector
void main() {
	VideoCapture cap(0);
	Mat img;

	//  미리 학습되어 있는 정보를 불러와서 내가 찾고자 하는 객체를 검출하는 기능을 제공
	CascadeClassifier plateCascade;
	plateCascade.load("Resources/haarcascade_russian_plate_number.xml");

	if (plateCascade.empty()) {
		cout << "XML file not loaded" << endl;
	}

	vector<Rect> plates;
	
	while (true) {
		cap.read(img);

		// 특정 영상에서 내가 찾고자 하는 객체를 검출
		plateCascade.detectMultiScale(img, plates, 1.1, 10);

		for (int i = 0; i < plates.size(); i++) {
			rectangle(img, plates[i].tl(), plates[i].br(), Scalar(255, 0, 44));
		}

		imshow("img", img);
		waitKey(1);
	}
}