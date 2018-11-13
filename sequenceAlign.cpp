#include "sequenceAlign.h"

int pairwise_alignment::global_align(int match, int mismatch, int gap)
{
    int score = seqan::globalAlignment(align,seqan::Score<int, seqan::Simple>(match,mismatch,gap));
    auto alignA = seqan::row(align,0);
    auto alignB = seqan::row(align,1);

    A_a.resize(seqan::length(alignA));
    B_a.resize(seqan::length(alignB));

    for (size_t n=0; n < A_a.size(); ++n)
        A_a[n] = alignA[n];
    
    for (size_t n=0; n < B_a.size(); ++n)
        B_a[n] = alignB[n];

    std::vector< std::vector<int> > pair_align = {A_a,B_a};
    return score;
}

int pairwise_alignment::global_align_score(int match, int mismatch, int gap)
{ 
    int score = seqan::globalAlignment(align,seqan::Score<int, seqan::Simple>(match,mismatch,gap)); 
    return score;
}

int pairwise_alignment::local_align(int match, int mismatch, int gap_extend, int gap_open)
{
    int score = seqan::localAlignment(align,seqan::Score<int>(match,mismatch,gap_extend,gap_open) );
    auto alignA = seqan::row(align,0);
    auto alignB = seqan::row(align,1);

    int minA = seqan::clippedBeginPosition(alignA);
    int maxA = seqan::clippedEndPosition(alignA);
    int minB = seqan::clippedBeginPosition(alignB);
    int maxB = seqan::clippedEndPosition(alignB);

    A_a.clear();
    B_a.clear();
    A_a.resize(maxA-minA);
    B_a.resize(maxB-minB);

    std::cout << "(" << minA << "," << maxA << ")\n";
    std::cout << "(" << minB << "," << maxB << ")\n";

    std::cout << "A LENGTH " << seqan::length(A) << "\n";
    std::cout << "B LENGTH " << seqan::length(B) << "\n";
    
    // for (size_t n=0; n<A_a.size(); ++n)
    size_t n = 0;
    for (auto c: alignA)
    {
        A_a[n] = c;
        n++;
    }
    
    n = 0;
    for (auto c: alignB)
    {
        B_a[n] = c;
        n++;
    }

    return score;
}

int pairwise_alignment::local_align_score(int match, int mismatch, int gap_extend, int gap_open)
{
    int score = seqan::localAlignment(align,seqan::Score<int>(match,mismatch,gap_extend,gap_open) );
    return score;
}

int main()
{
    std::vector<int> A = {0,1,2,3,5};
    std::vector<int> B = {0,1,2,6,5};

    pairwise_alignment pA(A,B);
    std::cout << pA.global_align() << "\n";
    return 0;
}
