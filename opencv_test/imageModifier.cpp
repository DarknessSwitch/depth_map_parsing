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

	int dir[2][8] = {{1,1,0,-1,-1,-1,0,1},{0,1,1,1,0,-1,-1,-1}};

	Mat result(depthMap.size(), depthMap[0].size(), CV_8UC3, Scalar(255,255,255));

	for(int i = 1; i < result.rows-1; i++)
	{
		Vec3b* p = result.ptr<Vec3b>(i);
		for(int j = 1; j < result.cols-1; j++)
			{
				Vec3b &pixel = p[j];
				double maxDelta = 0;
				int dirIndx = 0;
				double depth = depthMap[i][j];
				
				for(int k = 0; k < 8; k++)
				{
					if( abs(depth - depthMap[i+dir[0][k]][j+dir[1][k]]) > maxDelta)
					{
						maxDelta = abs(depth - depthMap[i+dir[0][k]][j+dir[1][k]]);
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

Vec3b imageModifier::paintPixel(int direction)
{
	Vec3b result;
	switch(direction)
	{
		case 0:
			result[0] = 0; result[1] = 0; result[2] = 255; // WEST, RED
		break;

		case 1:
			result[0] = 255; result[1] = 0; result[2] = 205; // NORTH-WEST, VIOLET
		break;

		case 2:
			result[0] = 255; result[1] = 25; result[2] = 0; // NORTH, BLUE
		break;

		case 3:
			result[0] = 255; result[1] = 188; result[2] = 0; //NORTH-EAST, LIGHT-BLUE
		break;
			
		case 4:
			result[0] = 154; result[1] = 255; result[2] = 0; //EAST, LIGHT-GREEN
		break;

		case 5:
			result[0] = 11; result[1] = 170; result[2] = 11; // SOUTH-EAST, GREEN
		break;

		case 6:
			result[0] = 18; result[1] = 255; result[2] = 243; // SOUTH, YELLOW
		break;

		case 7:
			result[0] = 20; result[1] = 115; result[2] = 239; // SOUTH-WEST, ORANGE
		break;

		default:
			result[0] = 255; result[1] = 255; result[2] = 255;
	}
	return result;
}