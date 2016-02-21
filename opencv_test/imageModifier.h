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
public:
	imageModifier(void);
	~imageModifier(void);
	static Mat convertToGreyscale(vector<vector<double>> depthMap, double furthestPoint);
	static Mat convertToRGB(vector<vector<double>> depthMap, int stepRatio);
	static Mat imposeEdges(Mat input, int lowThresh, int highThresh);
	static Mat convertToMat(vector<vector<double>>);
};

