"""
2145-Count_the_Hidden_Sequences.py
Billy.Ljm
21 April 2025

=======
Problem
=======
https://leetcode.com/problems/count-the-hidden-sequences/

You are given a 0-indexed array of n integers differences, which describes the 
differences between each pair of consecutive integers of a hidden sequence of 
length (n + 1). More formally, call the hidden sequence hidden, then we have 
that differences[i] = hidden[i + 1] - hidden[i].

You are further given two integers lower and upper that describe the inclusive 
range of values [lower, upper] that the hidden sequence can contain.

For example, given differences = [1, -3, 4], lower = 1, upper = 6, the hidden 
sequence is a sequence of length 4 whose elements are in between 1 and 6 (inclusive).
- [3, 4, 1, 5] and [4, 5, 2, 6] are possible hidden sequences.
- [5, 6, 3, 7] is not possible since it contains an element greater than 6.
- [1, 2, 3, 4] is not possible since the differences are not correct.

Return the number of possible hidden sequences there are. If there are no 
possible sequences, return 0.

===========
My Approach
===========
We can iterate through the difference and count the maximum and minimum 
difference wrt the first element. Then hidden[0] /in [lower - min, upper - max]
and we can count the number of possible integers for hidden[0]

This has a time complexity of O(n), and a space complexity of O(1), where n
is the length of the array.
"""

from collections import defaultdict

class Solution:
	def numberOfArrays(self, differences: list[int], lower: int, upper: int) -> int:
		# find minimum & maximum differences
		maxdiff = 0
		mindiff = 0
		diff = 0
		for i in differences:
			diff += i
			maxdiff = max(diff, maxdiff)
			mindiff = min(diff, mindiff)
		# return count of possibilities
		return max(0, (upper - maxdiff) - (lower - mindiff) + 1)

"""
Test cases
"""
if __name__ == "__main__":
	sol = Solution()

	# test case 1
	differences = [1,-3,4]
	lower = 1
	upper = 6
	print(f"numberOfArrays({differences}, {lower}, {upper}) = " +
	   str(sol.numberOfArrays(differences, lower, upper)))

	# test case 2
	differences = [3,-4,5,1,-2]
	lower = -4
	upper = 5
	print(f"numberOfArrays({differences}, {lower}, {upper}) = " +
	   str(sol.numberOfArrays(differences, lower, upper)))

	# test case 3
	differences = [4,-7,2]
	lower = 3
	upper = 6
	print(f"numberOfArrays({differences}, {lower}, {upper}) = " +
	   str(sol.numberOfArrays(differences, lower, upper)))

