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
int main(int ac, char** av) {
	// Mat�� �̹����� ���� ��ü�̴�. ��� ����
	string path = "Resources/alpaca.jpg";
	Mat img = imread(path);
	imshow("img", img);
	waitKey(0);

	return 0;
}