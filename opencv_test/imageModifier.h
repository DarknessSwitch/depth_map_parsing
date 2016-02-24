#pragma once

#include <opencv2/core.hpp>
#include <opencv2\opencv.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <vector>

using namespace std;
using namespace cv;

class imageModifier
{
private:
	static Vec3b paintPixel(int direction);
	static void dfs(int y, int x, vector<pair<int,int>> &coord, Mat &edges);
public:
	imageModifier(void);
	~imageModifier(void);
	static Mat convertToGreyscale(vector<vector<double>> depthMap, double furthestPoint);
	static Mat convertToRGB(vector<vector<double>> depthMap, int stepRatio, double minDelta);
	static Mat imposeEdges(Mat input, int lowThresh, int highThresh);
	static Mat detectGroundSurface(Mat edges);
};

