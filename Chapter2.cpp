#include <opencv2/opencv.hpp>		// OpenCV���� �����ϴ� ��� ���
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
	Mat imgGray;
	Mat imgBlur;

	// cvtColor( input Array,  output Array, flag)
	// : input Array�� �Է¹޾� flag �� ���� �ɼ����� �̹��� ��ä���� ����
	cvtColor(img, imgGray, COLOR_BGR2GRAY);
	// GaussianBlur( src, dst, kernel_size, sigma_x, sigma_y, borderType) 
	// �߾Ӱ��� ����ġ�� �� �ְ� �ֺ��� �� �帮��
	GaussianBlur(img, imgBlur, Size(3, 3), 3, 0);

	imshow("img", img);
	imshow("Gray img", imgGray);

	waitKey(0);
}