// 5.2.1感兴趣区域ROI.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

bool  ROI_AddImage();
bool  LinearBlending();
bool  ROI_LinearBlending();
void   ShowHelpText();

int main()
{
	//命令行翔黄色
	system("color 6F");

	if (ROI_AddImage() && LinearBlending() && ROI_LinearBlending())//相当于把这三个函数都运行了
	{
		cout << endl << "\n运行成功，得出了需要的图像";
	}

	waitKey(0);
	return 0;
}

//----------------------------------【ROI_AddImage( )函数】----------------------------------
// 函数名：ROI_AddImage（）
//	描述：利用感兴趣区域ROI实现图像叠加，直接将插入处的像素设为logo的像素，效果很逼真
//----------------------------------------------------------------------------------------------
bool  ROI_AddImage()
{

	// 【1】读入图像
	Mat srcImage1 = imread("dota_pa.jpg");
	Mat logoImage = imread("dota_logo.jpg");
	if (!srcImage1.data) { printf("读取srcImage1错误~！ \n"); return false; }
	if (!logoImage.data) { printf("读取logoImage错误~！ \n"); return false; }

	// 【2】定义一个Mat类型并给其设定ROI区域
	Mat imageROI = srcImage1(Rect(200, 250, logoImage.cols, logoImage.rows));

	// 【3】加载掩模（必须是灰度图）
	Mat mask = imread("dota_logo.jpg", 0);

	//【4】将掩膜拷贝到ROI
	//                区域     目标
	logoImage.copyTo(imageROI, mask);

	// 【5】显示结果
	namedWindow("<1>利用ROI实现图像叠加示例窗口");
	imshow("<1>利用ROI实现图像叠加示例窗口", srcImage1);

	return true;
}


//---------------------------------【LinearBlending（）函数】-------------------------------------
// 函数名：LinearBlending（）
// 描述：利用cv::addWeighted（）函数实现图像线性混合
//--------------------------------------------------------------------------------------------
bool  LinearBlending()
{
	//【0】定义一些局部变量
	double alphaValue = 0.5;
	double betaValue;
	Mat srcImage2, srcImage3, dstImage;

	// 【1】读取图像 ( 两幅图片需为同样的类型和尺寸 )
	srcImage2 = imread("mogu.jpg");
	srcImage3 = imread("rain.jpg");

	if (!srcImage2.data) { printf("读取srcImage2错误！ \n"); return false; }
	if (!srcImage3.data) { printf("读取srcImage3错误！ \n"); return false; }

	// 【2】进行图像混合加权操作
	betaValue = (1.0 - alphaValue);

	//void addWeighted(InputArray src1, double alpha, InputArray src2,double beta, double gamma, OutputArray dst, int dtype = -1);
	//                 第一个数组或mat   目标一权重    第二个目标      目标二权重    偏移量        输出目标      输出阵列可选深度（输入数组深度相同时，参数设为-1）
	//注意：输出数组深度为CV_32S（=4）时，函数不适用，会出现内存溢出或计算结果出错
	addWeighted(srcImage2, alphaValue, srcImage3, betaValue, 0.0, dstImage);//均匀混合
	//这里输入的两个数组必须有相同的尺寸和类型

	// 【3】显示原图窗口
	imshow("<2>线性混合示例窗口【原图】", srcImage2);
	imshow("<3>线性混合示例窗口【效果图】", dstImage);

	return true;

}

//---------------------------------【ROI_LinearBlending（）】-------------------------------------
// 函数名：ROI_LinearBlending（）
// 描述：线性混合实现函数,指定区域线性图像混合.利用cv::addWeighted（）函数结合定义
//			  感兴趣区域ROI，实现自定义区域的线性混合
//--------------------------------------------------------------------------------------------
bool  ROI_LinearBlending()
{

	//【1】读取图像
	Mat srcImage4 = imread("dota_pa.jpg", 1);
	Mat logoImage = imread("dota_logo.jpg");

	if (!srcImage4.data) { printf("读取srcImage4错误~！ \n"); return false; }
	if (!logoImage.data) { printf("读取logoImage错误~！ \n"); return false; }

	//【2】定义一个Mat类型并给其设定ROI区域
	Mat imageROI;
	//方法一
	imageROI = srcImage4(Rect(200, 250, logoImage.cols, logoImage.rows));
	//方法二
	//imageROI= srcImage4(Range(250,250+logoImage.rows),Range(200,200+logoImage.cols));

	//【3】将logo加到原图上
	addWeighted(imageROI, 0.5, logoImage, 0.3, 0., imageROI);//原图0.5，logo0.3 加权混合

	//【4】显示结果
	imshow("<4>区域线性图像混合示例窗口", srcImage4);

	return true;
}