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
	string filename = argv[1];
	vector<vector<double>> depthMap = inputHandler::readInputFile(filename);

	Mat greyscaleImage = imageModifier::convertToGreyscale(depthMap);
	imwrite("greyscale.jpg", greyscaleImage);
	namedWindow("Greyscale image", WINDOW_AUTOSIZE);
	imshow("Greyscale image", greyscaleImage);
	
    waitKey(0); // Wait for a keystroke in the window
    return 0;
}