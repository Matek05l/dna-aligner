#include "../../include/aligner/NeedlemanWunsch.h"
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

NeedlemanWunsch::NeedlemanWunsch(int match, int mismatch, int gap) 
	: matchScore(match), mismatchPenalty(mismatch), gapPenalty(gap)
{


}
AlignmentResult NeedlemanWunsch::align(const std::string& seq1, const std::string& seq2)
{
	fillMatrix(seq1, seq2);
	return traceback(seq1, seq2);
}

void NeedlemanWunsch::fillMatrix(const std::string& seq1, const std::string& seq2)
{
	size_t rows = seq1.length() + 1;
	size_t cols = seq2.length() + 1;

	dpMatrix.assign(rows, vector<int>(cols, 0));
	dirMatrix.assign(rows, vector<Direction>(cols, Direction::none));

	for (size_t i = 1; i < rows; i++)
	{
		dpMatrix[i][0] = static_cast<int>(i) * gapPenalty;
		dirMatrix[i][0] = Direction::up;
	}
	for (size_t j = 1; j < cols; j++)
	{
		dpMatrix[0][j] = static_cast<int>(j) * gapPenalty;
		dirMatrix[0][j] = Direction::left;
	}

	for (size_t i = 1; i < rows; i++) {
		for (size_t j = 1; j < cols; j++)
		{
			// diagonal
			int gsp = seq1[i - 1] == seq2[j - 1] ? matchScore : mismatchPenalty;
			int ScoreDiag = dpMatrix[i - 1][j - 1] + gsp;

			// up
			int scoreUp = dpMatrix[i - 1][j] + gapPenalty;

			// left
			int scoreLeft = dpMatrix[i][j - 1] + gapPenalty;

			int maxScore = max({ScoreDiag, scoreUp, scoreLeft});
			dpMatrix[i][j] = maxScore;

			if (maxScore == ScoreDiag)
			{
				dirMatrix[i][j] = Direction::diagonal;
			}
			else if (maxScore == scoreUp)
			{
				dirMatrix[i][j] = Direction::up;
			}
			else
			{
				dirMatrix[i][j] = Direction::left;
			}

		}
	}
}

AlignmentResult NeedlemanWunsch::traceback(const std::string& seq1, const std::string& seq2)

{
	string alignedseq1;
	string alignedseq2;

	size_t i = seq1.length();
	size_t j = seq2.length();
	int score = dpMatrix[i][j];

	//traceback
	while(i > 0 || j > 0)
	{
		Direction dir = dirMatrix[i][j];

		if (dir == Direction::diagonal)
		{
			alignedseq1 += seq1[i - 1];
			alignedseq2 += seq2[j - 1];
			--i; --j;
		}
		else if (dir == Direction::up)
		{
			alignedseq1 += seq1[i - 1];
			alignedseq2 += "-";
			--i;
		}
		else if (dir == Direction::left)
		{
			alignedseq1 += "-";
			alignedseq2 += seq2[j - 1];
			--j;
		}
	}
	//Traceback
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

	return{ alignedseq1, alignedseq2, score, idnper };
}


