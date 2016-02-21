#include <opencv2/core.hpp>
#include <opencv2\opencv.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <inputHandler.h>
#include <imageModifier.h>

using namespace cv;
using namespace std;

int ratio = 1;
string window_name = "Parsed depth map";
vector<vector<double>> depthMap;
string filePath;
string filename;
Mat image;

void stepRatio(int, void*)
{
  image = imageModifier::convertToRGB(depthMap, ratio);
  imshow( window_name, image );
  // on each trackbar change parsed image and image with edges are saved to the project's folder
  imwrite(filename, image);
  imwrite("edges_"+filename, imageModifier::imposeEdges(image, 120, 360));
}

int main( int argc, char** argv )
{
	if(argc!=2)
	{
		cout<<"please specify the filename\n";
		return -1;
	}
	filePath = argv[1];
	filename = filePath.substr(filePath.find_last_of('\\')+1); filename = filename.erase(filename.find_last_of('.'))+".jpg";

	depthMap = inputHandler::readInputFile(filePath);

	namedWindow(window_name, WINDOW_AUTOSIZE);
	createTrackbar( "Pixel step distance:", window_name, &ratio, 150, stepRatio );
	stepRatio(1,0); // initial creation of window with image
	
    waitKey(0); 
    return 0;
}