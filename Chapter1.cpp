#include <opencv2/imgcodecs.hpp>	// OpenCV���� �����ϴ� ��� ���
#include <opencv2/videoio.hpp>		// ���� ���� �� ��� segmentation�� ���õ� ��ƾ
#include <opencv2/imgcodecs.hpp>	// �⺻ ������ Ÿ���� ���� (Mat �̳� Point�� ����, ��� ���� Ȥ�� ���� ����)
#include <opencv2/highgui.hpp>		// ������ ȭ��, UIó��(�����̴�, ��ư ��) �� ���콺 ���� ����

#include <iostream>
#include <stdio.h>

using namespace cv;
using namespace std;

// #1. Read Images Videos and Webcams
// 1) Importing Images
//void main() {
//	// Mat�� �̹����� ���� ��ü�̴�. ��� ����
//	string path = "Resources/alpaca.jpg";
//	Mat img = imread(path);
//	imshow("img", img);
//	waitKey(0);
//}

// 2) Importing Video
void main() {
	string path = "Resources/eddy.mp4";
	// VideoCapture '���� �̸�'( "������ �̸�" ) : ������ ȭ��(frame)�� ����
	VideoCapture cap(path);
	Mat video;

	while (true) {
		cap.read(video);
		imshow("Video", video);
		// Ű �Է��� ��ٸ��� ��� �Լ�
		// 0 : ���� ���
		// ms(�и�����) ������ �ð� : �ش� �ð���ŭ ��� (1000ms = 1��)
		waitKey(20);
	}
}