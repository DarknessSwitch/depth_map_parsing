#include "inputHandler.h"

double inputHandler::furthestPoint;

inputHandler::inputHandler()
{
	inputHandler::furthestPoint = 255;
}

// the function only expects a line of doubles separated with whitespaces, has no argument validation 
vector<double> inputHandler::parseLineOfDoubles (string line) 
{
	vector<double> result;
	int pos = 0;
	int spacePosition = line.find(" ", pos);
	double tmp;
	while(spacePosition!=-1)
	{
		tmp = stod(line.substr(pos, spacePosition));
		inputHandler::furthestPoint = max(tmp, inputHandler::furthestPoint);
		result.push_back(tmp);

		pos = spacePosition+1;		
		spacePosition = line.find(" ", pos);
	}	
	return result;
}

vector<vector<double>> inputHandler::readInputFile(string filename)
{
	vector<vector<double>> result;
	string line;
	ifstream is(filename);
	if(is.is_open())
	{
		cout<<"Reading the file...\n";
		while( getline(is, line))
		{
			vector<double> tmp(parseLineOfDoubles(line));
			result.push_back( tmp );
		}
		is.close();
		cout<<filename<<" has been read successfully.\n";
	}
	else
	{
		cout<<filename<<" could not be opened!\n";
	}
	return result;
}
