from cython.operator import dereference as deref, preincrement as inc, address as at
cimport utils

cimport numpy as np
import numpy 

cdef class seqAlign:

	cdef pairwise_alignment* PA # Holds the class we wish to wrap
	
	def __cinit__(self, **kwargs):
		if ('A' in kwargs and 'B' in kwargs):
			self.PA = new pairwise_alignment(kwargs['A'],kwargs['B'])
		else:
			self.PA = new pairwise_alignment()

	def __dealloc__(self):
		del self.PA

	def setA(self,A):
		self.PA.update_A(A)
	
	def setB(self,B):
		self.PA.update_B(B)
	
	def globalAlign(self,int match=0,int mismatch=-1, int gap=-1, return_align=False):
		if (return_align):
			score = self.PA.global_align(match,mismatch,gap)
			return score,numpy.array(self.PA.A_a),numpy.array(self.PA.B_a)
		else:
			score = self.PA.global_align(match,mismatch,gap)
			return score

	def localAlign(self, int match=5, int mismatch=-5, int gap_extend=-1, int gap_open=-3, return_align=False):
		if (return_align):
			score = self.PA.local_align(match, mismatch, gap_extend, gap_open)
			return score,numpy.array(self.PA.A_a),numpy.array(self.PA.B_a)
		else:
			score = self.PA.local_align_score(match, mismatch, gap_extend, gap_open)
			return score