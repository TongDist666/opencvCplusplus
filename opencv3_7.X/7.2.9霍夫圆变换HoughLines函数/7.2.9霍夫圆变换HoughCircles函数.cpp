// 7.2.9霍夫圆变换HoughLines函数.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;
using namespace std;

int main()
{
	system("color 1D");//背景蓝色，文字粉色

	Mat srcImage = imread("1.jpg");
	Mat midImage, dstImage;

	imshow("【原始图】", srcImage);

	cvtColor(srcImage, midImage, COLOR_BGR2GRAY);//转化边缘检测后的图为灰度图
	GaussianBlur(midImage, midImage, Size(9, 9), 2, 2);//此处使用高斯平滑

	//进行霍夫圆变换
	vector<Vec3f> circles;
	HoughCircles(midImage, circles, HOUGH_GRADIENT, 1, 10, 200, 100, 0, 0);
	/*HoughCircles(
		1 输入图像 8位灰度单通，
		2 圆的输出矢量 3个浮点数，
		3 检测方法 默认且对圆只有一种  HOUGH_GRADIENT，
		4 int 输入图像除以累加器分辨率，
		5 double 最小圆心距，
		6 double canny高阈值（低阈值为高阈值一半） 默认100，
		7 double 圆心累加器阈值 默认100（越大对圆要求越多），
		8 int 最小圆半径 默认0，
		9 int 最大圆半径 默认0)
	*/

	//依次在图中绘制出圆
	for (size_t i = 0; i < circles.size(); i++)
	{
		//参数定义
		Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
		int radius = cvRound(circles[i][2]);
		//绘制圆心
		circle(srcImage, center, 3, Scalar(0, 255, 0), -1, 8, 0);
		//绘制圆轮廓
		circle(srcImage, center, radius, Scalar(155, 50, 255), 3, 8, 0);
	}
	imshow("【效果图】", srcImage);
	
	printf("输入ESC 退出");
	while (waitKey(333)!=27) {}
	return 0;
}