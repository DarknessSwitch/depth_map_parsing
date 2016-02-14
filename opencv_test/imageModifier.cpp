#include "imageModifier.h"

using namespace cv;
using namespace std;

Mat imageModifier::convertToGreyscale(vector<vector<double>> depthMap)
{
	Mat result(depthMap.size(), depthMap[0].size(), CV_8UC1, 1);
	for(int i = 0; i < result.rows; i++)
	{
		uchar* p = result.ptr<uchar>(i);
		for(int j = 0; j < result.cols; j++)
			{
				uchar color = (depthMap[i][j]*255) /20000;
				p[j] = color;
			}
	}
	return result;
}
