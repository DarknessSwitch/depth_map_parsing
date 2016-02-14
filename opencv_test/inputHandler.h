#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

class inputHandler
{	
public:
	inputHandler(void);
	~inputHandler(void);
	static vector<double> parseLineOfDoubles(string line);
	static vector<vector<double>> readInputFile(string filename);
	static double furthestPoint;
};
