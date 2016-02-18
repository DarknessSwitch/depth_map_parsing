#include "imageModifier.h"

using namespace cv;
using namespace std;

Mat imageModifier::convertToGreyscale(vector<vector<double>> depthMap, double maxPoint)
{
	Mat result(depthMap.size(), depthMap[0].size(), CV_8UC1);
	for(int i = 0; i < result.rows; i++)
	{
		uchar* p = result.ptr<uchar>(i);
		for(int j = 0; j < result.cols; j++)
			{
				uchar color = (depthMap[i][j]*255) / (maxPoint);
				p[j] = color;
			}
	}
	return result;
}

// todo
Mat imageModifier::convertToRGB(vector<vector<double>> depthMap, double maxPoint, double minPoint)
{
	Mat result(depthMap.size(), depthMap[0].size(), CV_8UC3);
	double closeBorder = minPoint + (maxPoint - minPoint)/3;
	double farBorder = maxPoint - (maxPoint - minPoint)/3;
	double mid = maxPoint - (maxPoint - minPoint)/2;
	for(int i = 0; i < result.rows; i++)
	{
		Vec3b* p = result.ptr<Vec3b>(i);
		for(int j = 0; j < result.cols; j++)
			{
				double depth = depthMap[i][j];
				Vec3b &pixel = p[j];
				/*if(depth < closeBorder)
				{
					pixel[0] = depth*(closeBorder-minPoint)/(maxPoint-minPoint) * 255 / maxPoint;
					pixel[1] = (depth - minPoint) * 255 / maxPoint;
					pixel[2] = (depth - minPoint)/2 * 255 / maxPoint;
				}
				else if(depth>= closeBorder && depth < farBorder)
				{
					pixel[0] = depth * 255 / (closeBorder - minPoint);
					pixel[1] = depth * 255 / maxPoint;
					pixel[2] = (depth - minPoint)/2 * 255 / maxPoint;
				}
				else
				{
					pixel[0] = (maxPoint - depth)/2 * 255 / maxPoint;		
					pixel[1] = (maxPoint - depth) * 255 / maxPoint;
					pixel[2] = depth*(maxPoint-farBorder)/(maxPoint-minPoint) * 255 / maxPoint;					
				}*/
				if(depth < mid)
				{
					pixel[0] = depth*(mid-minPoint)/(maxPoint-minPoint) * 255 / maxPoint;
					pixel[1] = (mid - depth) * 255 / maxPoint;
					pixel[2] = (mid - depth)/2 * 255 / maxPoint;
				}
				else
				{
					pixel[0] = (depth - mid)/2 * 255 / maxPoint;
					pixel[1] = (depth - mid) * 255 / maxPoint;
					pixel[2] = depth*(maxPoint - mid)/(maxPoint-minPoint) * 255 / maxPoint;
				}
			}
	}
	return result;
}

 
 //todo
Mat imageModifier::imposeEdges(Mat input, int lowThresh, int highThresh)
{
	Mat result;
	if(input.channels() > 1)
	{ 
		cvtColor(input, input, CV_BGR2GRAY);
	}
	//blur(input, input, Size(3,3));
	result = Scalar::all(0);
	Canny(input, input, lowThresh, highThresh, 5, false);	
	input.copyTo(result);
	return result;
}

/*
//todo?
Mat imageModifier::convertToMat(vector<vector<double>> depthMap)
{
	Mat result(depthMap.size(), depthMap[0].size(), CV_64FC1);
	for(int i = 0; i < result.rows; i++)
	{
		double* p = result.ptr<double>(i);
		for(int j = 0; j < result.cols; j++)
			{
				double pixel = depthMap[i][j];
				p[j] = pixel;
			}
	}
	return result;
}*/