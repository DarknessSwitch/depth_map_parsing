#include <opencv2/core.hpp>
#include <opencv2\opencv.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <inputHandler.h>
#include <imageModifier.h>

using namespace cv;
using namespace std;

int main( int argc, char** argv )
{
	if(argc!=2)
	{
		cout<<"please specify the filename\n";
		return -1;
	}
	string filePath = argv[1];
	string filename = filePath.substr(filePath.find_last_of('\\')+1); filename = filename.erase(filename.find_last_of('.'))+".jpg";

	vector<vector<double>> depthMap = inputHandler::readInputFile(filePath);
	Mat greyscaleImage = imageModifier::convertToRGB(depthMap, inputHandler::furthestPoint, inputHandler::closestPoint);
	imwrite(filename, greyscaleImage);// greyscale is saved to the project's folder
	namedWindow("Greyscale image", WINDOW_AUTOSIZE);
	imshow("Greyscale image", greyscaleImage);
	
    waitKey(0); 
    return 0;
}