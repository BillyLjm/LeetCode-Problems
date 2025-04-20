"""
0781-Rabbits_in_Forest.py
Billy.Ljm
20 April 2025

=======
Problem
=======
https://leetcode.com/problems/rabbits-in-forest/

There is a forest with an unknown number of rabbits. We asked n rabbits "How 
many rabbits have the same color as you?" and collected the answers in an 
integer array answers where answers[i] is the answer of the ith rabbit.

Given the array answers, return the minimum number of rabbits that could be in 
the forest.

===========
My Approach
===========
The minimum number is achieved when we group the rabbits who reported similar
numbers together. If 5 rabbits report 2, then we group them in ceil(5/3) groups.
The the number of rabbits will be the number of groups times the size of each.

This has a time complexity of O(n), and a space complexity of O(n), where n is 
the number of rabbits.
"""

import math
from collections import Counter

class Solution:
	def numRabbits(self, answers: list[int]) -> int:
		# count number of each response
		freq = Counter()
		for i in answers:
			freq[i+1] += 1
		# count number of groups
		for i in freq:
			freq[i] = math.ceil(freq[i] / i)
		# count minimum number
		cnt = 0
		for i in freq:
			cnt += freq[i] * i
		return cnt

"""
Test cases
"""
if __name__ == "__main__":
	sol = Solution()

	# test case 1
	answers = [1,1,2]
	print(f"numRabbits({answers}) = " +
	   str(sol.numRabbits(answers)))

	# test case 2
	answers = [10,10,10]
	print(f"numRabbits({answers}) = " +
	   str(sol.numRabbits(answers)))