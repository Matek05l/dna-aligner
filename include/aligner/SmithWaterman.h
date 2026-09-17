#ifndef SMITH_WATERMAN_H
#define SMITH_WATERMAN_H
#include <string>
#include <vector>
#include "../utils/AlignmentResult.h"

enum class DirectionSW {none, up, left, diagonal};

class SmithWaterman {
public:
	SmithWaterman(int match = 3, int mismatch = -1, int gap = -2);
	AlignmentResult align(const std::string& seq1, const std::string& seq2);

private:
	int matchScore;
	int mismatchPenalty;
	int gapPenalty;

	using ScoreMatrix = std::vector<std::vector<int>>;
	using TraceMatrix = std::vector<std::vector<DirectionSW>>;

	ScoreMatrix dpMatrix;
	TraceMatrix dirMatrix;

	void fillMatrix(const std::string& seq1, const std::string& seq2);
	AlignmentResult traceback(const std::string& seq1, const std::string& seq2);

};

#endif 

