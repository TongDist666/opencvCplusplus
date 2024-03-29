// 1.5.2图像腐蚀.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<opencv2\highgui\highgui.hpp>
#include<opencv2\imgproc\imgproc.hpp>
using namespace cv;
//opencv 最基本的形态学运算之一  腐蚀
//即，用图中的暗色部分“腐蚀”掉高亮部分
int main()
{
	Mat srcImage = imread("1.jpg");
	imshow("原图_腐蚀操作",srcImage);

	//进行腐蚀操作
	//getStructuringElement返回值为指定形状和尺寸的结构元素（内核矩阵），用Mat类型变量接收
	Mat element = getStructuringElement(MORPH_RECT, Size(5,5));//size内数字越小，腐蚀块越小
	Mat dstImage;

	//erode函数对图像进行腐蚀操作
	//    目标图片   结果     腐蚀参数
	erode(srcImage, dstImage, element);
	imshow("腐蚀图_腐蚀操作", dstImage);
	waitKey(0);
    return 0;
}

