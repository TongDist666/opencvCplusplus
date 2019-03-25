// 1.6.1视频读取播放.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<opencv2\opencv.hpp>
using namespace cv;

int main()
{
	system("color 4A");//背景猩红色，字绿色
	printf("hello");

	//读取视频
	VideoCapture capture("1.mp4");
	
	while (1) {
		Mat frame;
		capture >> frame;//读取当前帧
		if (frame.empty()) break;//判断是否结束
		imshow("视频播放", frame);//显示
		if (waitKey(30) == 27) break;
	}
	return 0;
}
//没声音
