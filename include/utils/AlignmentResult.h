#ifndef ALIGNMENT_RESULT_H
#define ALIGNMENT_RESULT_H

#include <string>
struct AlignmentResult
{
	std::string algndseq1;
	std::string algndseq2;
	int score;
	double identityperc;
};

#endif