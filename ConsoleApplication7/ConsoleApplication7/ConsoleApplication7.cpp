// ConsoleApplication7.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<opencv2/opencv.hpp>
using namespace cv;


int main()
{
	Mat img = imread("1.jpg");
	imshow("td", img);
	waitKey(6000);
    return 0;
}

