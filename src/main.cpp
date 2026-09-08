#include <iostream>
#include <vector>
#include <cstdlib>
#include "../include/fasta/FastaParser.h"
#include "../include/aligner/ScoringMatrix.h"
#include "../include/aligner/NeedlemanWunsch.h"
#include "../include/utils/Printer.h"

using namespace std;



int main() 
{
	cout << "---FASTA PARSER---" << endl;

	auto sequences = FastaParser::parse("data/dna.fasta");
    for ( const auto& seqPair : sequences) {
        cout << "Header: " << seqPair.first << endl;
        cout << "Sequence: " << seqPair.second << endl;
        cout << "----------------------" << endl;
    }
    FastaParser parser;
    vector<pair<string, string>>records = parser.parse("data/dna.fasta");
    string sequence1 = records[0].second;
    string sequence2 = records[1].second;

    /*
    cout << "----- MATRIX -----" << endl;
    ScoringMatrix smatrix;
    smatrix.openblos("matrices/BLOSUM62.txt");

    cout << "Podaj aminokwasy \n";
    char aaac, baac;
    cin >> aaac >> baac;
    cout << smatrix.getScore(aaac, baac);    
    */
    cout << "---- NWA ---- \n";
    NeedlemanWunsch nwalgorithm(1, -1, -1);

    AlignmentResult result = nwalgorithm.align(sequence1, sequence2);

    Printer showp;
    showp.print(result);
}
    
