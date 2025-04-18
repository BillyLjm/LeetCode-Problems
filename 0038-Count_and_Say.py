"""
0038-Count_and_Say.py
Billy.Ljm
18 April 2025

=======
Problem
=======
https://leetcode.com/problems/count-and-say/

The count-and-say sequence is a sequence of digit strings defined by the 
recursive formula:

- countAndSay(1) = "1"
- countAndSay(n) is the run-length encoding of countAndSay(n-1).

Run-length encoding (RLE) is a string compression method that works by replacing 
consecutive identical characters (repeated 2 or more times) with the 
concatenation of the character and the number marking the count of the 
characters (length of the run). For example, to compress the string "3322251" we 
replace "33" with "23", replace "222" with "32", replace "5" with "15" and 
replace "1" with "11". Thus the compressed string becomes "23321511".

Given a positive integer n, return the nth element of the count-and-say sequence.

===========
My Approach
===========
We just have to implement the RLE encoding. But we can use iteration instead of
recursion to save a bit of function overhead

This has a time complexity of O(n), and a space complexity of O(n), where n is 
the argument.
"""

import math

class Solution:
	def countAndSay(self, n: int) -> str:
		nex = '1'
		for _ in range(n-1):
			prev, nex = nex, ''
			cnt = 1
			for i in range(len(prev)):
				if i+1 >= len(prev) or prev[i] != prev[i+1]:
					nex = nex + str(cnt) + prev[i]
					cnt = 1
				else:
					cnt += 1
		return nex

"""
Test cases
"""
if __name__ == "__main__":
	sol = Solution()

	# test case 1
	n = 4
	print(f"countAndSay({n}) = " +
	   str(sol.countAndSay(n)))

	# test case 2
	n = 1
	print(f"countAndSay({n}) = " +
	   str(sol.countAndSay(n)))