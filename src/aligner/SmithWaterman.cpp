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
		}
	}
}