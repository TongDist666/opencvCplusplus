// 5.1.4计时函数.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<opencv2\core\core.hpp>
#include<iostream>
using namespace cv;
using namespace std;
/*
getTickCount()
返回当前已经走过的cpu时钟数

getTickFrequency()
返回一秒钟走过的时钟周期数
*/
int main()
{
	int j = 1;
	double time0 = static_cast<double>(getTickCount());
	for (int i = 0; i < 1000; i++) {
		j = j + i;
	}
	time0 = ((double)getTickCount() - time0) / getTickFrequency();
	cout<<" 运行时间："<< time0 <<endl<<j<<endl;
	system("pause");
    return 0;
}

