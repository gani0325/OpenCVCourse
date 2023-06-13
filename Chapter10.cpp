#include <opencv2/opencv.hpp>		// OpenCV���� �����ϴ� ��� ���
#include <opencv2/videoio.hpp>		// ���� ���� �� ��� segmentation�� ���õ� ��ƾ
#include <opencv2/imgcodecs.hpp>	// �⺻ ������ Ÿ���� ���� (Mat �̳� Point�� ����, ��� ���� Ȥ�� ���� ����)
#include <opencv2/highgui.hpp>		// ������ ȭ��, UIó��(�����̴�, ��ư ��) �� ���콺 ���� ����
#include <opencv2/objdetect.hpp>
#include <iostream>
#include <stdio.h>

using namespace cv;
using namespace std;

// #10. Document Scanner
Mat imgOriginal, imgGray, imgCanny, imgThre, imgBlur, imgErode, imgDil;
vector<Point> initialPoints;

Mat preProcessing(Mat img) {
	// cvtColor( input Array,  output Array, flag)
	// : input Array�� �Է¹޾� flag �� ���� �ɼ����� �̹��� ��ä���� ����
	cvtColor(img, imgGray, COLOR_BGR2GRAY);
	// GaussianBlur( src, dst, kernel_size, sigma_x, sigma_y, borderType) 
	// : �߾Ӱ��� ����ġ�� �� �ְ� �ֺ��� �� �帮��
	GaussianBlur(img, imgBlur, Size(3, 3), 3, 0);
	// Canny( src, dst, threshold1, threshold2)
	// : ��輱 ����
	Canny(imgBlur, imgCanny, 25, 75);
	Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
	// Morphology 
	// For Erosion : erode( src, dst, kernel, anchor, iteration, borderType, borderValue)
	// : ��� �ȼ��� �ø��� ����
	//erode(imgCanny, imgErode, kernel);
	// For Dilation : dilate( src, dst, kernel, anchor, iteration, borderType, borderValue)
	// : ��� �ȼ��� ���̴� ����
	dilate(imgCanny, imgDil, kernel);
	return imgDil;
}

vector<Point> getContours(Mat imgDil) {
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;

	// findContours(image, mode, method, contours=None, hierarchy=None, offset=None) 
	// : �ܰ��� �����̶� ��ü�� �ܰ��� ��ǥ�� ��� �����ϴ� �۾�
	findContours(imgDil, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	vector<vector<Point>> conPoly(contours.size());
	vector<Rect> boundRect(contours.size());
	vector<Point> biggest;
	int maxArea = 0;

	for (int i = 0; i < contours.size(); i++) {
		int area = contourArea(contours[i]);
		cout << area << endl;

		string objectType;

		if (area > 1000) {
			float peri = arcLength(contours[i], true);
			// approxPolyDP(������, �ٻ�ġ ��Ȯ��, ��)
			// : ���������� ��������� �ٻ��� �ٻ� �ٰ������� ��ȯ
			approxPolyDP(contours[i], conPoly[i], 0.02 * peri, true);

			if (area > maxArea && conPoly[i].size() == 4) {
				drawContours(imgOriginal, conPoly, i, Scalar(255, 0, 255), 5);
				biggest = { conPoly[i][0], conPoly[i][1], conPoly[i][2], conPoly[i][3] };
				maxArea = area;
			}
			// drawContours(image, contours, contourIdx, color, thickness=None, lineType=No)
			// : ������ �ܰ����� Ȯ���ϱ� ���� �� �Լ��� �̿��Ͽ� �ܰ����� ȭ�鿡 �׸���
			//drawContours(imgOriginal, conPoly, i, Scalar(255, 0, 255), 2);
			//rectangle(imgOriginal, boundRect[i].tl(), boundRect[i].br(), Scalar(0, 255, 0), 5);
		}
	}
	return biggest;
}

void drawPoints(vector<Point> points, Scalar color) {
	for (int i = 0; i < points.size(); i++) {
		circle(imgOriginal, points[i], 30, color, FILLED);
		putText(imgOriginal, to_string(i), points[i], FONT_HERSHEY_PLAIN, 2, color, 2);
	}
}

int main() {
	string path = "Resources/paper.jpg";
	imgOriginal = imread(path);
	resize(imgOriginal, imgOriginal, Size(), 0.5, 0.5);

	// Preprocessing
	imgThre = preProcessing(imgOriginal);
	// Get contours - Biggest
	initialPoints = getContours(imgThre);
	drawPoints(initialPoints, Scalar(0, 0, 255));
	// Warp
	imshow("image", imgOriginal);
	imshow("image Dial", imgDil);

	waitKey(0);
}