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
	Mat img(512, 512, CV_8UC3, Scalar(255, 0, 100));		// Blank image
	
	// circle( img, Point(x, y), radius, Scalar(b,g,r), thickness, lineType, shift )
	circle(img, Point(256, 256), 155, Scalar(0, 69, 255), 10);
	// rectangle( img , Rect , Scalar(b, g, r), thickness, lineType, shift )
	rectangle(img, Point(130, 226), Point(382, 286), Scalar(255, 255, 0), FILLED);

	imshow("Image", img);
	waitKey(0);
}