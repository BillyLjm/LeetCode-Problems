"""
2176-Count_Equal_and_Divisible_Pairs_in_an_Array.py
Billy.Ljm
17 April 2025

=======
Problem
=======
https://leetcode.com/problems/count-equal-and-divisible-pairs-in-an-array/

Given a 0-indexed integer array nums of length n and an integer k, return the 
number of pairs (i, j) where 0 <= i < j < n, such that nums[i] == nums[j] and 
(i * j) is divisible by k. 

===========
My Approach
===========
We just have to iterate through every pair of i and j, and check if the
conditions are fulfilled. We can speed this up slightly by using a dict to save 
the indices of similar elements as we crawl through the list

This has a time complexity of O(n^2), and a space complexity of O(n^2), where n
is the length of the array.
"""

from collections import defaultdict

class Solution:
	def countPairs(self, nums: list[int], k: int) -> int:
		cnt = 0 # count of pairs
		idx = defaultdict(list) # index of previous elements
		for i in range(len(nums)):
			for j in idx[nums[i]]:
				cnt += ((i * j) % k == 0)
			idx[nums[i]].append(i)
		return cnt

"""
Test cases
"""
if __name__ == "__main__":
	sol = Solution()

	# test case 1
	nums = [3,1,2,2,2,1,3]
	k = 2
	print(f"countPairs({nums}, {k}) = " +
	   str(sol.countPairs(nums, k)))

	# test case 2
	nums = [1,2,3,4]
	k = 1
	print(f"countPairs({nums}, {k}) = " +
	   str(sol.countPairs(nums, k)))