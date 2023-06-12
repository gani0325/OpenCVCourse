#include <opencv2/opencv.hpp>		// OpenCV���� �����ϴ� ��� ���
#include <opencv2/videoio.hpp>		// ���� ���� �� ��� segmentation�� ���õ� ��ƾ
#include <opencv2/imgcodecs.hpp>	// �⺻ ������ Ÿ���� ���� (Mat �̳� Point�� ����, ��� ���� Ȥ�� ���� ����)
#include <opencv2/highgui.hpp>		// ������ ȭ��, UIó��(�����̴�, ��ư ��) �� ���콺 ���� ����
#include <iostream>
#include <stdio.h>

using namespace cv;
using namespace std;

// #7. Shapes/Contour Detection
Mat imgGray, imgBlur, imgCanny, imgDil, imgErode;

void getContours(Mat imgDil, Mat img) {

	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	
	// findContours(image, mode, method, contours=None, hierarchy=None, offset=None) 
	// : �ܰ��� �����̶� ��ü�� �ܰ��� ��ǥ�� ��� �����ϴ� �۾�
	findContours(imgDil, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	vector<vector<Point>> conPoly(contours.size());
	vector<Rect> boundRect(contours.size());

	for (int i = 0; i < contours.size(); i++)
	{
		float peri = arcLength(contours[i], true);
		approxPolyDP(contours[i], conPoly[i], 0.02 * peri, true);

		// drawContours(image, contours, contourIdx, color, thickness=None, lineType=No)
		// : ������ �ܰ����� Ȯ���ϱ� ���� �� �Լ��� �̿��Ͽ� �ܰ����� ȭ�鿡 �׸���
		drawContours(img, contours, -1, Scalar(255, 0, 255), 2);
		cout << conPoly[i].size() << endl;
		
		// �־��� ���� ���δ� �ּ� ũ�� �簢��(�ٿ�� �ڽ�)�� ��ȯ
		boundRect[i] = boundingRect(conPoly[i]);
		rectangle(img, boundRect[i].tl(), boundRect[i].br(), Scalar(0, 255, 0), 5);

	}
}

void main() {
	string path = "Resources/shapes.png";
	Mat img = imread(path);

	// Preprocessing
	cvtColor(img, imgGray, COLOR_BGR2GRAY);
	GaussianBlur(imgGray, imgBlur, Size(3, 3), 3, 0);
	Canny(imgBlur, imgCanny, 25, 75);

	// getStructuringElement(shape, ksize, anchor=None) 
	// : ũ��� ����� �����ϰ� ������ ��ġ�� ���Ǵ�� ����
	Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
	dilate(imgCanny, imgDil, kernel);

	getContours(imgDil, img);

	imshow("Image", img);
	//imshow("Image Gray", imgGray);
	//imshow("Image Blur", imgBlur);
	//imshow("Image Canny", imgCanny);
	//imshow("Image Dil", imgDil);

	waitKey(0);

}