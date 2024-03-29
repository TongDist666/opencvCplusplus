// 9.4.7反向投影.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
using namespace cv;

#define WINDOW_NAME1 "【原始图】"
#define WINDOW_NAME2 "【效果图】"

Mat g_srcImage; Mat g_hsvImage; Mat g_hueImage;
int g_bins = 30;//直方图组距

void on_BinChange(int, void*);

int main()
{
	system("color 1B");//深蓝色背景，字靛色
	
	//【1】读取源图像，并转换到 HSV 空间
	g_srcImage = imread("1.jpg", 1);
	if (!g_srcImage.data) { printf("读取图片错误，请确定目录下是否有imread函数指定图片存在~！ \n"); return false; }
	cvtColor(g_srcImage, g_hsvImage, COLOR_BGR2HSV);

	//【2】分离 Hue 色调通道
	g_hueImage.create(g_hsvImage.size(), g_hsvImage.depth());
	int ch[] = { 0, 0 };
	mixChannels(&g_hsvImage, 1, &g_hueImage, 1, ch, 1);
	/*
	mixChannels(
		1 const mat*输入数组src
		2 size_t src输入矩阵数
		3 Mat*输出数组dst  必须初始化且大小深度和src[0]相同
		4 size_t dst矩阵数
		5 const int* 对指定通道进行复制的数组索引
		6 size_t上一参数的索引数
	)
	*/

	//【3】创建 Trackbar 来输入bin的数目
	namedWindow(WINDOW_NAME1, WINDOW_AUTOSIZE);
	namedWindow(WINDOW_NAME2, WINDOW_AUTOSIZE);
	createTrackbar("色调组距 ", WINDOW_NAME2, &g_bins, 180, on_BinChange);
	on_BinChange(0, 0);//进行一次初始化

					   //【4】显示效果图
	imshow(WINDOW_NAME1, g_srcImage);

	printf("按ESC退出");
	while (waitKey(333) != 27) {}
	return 0;
}

void on_BinChange(int, void*)
{
	//【1】参数准备
	MatND hist;
	int histSize = MAX(g_bins, 2);
	float hue_range[] = { 0, 180 };
	const float* ranges = { hue_range };

	//【2】计算直方图并归一化
	calcHist(&g_hueImage, 1, 0, Mat(), hist, 1, &histSize, &ranges, true, false);
	normalize(hist, hist, 0, 255, NORM_MINMAX, -1, Mat());

	//【3】计算反向投影
	MatND backproj;
	calcBackProject(&g_hueImage, 1, 0, hist, backproj, &ranges, 1, true);
	/*
	calcBackProject（
		1 const Mat*类型 输入数组 深度：CV_8U或CV_32F 通道任意
		2 int 输入数组个数
		3 const int*需要统计的通道索引，第一个数组通道从0到image[0].channels()-1,第二个数组通道从image[0].channels()计算到image[0].channels()+image[1].channels()-1
		4 输入直方图
		5 目标反向投影阵列，单通，和image[0]有相同大小和深度
		6 const float**每一维数值的取值范围数组
		7 double 默认1 输出的方向投影可选的缩放因子
		8 bool 指示直方图是否均匀的标识符 默认TRUE
	）
	*/


	//【4】显示反向投影
	imshow(WINDOW_NAME2, backproj);

	//【5】绘制直方图的参数准备
	int w = 400; int h = 400;
	int bin_w = cvRound((double)w / histSize);
	Mat histImg = Mat::zeros(w, h, CV_8UC3);

	//【6】绘制直方图
	for (int i = 0; i < g_bins; i++)
	{
		rectangle(histImg, Point(i*bin_w, h), Point((i + 1)*bin_w, h - cvRound(hist.at<float>(i)*h / 255.0)), Scalar(100, 123, 255), -1);
	}

	//【7】显示直方图窗口
	imshow("直方图", histImg);
}