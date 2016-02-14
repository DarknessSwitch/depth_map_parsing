#pragma once

#include <opencv2/core.hpp>
#include <opencv2\opencv.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <vector>

using namespace std;

class imageModifier
{
public:
	imageModifier(void);
	~imageModifier(void);
	static cv::Mat convertToGreyscale(vector<vector<double>> depthMap);
};

