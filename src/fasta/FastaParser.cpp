#include "../../include/fasta/FastaParser.h"
#include <iostream>
#include <fstream>
using namespace std;

vector<pair<string, string>> FastaParser::parse(string filePath)
{
    vector<pair<string, string>> result;
    ifstream DnaSeq(filePath);


    if (!DnaSeq.is_open())
    {
        cerr << "b³ad z plikiem FASTA" << filePath << endl;
        return result;
    }

    string line;
    string currentHeader = "";
    string currentSequence = "";

    while (getline(DnaSeq, line))
    {
        if (line.empty()) continue;

        if (line[0] == '>')
        {
            if (!currentHeader.empty())
                result.push_back({ currentHeader, currentSequence });
            currentHeader = line.substr(1);
            currentSequence = "";


        }
        else
        {
            currentSequence += line;
        }



        
    }
    if (!currentHeader.empty())
    {
        result.push_back({ currentHeader, currentSequence });
    }
    DnaSeq.close();
    return result;  
}