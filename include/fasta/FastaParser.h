#ifndef FASTA_PARSER_H
#define FASTA_PARSER_H

#include <string>
#include <vector>
#include <utility>

class FastaParser
{
public:
	static std::vector < std::pair < std::string, std::string >> parse(std::string filePath);
};

#endif
