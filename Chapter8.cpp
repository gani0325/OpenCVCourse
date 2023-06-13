#include <opencv2/opencv.hpp>		// OpenCV���� �����ϴ� ��� ���
#include <opencv2/videoio.hpp>		// ���� ���� �� ��� segmentation�� ���õ� ��ƾ
#include <opencv2/imgcodecs.hpp>	// �⺻ ������ Ÿ���� ���� (Mat �̳� Point�� ����, ��� ���� Ȥ�� ���� ����)
#include <opencv2/highgui.hpp>		// ������ ȭ��, UIó��(�����̴�, ��ư ��) �� ���콺 ���� ����
#include <opencv2/objdetect.hpp>
#include <iostream>
#include <stdio.h>

using namespace cv;
using namespace std;

// #8. Face Detection
void main() {
	// Mat�� �̹����� ���� ��ü�̴�. ��� ����
	string path = "Resources/jk2.jpg";
	Mat img = imread(path);
	Mat imgResize;

	resize(img, imgResize, Size(300, 300));

	//  �̸� �н��Ǿ� �ִ� ������ �ҷ��ͼ� ���� ã���� �ϴ� ��ü�� �����ϴ� ����� ����
	CascadeClassifier faceCascade;
	faceCascade.load("Resources/haarcascade_frontalface_default.xml");
	
	if (faceCascade.empty()) {
		cout << "XML file not loaded" << endl;
	}

	vector<Rect> faces;
	// Ư�� ���󿡼� ���� ã���� �ϴ� ��ü�� ����
	faceCascade.detectMultiScale(imgResize, faces, 1.1, 10);

	for (int i = 0; i < faces.size(); i++) {
		rectangle(imgResize, faces[i].tl(), faces[i].br(), Scalar(255, 0, 44));
	}

	imshow("img", imgResize);
	waitKey(0);

}