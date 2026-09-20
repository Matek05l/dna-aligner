#include "../../include/aligner/SmithWaterman.h"
#include <string>
#include <vector>

using namespace std;

SmithWaterman::SmithWaterman(int match, int mismatch, int gap)
	: matchScore(match), mismatchPenalty(mismatch), gapPenalty(gap)
{

}
AlignmentResult SmithWaterman::align(const string& seq1, const string& seq2)
{
	fillMatrix(seq1, seq2);
	return traceback(seq1, seq2);
}
void SmithWaterman::fillMatrix(const string& seq1, const string& seq2)
{
	size_t rows = seq1.length() + 1;	
	size_t cols = seq2.length() + 1;	

	dpMatrix.assign(rows, vector<int>(cols, 0));
	dirMatrix.assign(rows, vector<DirectionSW>(cols, DirectionSW::none));

	for (size_t i = 1; i < rows; i++){
		for (size_t j = 1; j < cols; j++)
		{
			//diagonal
			int gsp = seq1[i - 1] == seq2[j - 1] ? matchScore : mismatchPenalty;
			int scoreDiag = dpMatrix[i - 1][j - 1] + gsp;

			//Up
			int ScoreUp = dpMatrix[i - 1][j] + gapPenalty;

			//left
			int ScoreLeft = dpMatrix[i][j - 1] + gapPenalty;

			int MaxScore = max({ scoreDiag, ScoreUp, ScoreLeft, 0 });
			dpMatrix[i][j] = MaxScore;

			if (MaxScore == scoreDiag)
			{
				dirMatrix[i][j] = DirectionSW::diagonal;
			}
			else if (MaxScore == ScoreUp)
			{
				dirMatrix[i][j] = DirectionSW::up;
			}
			else
			{
				dirMatrix[i][j] = DirectionSW::left;
			}
		}
	}
}

AlignmentResult SmithWaterman::traceback(const string& seq1, const string& seq2)
{
	string alignedseq1;
	string alignedseq2;

	size_t rows = dpMatrix.size();
	size_t cols = dpMatrix[0].size();
	int maxVal = 0;
	size_t bestI = 0, bestJ = 0;

	for (size_t i = 0; i < rows; i++) {
		for (size_t j = 0; j < cols; j++)
		{
			if (dpMatrix[i][j] > maxVal)
			{
				maxVal = dpMatrix[i][j];
				bestI = i;
				bestJ = j;
			}
		}
	}

	//traceback
	size_t i = bestI;
	size_t j = bestJ;

	while (dpMatrix[i][j] > 0)
	{
		DirectionSW dir = dirMatrix[i][j];

		if (dir == DirectionSW::diagonal)
		{
			alignedseq1 += seq1[i - 1];
			alignedseq2 += seq2[j - 1];
			--i; --j;
		}
		else if (dir == DirectionSW::up)
		{
			alignedseq1 += seq1[i - 1];
			alignedseq2 += "-";
			--i;
		}
		else if (dir == DirectionSW::left)
		{
			alignedseq1 += "-";
			alignedseq2 += seq2[j - 1];
			--j;
		}


	}
	//reverse

	reverse(alignedseq1.begin(), alignedseq1.end());
	reverse(alignedseq2.begin(), alignedseq2.end());

	//identity typerc
	int matches = 0;
	for (size_t k = 0; k < alignedseq1.length(); ++k)
	{
		if (alignedseq1[k] == alignedseq2[k])
		{
			matches++;
		}
	}
	double idnper = 0.0;
	if (!alignedseq1.empty())
	{
		idnper = (static_cast<double>(matches) / alignedseq1.length()) * 100;
	}

	return{ alignedseq1, alignedseq2, maxVal, idnper };
}