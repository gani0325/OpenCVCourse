#include <opencv2/opencv.hpp>		// OpenCV���� �����ϴ� ��� ���
#include <opencv2/videoio.hpp>		// ���� ���� �� ��� segmentation�� ���õ� ��ƾ
#include <opencv2/imgcodecs.hpp>	// �⺻ ������ Ÿ���� ���� (Mat �̳� Point�� ����, ��� ���� Ȥ�� ���� ����)
#include <opencv2/highgui.hpp>		// ������ ȭ��, UIó��(�����̴�, ��ư ��) �� ���콺 ���� ����
#include <opencv2/objdetect.hpp>
#include <iostream>
#include <stdio.h>

using namespace cv;
using namespace std;

// #9. Project1 - Virtual Painter
////////////////////  COLOR VALUES ////////////////////////////////
// hmin, smin, vmin, hmax, smax, vmax
vector<vector<int>> myColors{ {124,48,117,143,170,255},		// Purple
							   {68,72,156,102,126,255} };	// Green
vector<Scalar> myColorValues{ {255,0,255},		// Purple
							  {0,255,0} };		// Green 	

void findColor(Mat img) {
	Mat imgHSV;
	cvtColor(img, imgHSV, COLOR_BGR2HSV);

	for (int i = 0; i < myColors.size(); i++) {
		Scalar lower(myColors[i][0], myColors[i][1], myColors[i][2]);
		Scalar upper(myColors[i][3], myColors[i][4], myColors[i][5]);
		Mat mask;
		inRange(imgHSV, lower, upper, mask);
		imshow(to_string(i), mask);
	}
}

int main() {
	Mat img;
	VideoCapture cap(0);

	while (true) {
		cap.read(img);
		findColor(img);

		imshow("image", img);
		waitKey(1);
	}
}