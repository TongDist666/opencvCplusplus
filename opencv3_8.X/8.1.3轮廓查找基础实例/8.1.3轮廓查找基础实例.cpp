// 8.1.3轮廓查找基础实例.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <opencv2/opencv.hpp>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
	system("color 7D");//背景灰白色，字粉色

	// 【1】载入原始图，且必须以二值图模式载入
	Mat srcImage = imread("1.jpg", 0);
	imshow("原始图", srcImage);

	//【2】初始化结果图
	Mat dstImage = Mat::zeros(srcImage.rows, srcImage.cols, CV_8UC3);

	//【3】srcImage取大于阈值119的那部分
	srcImage = srcImage > 119;
	imshow("取阈值后的原始图", srcImage);

	//【4】定义轮廓和层次结构
	vector<vector<Point> > contours;//轮廓
	vector<Vec4i> hierarchy;

	//【5】查找轮廓
	//此句代码的OpenCV2版为：
	//findContours( srcImage, contours, hierarchy,CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE );
	//此句代码的OpenCV3版为：
	findContours(srcImage, contours, hierarchy, RETR_CCOMP, CHAIN_APPROX_SIMPLE);
	/*
	findContours(
		1 输入图像 8位单通二进制（函数会在提取轮廓的同时修改图像内容）
		2 输出 vector<vector<Point> > contours检测到的轮廓
		3 输出向量 包含图像的拓扑结构 vector<Vec4i> hierarchy 其中每个contours[i]包含4个元素hierarchy[i][0]~[i][3]表示前一轮廓、后一轮廓、父轮廓和内嵌轮廓索引编号，没有对应项的hierarchy[i]设为负数
		4 int 轮廓检索模式
			i）RETR_EXTERNAL只检测最外层轮廓，对所有轮廓设置hierarchy[i][2]=hierarty[i][3]=1
			ii）RETR_LIST提取所有轮廓提取到list中，轮廓不设等级关系
			iii）RETR_CCOMP提取所有轮廓，将其组织为双层结构
			iv）RETR_TREE提取所有轮廓，重新建立网状的轮廓结构
			Opencv2中要加前缀CV_
		5 int 轮廓近似办法
			i）CHAIN_APPROX_NONE获取每个轮廓的每个像素，相邻两个像素的位置不能超过1
			ii）CHAIN_APPROX_SIMPLE压缩水平、垂直和对角线方向上的元素，只保留该方向的终点坐标
		6 point 轮廓点的可选偏移量
	)
	*/

	// 【6】遍历所有顶层的轮廓， 以随机颜色绘制出每个连接组件颜色
	int index = 0;
	for (; index >= 0; index = hierarchy[index][0])
	{
		Scalar color(rand() & 255, rand() & 255, rand() & 255);
		//此句代码的OpenCV2版为：
		//drawContours( dstImage, contours, index, color, CV_FILLED, 8, hierarchy );
		//此句代码的OpenCV3版为：
		drawContours(dstImage, contours, index, color, FILLED, 8, hierarchy);
		/*
		drawContours(
			1 输入图像 mat就行
			2 输入轮廓 vector<vector<Point> >
			3 int 轮廓绘制指示变量 负数是绘制所有轮廓
			4 const scalar& 轮廓颜色
			5 int 轮廓线条粗细 默认1 负值是绘制在轮廓内部（也可以填FILLED）
			6 int 线条类型 默认8 
				8       8联通
				4       4联通
				LINE_AA 抗锯齿类型
			7 hierarchy 可选的层次结构信息 默认noArray（）
			8 int 绘制轮廓的最大等级 默认INT_MAX
			9 point 可选的轮廓偏移参数 默认Point（）
		)
		*/
	}

	//【7】显示最后的轮廓图
	imshow("轮廓图", dstImage);

	printf("按ESC退出");
	while (waitKey(333) != 27) {}
	return 0;
}