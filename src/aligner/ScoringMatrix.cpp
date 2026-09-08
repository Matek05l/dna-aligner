#include "../../include/aligner/ScoringMatrix.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;


	void ScoringMatrix::openblos(string blosfilepath)
	{
		ifstream blosdata(blosfilepath);
		string line;

		if (!blosdata.is_open())
		{
			cerr << "b³¹d z plikiem txt" << blosfilepath << endl;
			return;
		}


		//h
		bool ihr = false;
		int rowindex = 0;

		while (getline(blosdata, line))
		{
			if (line.empty() || line[0] == '#') continue;

			stringstream ss(line);


			if (!ihr) 
			{
				char aa;
				int index = 0;
				while (ss >> aa)
				{
					ltoindex[static_cast<unsigned char>(aa)] = index;
					index++;
				}
				ihr = true;
				continue;
			}
			
			char rletter;
			ss >> rletter;

			int val;
			int colindex = 0;
			while (ss >> val)
			{
				matrix[rowindex][colindex] = val;
				colindex++;
			}
			rowindex++;
			
		}
		blosdata.close();
	}

	int ScoringMatrix::getScore(char a, char b) const
	{

		int idxA = ltoindex[static_cast<unsigned char>(a)];
		int idxB = ltoindex[static_cast<unsigned char>(b)];


		return matrix[idxA][idxB];
		
	}




