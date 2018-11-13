#ifndef SEQUENCEALIGN_H
#define SEQUENCEALIGN_H
#define VERBOSE 0

#include <iostream>
#include <vector>
#include <utility> 

#include <seqan/sequence.h>
#include <seqan/align.h>

typedef seqan::String<int> gene_order;
typedef seqan::Align<gene_order, seqan::ArrayGaps> synteny;
// typedef std::vector< std::vector<int> > pairAlign;

class pairwise_alignment
{
private:
    gene_order A,B;
    seqan::Align<gene_order, seqan::ArrayGaps> align; 
public:
    std::vector<int> A_a,B_a;

    pairwise_alignment() { seqan::resize(seqan::rows(align), 2); }

    pairwise_alignment( std::vector<int> _A, std::vector<int> _B ) 
    {
        seqan::resize(seqan::rows(align), 2);
        A=_A; 
        seqan::assignSource(seqan::row(align,0),A);
        B=_B;
        seqan::assignSource(seqan::row(align,1),B);
    }
    
    void update_A(std::vector<int> _A) {seqan::clear(A); seqan::clear(seqan::rows(align)); A=_A; seqan::assignSource(seqan::row(align,0),A); A_a.clear(); B_a.clear();}
    void update_B(std::vector<int> _B) {seqan::clear(B); seqan::clear(seqan::rows(align)); B=_B; seqan::assignSource(seqan::row(align,1),B); A_a.clear(); B_a.clear();}

    int global_align(int match=0, int mismatch=-1, int gap=-1);
    int global_align_score(int match=0, int mismatch=-1, int gap=-1);

    int local_align(int match=3, int mismatch=-3, int gap_extend=-1, int gap_open=-2);
    int local_align_score(int match=3, int mismatch=-3, int gap_extend=-1, int gap_open=-2);
};

#endif
