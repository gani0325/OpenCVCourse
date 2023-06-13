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

int main() {
	string path = "Resources/paper.jpg";
	imgOriginal = imread(path);
	resize(imgOriginal, imgOriginal, Size(), 0.5, 0.5);

	// Preprocessing
	imgThre = preProcessing(imgOriginal);
	imshow("image", imgOriginal);
	imshow("image Dial", imgDil);

	waitKey(0);
}