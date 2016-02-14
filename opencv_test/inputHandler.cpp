#include "inputHandler.h"

// the function only expects a line of doubles separated with whitespaces, has no argument validation 
vector<double> inputHandler::parseLineOfDoubles (string line) 
{
	vector<double> result;
	int pos = 0;
	int spacePosition = line.find(" ", pos);
	while(spacePosition!=-1)
	{
		result.push_back(stod(line.substr(pos, spacePosition)));
		pos = spacePosition+1;		
		spacePosition = line.find(" ", pos);
	}	
	return result;
}

vector<vector<double>> inputHandler::readInputFile(string filename)
{
	vector<vector<double>> result;
	double tmp;
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
