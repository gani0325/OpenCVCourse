#include <opencv2/opencv.hpp>		// OpenCV���� �����ϴ� ��� ���
#include <opencv2/videoio.hpp>		// ���� ���� �� ��� segmentation�� ���õ� ��ƾ
#include <opencv2/imgcodecs.hpp>	// �⺻ ������ Ÿ���� ���� (Mat �̳� Point�� ����, ��� ���� Ȥ�� ���� ����)
#include <opencv2/highgui.hpp>		// ������ ȭ��, UIó��(�����̴�, ��ư ��) �� ���콺 ���� ����
#include <iostream>
#include <stdio.h>

using namespace cv;
using namespace std;

// #4. Drawing shapes and text
void main() {
	// Mat�� �̹����� ���� ��ü�̴�. ��� ����
	Mat img(512, 512, CV_8UC3, Scalar(255, 0, 255));		// Blank image
	imshow("Image", img);

	waitKey(0);
}