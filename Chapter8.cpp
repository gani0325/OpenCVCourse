#include <opencv2/opencv.hpp>		// OpenCV에서 지원하는 모든 기능
#include <opencv2/videoio.hpp>		// 비디오 추적 및 배경 segmentation과 관련된 루틴
#include <opencv2/imgcodecs.hpp>	// 기본 데이터 타입이 선언 (Mat 이나 Point가 선언, 행렬 연산 혹은 벡터 연산)
#include <opencv2/highgui.hpp>		// 윈도우 화면, UI처리(슬라이더, 버튼 등) 및 마우스 제어 가능
#include <opencv2/objdetect.hpp>
#include <iostream>
#include <stdio.h>

using namespace cv;
using namespace std;

// #8. Face Detection
void main() {
	// Mat은 이미지를 담을 객체이다. 행렬 구성
	string path = "Resources/jk2.jpg";
	Mat img = imread(path);
	Mat imgResize;

	resize(img, imgResize, Size(300, 300));

	//  미리 학습되어 있는 정보를 불러와서 내가 찾고자 하는 객체를 검출하는 기능을 제공
	CascadeClassifier faceCascade;
	faceCascade.load("Resources/haarcascade_frontalface_default.xml");
	
	if (faceCascade.empty()) {
		cout << "XML file not loaded" << endl;
	}

	vector<Rect> faces;
	// 특정 영상에서 내가 찾고자 하는 객체를 검출
	faceCascade.detectMultiScale(imgResize, faces, 1.1, 10);

	for (int i = 0; i < faces.size(); i++) {
		rectangle(imgResize, faces[i].tl(), faces[i].br(), Scalar(255, 0, 44));
	}

	imshow("img", imgResize);
	waitKey(0);

}