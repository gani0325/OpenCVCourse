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
Mat img;
////////////////////  COLOR VALUES ////////////////////////////////
// hmin, smin, vmin, hmax, smax, vmax
vector<vector<int>> myColors{ {124,48,117,143,170,255},		// Purple
							   {68,72,156,102,126,255} };	// Green
vector<Scalar> myColorValues{ {255,0,255},		// Purple
							  {0,255,0} };		// Green 	

void getContours(Mat imgDil) {
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;

	// findContours(image, mode, method, contours=None, hierarchy=None, offset=None) 
	// : �ܰ��� �����̶� ��ü�� �ܰ��� ��ǥ�� ��� �����ϴ� �۾�
	findContours(imgDil, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

	for (int i = 0; i < contours.size(); i++) {
		int area = contourArea(contours[i]);
		cout << area << endl;

		vector<vector<Point>> conPoly(contours.size());
		vector<Rect> boundRect(contours.size());
		string objectType;

		if (area > 1000) {
			float peri = arcLength(contours[i], true);

			// approxPolyDP(������, �ٻ�ġ ��Ȯ��, ��)
			// : ���������� ��������� �ٻ��� �ٻ� �ٰ������� ��ȯ
			approxPolyDP(contours[i], conPoly[i], 0.02 * peri, true);

			cout << conPoly[i].size() << endl;
			boundRect[i] = boundingRect(conPoly[i]);

			int objCor = (int)conPoly[i].size();

			// ��� ����� ���� ���簢�� or ���簢�� �����ϱ�
			if (objCor == 3) { objectType = "Tri"; }
			else if (objCor == 4)
			{
				float aspRatio = (float)boundRect[i].width / (float)boundRect[i].height;
				cout << aspRatio << endl;
				if (aspRatio > 0.95 && aspRatio < 1.05) { objectType = "Square"; }
				else { objectType = "Rect"; }
			}
			else if (objCor > 4) { objectType = "Circle"; }

			// drawContours(image, contours, contourIdx, color, thickness=None, lineType=No)
			// : ������ �ܰ����� Ȯ���ϱ� ���� �� �Լ��� �̿��Ͽ� �ܰ����� ȭ�鿡 �׸���
			drawContours(img, conPoly, i, Scalar(255, 0, 255), 2);
		}
	}
}

void findColor(Mat img) {
	Mat imgHSV;
	cvtColor(img, imgHSV, COLOR_BGR2HSV);

	for (int i = 0; i < myColors.size(); i++) {
		Scalar lower(myColors[i][0], myColors[i][1], myColors[i][2]);
		Scalar upper(myColors[i][3], myColors[i][4], myColors[i][5]);
		Mat mask;
		inRange(imgHSV, lower, upper, mask);
		//imshow(to_string(i), mask);
		getContours(mask);
	}
}

int main() {
	VideoCapture cap(0);

	while (true) {
		cap.read(img);
		findColor(img);

		imshow("image", img);
		waitKey(1);
	}
}