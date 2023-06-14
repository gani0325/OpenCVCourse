#include <opencv2/opencv.hpp>		// OpenCV���� �����ϴ� ��� ���
#include <opencv2/videoio.hpp>		// ���� ���� �� ��� segmentation�� ���õ� ��ƾ
#include <opencv2/imgcodecs.hpp>	// �⺻ ������ Ÿ���� ���� (Mat �̳� Point�� ����, ��� ���� Ȥ�� ���� ����)
#include <opencv2/highgui.hpp>		// ������ ȭ��, UIó��(�����̴�, ��ư ��) �� ���콺 ���� ����
#include <opencv2/objdetect.hpp>
#include <iostream>
#include <stdio.h>

using namespace cv;
using namespace std;

// #11. License Plate Detector
void main() {
	VideoCapture cap(0);
	Mat img;

	//  �̸� �н��Ǿ� �ִ� ������ �ҷ��ͼ� ���� ã���� �ϴ� ��ü�� �����ϴ� ����� ����
	CascadeClassifier plateCascade;
	plateCascade.load("Resources/haarcascade_russian_plate_number.xml");

	if (plateCascade.empty()) {
		cout << "XML file not loaded" << endl;
	}

	vector<Rect> plates;
	
	while (true) {
		cap.read(img);

		// Ư�� ���󿡼� ���� ã���� �ϴ� ��ü�� ����
		plateCascade.detectMultiScale(img, plates, 1.1, 10);

		for (int i = 0; i < plates.size(); i++) {
			rectangle(img, plates[i].tl(), plates[i].br(), Scalar(255, 0, 44));
		}

		imshow("img", img);
		waitKey(1);
	}
}