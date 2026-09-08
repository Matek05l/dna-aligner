# DNA Sequence Aligner

A C++ command-line tool for pairwise biological sequence alignment.  
Implements **Needleman-Wunsch** (global) and **Smith-Waterman** (local) algorithms.

## Features

- Global alignment — Needleman-Wunsch algorithm
- Local alignment — Smith-Waterman algorithm
- FASTA file parsing (multi-sequence files supported)
- BLOSUM62 substitution matrix for protein sequences
- Alignment visualization with match/mismatch/gap indicators
- Identity percentage calculation

## Project Structure
dna-aligner/
├── include/
│ ├── aligner/ # NeedlemanWunsch, SmithWaterman, ScoringMatrix
│ ├── fasta/ # FastaParser
│ └── utils/ # AlignmentResult, Printer
├── src/ # implementations
├── data/ # sample FASTA files
├── matrices/ # BLOSUM62 substitution matrix
└── tests/ # unit tests
## Sample Data

| File | Organism | Source |
|------|----------|--------|
| `data/dna.fasta` | *Danio rerio* / *Homo sapiens* BRCA1 | NCBI NM_131263, NM_007293 |
| `data/protein.fasta` | Hemoglobin alpha | NCBI NP_000549 |

## Algorithms

**Needleman-Wunsch** — global alignment. Aligns two sequences end-to-end.  
Best used when sequences are of similar length.

**Smith-Waterman** — local alignment. Finds the best matching subsequence.  
Best used when one sequence may be a fragment of another.
