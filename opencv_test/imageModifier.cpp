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

Mat imageModifier::convertToRGB(vector<vector<double>> depthMap, int stepRatio, double minDelta)
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
				int dirIndx = -1, y, x;
				double depth = depthMap[i][j];
				
				for(int k = 0; k < 8; k++)
				{
					y = i+dir[0][k]*stepRatio;
					x = j+dir[1][k]*stepRatio;
					if(x >= 0 && x < result.cols && y >= 0 && y < result.rows)
						if( abs(depth - depthMap[y][x]) > minDelta && abs(depth - depthMap[y][x]) > maxDelta)
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

Mat imageModifier::detectGroundSurface(Mat edges)
{
	Mat result(edges.rows, edges.cols, CV_8UC1, Scalar(0));
	vector<pair<int,int>> coords;

	for(int i = 0; i < edges.rows; i++)
	{
		for(int j = 0; j < edges.cols; j++)
		{
			if(edges.ptr<uchar>(i)[j]==255)
			{
				vector<pair<int, int>> tmp;
				//iterating through surrounding pixels to find all pixels belonging to this edge. maybe similar to dfs
				dfs(i,j,tmp,edges); 		
				if(tmp.size()>coords.size()) 
					coords = tmp;						
			}
		}
	}

	// painting white the ground surface region 
	for(int i = 0; i < coords.size(); i++)
	{
		for(int j = coords[i].first; j<result.rows; j++)
		{
			result.ptr<uchar>(j)[coords[i].second] = 255;
			//result.ptr<uchar>(coords[i].first)[coords[i].second] = 255;
		}
	}
	return result;
}

Vec3b imageModifier::paintPixel(int direction)
{
	Vec3b result;
	switch(direction)
	{
		case -1:
			result[0] = 50; result[1] = 50; result[2] = 50; //below threshold
		break;

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

void imageModifier::dfs(int y, int x, vector<pair<int,int>> &coord, Mat &edges)
{
	int dir[2][8] = {{0,1,1,1,0,-1,-1,-1},{1,1,0,-1,-1,-1,0,1}};
	coord.push_back(make_pair(y,x));
	edges.ptr<uchar>(y)[x] = 0;
	for(int k = 0; k < 8; k++)
	{
		if(x+dir[1][k] >= 0 && x+dir[1][k] < edges.cols && y+dir[0][k] >= 0 && y+dir[0][k] < edges.rows)
			if(edges.ptr<uchar>(y+dir[0][k])[x+dir[1][k]]==255)
			{
				dfs(y+dir[0][k],x+dir[1][k], coord, edges);
			}
	}
}