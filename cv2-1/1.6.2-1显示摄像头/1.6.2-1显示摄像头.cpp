// 1.6.2-1显示摄像头.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<opencv2\opencv.hpp>//VideoCapture
using namespace cv;

int main()
{
	system("color 5A");//背景紫色，字绿色
	printf("hello");

	//读取摄像头
	VideoCapture capture(0);

	while (1) {
		Mat frame;
		capture >> frame;//读取当前帧
		imshow("摄像头播放", frame);//显示
		if(waitKey(30)==27) break;
	}
	return 0;
}

