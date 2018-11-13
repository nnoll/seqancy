from libcpp.vector cimport vector
from libcpp.pair cimport pair

cdef extern from "sequenceAlign.h":
	
	cdef cppclass pairwise_alignment:

		vector[int] A_a
		vector[int] B_a

		pairwise_alignment() except +
		pairwise_alignment(vector[int] _A, vector[int] _B ) except +
		
		void update_A(vector[int] A)
		void update_B(vector[int] B)

		int global_align(int match, int mismatch, int gap)
		int global_align_score(int match, int mismatch, int gap)

		int local_align(int match, int mismatch, int gap_extend, int gap_open)
		int local_align_score(int match, int mismatch, int gap_extend, int gap_open)