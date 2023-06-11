#include <opencv2/opencv.hpp>		// OpenCV���� �����ϴ� ��� ���
#include <opencv2/videoio.hpp>		// ���� ���� �� ��� segmentation�� ���õ� ��ƾ
#include <opencv2/imgcodecs.hpp>	// �⺻ ������ Ÿ���� ���� (Mat �̳� Point�� ����, ��� ���� Ȥ�� ���� ����)
#include <opencv2/highgui.hpp>		// ������ ȭ��, UIó��(�����̴�, ��ư ��) �� ���콺 ���� ����
#include <iostream>
#include <stdio.h>

using namespace cv;
using namespace std;

// #2. Basic Functions (cvtColor, GaussianBlur, Edge detection, dilate, erode)
void main() {
	// Mat�� �̹����� ���� ��ü�̴�. ��� ����
	string path = "Resources/alpaca.jpg";
	Mat img = imread(path);
	Mat imgGray;
	Mat imgBlur;
	Mat imgCanny;
	Mat imgDil;
	Mat imgErode;

	// cvtColor( input Array,  output Array, flag)
	// : input Array�� �Է¹޾� flag �� ���� �ɼ����� �̹��� ��ä���� ����
	cvtColor(img, imgGray, COLOR_BGR2GRAY);
	// GaussianBlur( src, dst, kernel_size, sigma_x, sigma_y, borderType) 
	// : �߾Ӱ��� ����ġ�� �� �ְ� �ֺ��� �� �帮��
	GaussianBlur(img, imgBlur, Size(3, 3), 3, 0);
	// Canny( src, dst, threshold1, threshold2)
	// : ��輱 ����
	Canny(imgBlur, imgCanny, 50, 150);
	Mat kernel = getStructuringElement(MORPH_RECT, Size(5, 5));
	// Morphology 
	// For Erosion : erode( src, dst, kernel, anchor, iteration, borderType, borderValue)
	// : ��� �ȼ��� �ø��� ����
	erode(imgCanny, imgErode, kernel, Point(-1, -1), 1);
	// For Dilation : dilate( src, dst, kernel, anchor, iteration, borderType, borderValue)
	// : ��� �ȼ��� ���̴� ����
	dilate(imgCanny, imgDil, kernel, Point(-1, -1), 1);

	imshow("img", img);
	imshow("Gray img", imgGray);
	imshow("Gray Blur", imgBlur);
	imshow("Canny", imgCanny);
	imshow("Dilation", imgDil);
	imshow("Erode", imgErode);

	waitKey(0);
}