#include <opencv2/opencv.hpp>		// OpenCV���� �����ϴ� ��� ���
#include <opencv2/videoio.hpp>		// ���� ���� �� ��� segmentation�� ���õ� ��ƾ
#include <opencv2/imgcodecs.hpp>	// �⺻ ������ Ÿ���� ���� (Mat �̳� Point�� ����, ��� ���� Ȥ�� ���� ����)
#include <opencv2/highgui.hpp>		// ������ ȭ��, UIó��(�����̴�, ��ư ��) �� ���콺 ���� ����
#include <iostream>
#include <stdio.h>

using namespace cv;
using namespace std;

// #3. Resize and Crop
// 1) Importing Images
void main() {
	// Mat�� �̹����� ���� ��ü�̴�. ��� ����
	string path = "Resources/alpaca.jpg";
	Mat img = imread(path);
	Mat imgResize;

	cout << img.size() << endl;		// [612 X 536]
	resize(img, imgResize, Size(300, 300));

	imshow("Image", img);
	imshow("Image Resize", imgResize);
	waitKey(0);
}