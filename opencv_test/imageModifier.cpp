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
Mat imageModifier::convertToRGB(vector<vector<double>> depthMap, int stepRatio)
{

	int dir[2][8] = {{0,1,1,1,0,-1,-1,-1},{1,1,0,-1,-1,-1,0,1}};

	Mat result(depthMap.size(), depthMap[0].size(), CV_8UC3, Scalar(255,255,255));

	for(int i = 0; i < result.rows; i++)
	{
		Vec3b* p = result.ptr<Vec3b>(i);
		for(int j = 0; j < result.cols; j++)
			{
				Vec3b &pixel = p[j];
				double maxDelta = 0;
				int dirIndx = 0, y, x;
				double depth = depthMap[i][j];
				
				for(int k = 0; k < 8; k++)
				{
					y = i+dir[0][k]*stepRatio;
					x = j+dir[1][k]*stepRatio;
					if(x >= 0 && x < result.cols && y >= 0 && y < result.rows)
						if( abs(depth - depthMap[y][x]) > maxDelta)
						{
							maxDelta = abs(depth - depthMap[y][x]);
							dirIndx = k;
						}					
				}
				pixel = paintPixel(dirIndx);
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
	blur(input, input, Size(3,3));
	result = Scalar::all(0);
	Canny(input, input, lowThresh, highThresh);	
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

Vec3b imageModifier::paintPixel(int direction)
{
	Vec3b result;
	switch(direction)
	{
		case 0:
			result[0] = 0; result[1] = 100; result[2] = 0; // WEST
		break;

		case 1:
			result[0] = 25; result[1] = 50; result[2] = 0; // NORTH-WEST
		break;

		case 2:
			result[0] = 0; result[1] = 0; result[2] = 0; // NORTH
		break;

		case 3:
			result[0] = 50; result[1] = 25; result[2] = 0; //NORTH-EAST
		break;
			
		case 4:
			result[0] = 0; result[1] = 100; result[2] = 0; //EAST
		break;

		case 5:
			result[0] = 50; result[1] = 25; result[2] = 255; // SOUTH-EAST
		break;

		case 6:
			result[0] = 75; result[1] = 75; result[2] = 255; // SOUTH
		break;

		case 7:
			result[0] = 25; result[1] = 50; result[2] = 255; // SOUTH-WEST
		break;

		default:
			result[0] = 255; result[1] = 255; result[2] = 255;
	}
	return result;
}