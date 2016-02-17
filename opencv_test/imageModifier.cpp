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
	for(int i = 0; i < result.rows; i++)
	{
		Vec3b* p = result.ptr<Vec3b>(i);
		for(int j = 0; j < result.cols; j++)
			{
				Vec3b &pixel = p[j];
				pixel[0] = (maxPoint - depthMap[i][j]+1)*255/maxPoint;
				pixel[1] = depthMap[i][j]*255/maxPoint;;
				pixel[2] = (depthMap[i][j] - minPoint+1)*255/maxPoint;
			}
	}
	return result;
}

/* //todo
Mat imageModifier::imposeEdges(Mat input)
{
	Mat result;
	//cvtColor(input, input, CV_BGR2GRAY);
	result = Scalar::all(0);
	//blur(edges, edges, Size(3,3));
	//Canny(input, input, 10, 30);	
	//cornerHarris(input, input, 2, 3, 0.04); 
	input.copyTo(result);
	return result;
}

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