#include <iostream>
#include <vector>
#include <string>
#include "../../include/utils/Printer.h"

using namespace std;
void Printer::print(const AlignmentResult& result)
{
	int ags = result.algndseq1.length();
	cout << "seq1: " << result.algndseq1 << endl;
	string cseq1 = result.algndseq1;
	string cseq2 = result.algndseq2;
	cout << "ilu:  ";
	for (int i = 0; i < ags; i++)
	{
		if (cseq1[i] == '-' || cseq2[i] == '-') 
		{
			cout << ' ';
		}
		else if (cseq1[i] == cseq2[i])           
		{
			cout << '|';
		}
		else                                     
		{
			cout << 'x';
		}
	}
	cout << endl;
	cout << "seq2: " << result.algndseq2 << endl;
	
	
	
	cout << "final score : " << result.score << endl;
	cout << "percentage: " << result.identityperc << endl;
}
