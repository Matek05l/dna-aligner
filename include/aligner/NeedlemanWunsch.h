#ifndef NEEDLEMAN_WUNSCH_H
#define NEEDLEMAN_WUNSCH_H
#include <vector>
#include <string>
#include "../utils/AlignmentResult.h"

enum class Direction {
    none, up, left, diagonal
};

class NeedlemanWunsch {
public:
    NeedlemanWunsch(int match = 1, int mismatch = -1, int gap = -1);
    AlignmentResult align(const std::string& seq1, const std::string& seq2);

private:
    int matchScore;
    int mismatchPenalty;
    int gapPenalty;

    using ScoreMatrix = std::vector<std::vector<int>>;
    using TraceMatrix = std::vector<std::vector<Direction>>;

    ScoreMatrix dpMatrix;
    TraceMatrix dirMatrix;

    void fillMatrix(const std::string& seq1, const std::string& seq2);
    AlignmentResult traceback(const std::string& seq1, const std::string& seq2);

};  
#endif