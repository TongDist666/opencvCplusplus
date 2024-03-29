// 7.1.5.2Scharr滤波器.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<opencv2\opencv.hpp>
#include<opencv2\imgproc\imgproc.hpp>
#include<opencv2\highgui\highgui.hpp>
using namespace cv;

int main()
{
	system("color 6E");//暗黄色

	Mat grad_x, abs_grad_x, grad_y, abs_grad_y, dst;

	Mat src = imread("1.jpg");

	imshow("scharr滤波器【原图】",src);

	//X方向梯度
	//scharr(输入图像，输出图像，图像深度，x方向差分阶数，y方向差分阶数，计算导数时的缩放因子，结果delta值，边界模式)
	Scharr(src, grad_x, CV_16S, 1, 0, 1, 0, BORDER_DEFAULT);
	convertScaleAbs(grad_x, abs_grad_x);
	imshow("X方向scharr滤波【效果图】", abs_grad_x);

	//Y方向梯度
	Scharr(src, grad_y, CV_16S, 0, 1, 1, 0, BORDER_DEFAULT);
	convertScaleAbs(grad_y, abs_grad_y);
	imshow("Y方向scharr滤波【效果图】", abs_grad_y);

	//合并梯度
	addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, dst);

	imshow("整体方向scharr滤波【效果图】", dst);

	printf("hello");
	while (waitKey(333) != 27) {}
    return 0;
}

