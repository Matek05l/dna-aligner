#ifndef SCORING_MATRIX_H
#define SCORING_MATRIX_H
#include <string>
#include <vector>
#include <sstream>

class ScoringMatrix {
public:
	void openblos(std::string blosfilepath);
	int getScore(char a, char b) const;
private:
	int matrix[24][24];
	int ltoindex[256];
};


#endif 
 
