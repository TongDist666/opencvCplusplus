// opencv3_8.X.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<opencv2\opencv.hpp>
#include<Windows.h>//Sleep的头文件
using namespace cv;

int main()
{
	RNG suijishu;//随机数产生器
	while (waitKey(1)!=27) {
		printf("随机数：%d\n",suijishu.uniform(0,1024));
		Sleep(1000);
	}
    return 0;
}

