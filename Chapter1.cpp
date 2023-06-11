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
void main() {
	// Mat�� �̹����� ���� ��ü�̴�. ��� ����
	string path = "Resources/alpaca.jpg";
	Mat img = imread(path);
	imshow("img", img);
	waitKey(0);
}

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

// 3) Importing Webcam
int main(int argv, char** argc) {
	// ���� ��ķ�� �ְ�, Ȱ��ȭ�� �Ǿ��ִ� ��� ���� ��ķ�� ī�޶� ��ȣ�� '0' 
	// ��ķ�� �߰��� ��� ī�޶� ��ȣ�� '1' 
	VideoCapture cap(0);
	
	// ī�޶��� �̹����� �о ��� Mat���·� ��ȯ�ϴµ�, RGB�� �ƴ� BGR�� �о��
	Mat webcam;

	while (1) {
		// ����Ǵ� ������ �� frame�� �о true ��ȯ
		cap.read(webcam);
		// Read�� ���� �о�� �������� ȭ�鿡 Display�ϴ� �Լ�.
		imshow("Webcam", webcam);
		// Ű �Է��� ��ٸ��� ��� �Լ�
		// 0 : ���� ���
		// ms(�и�����) ������ �ð� : �ش� �ð���ŭ ��� (1000ms = 1��)
		waitKey(1);
	}
	return 0;
}

// 3) Importing Webcam
int main(int, char**)
{
	Mat frame; // OpenCV���� ���� �⺻�� �Ǵ� Matrix ����ü(�̹����� �о� �ش� ������ Mat���·� ��ȯ)
	VideoCapture cap; // ������ �ҷ�����
	cap.open(0); // ������ ����(Camera ����) + ī�޶��ȣ(0(���� �켱))
	if (!cap.isOpened())
	{
		cout << "Error! Cannot open the camera" << endl;
		return -1;
	}
	while (1)
	{
		cap.read(frame); // ������ �� �����Ӿ� read
		imshow("LIVE", frame); // �������� ȭ�鿡 display
		if (waitKey(5) >= 0) // 5��ŭ Ű�Է��� ����ϰ�, �߻��� ��ȯ
			break;
	}
	return 0;
}