"""
2563-Count_the_Number_of_Fair_Pairs.py
Billy.Ljm
19 April 2025

=======
Problem
=======
https://leetcode.com/problems/count-the-number-of-fair-pairs/

Given a 0-indexed integer array nums of size n and two integers lower and upper,
return the number of fair pairs.

A pair (i, j) is fair if:
- 0 <= i < j < n, and
- lower <= nums[i] + nums[j] <= upper

===========
My Approach
===========
We can iterate through i and sort the values to the right of i, or more
efficiently we can sort the array and remove the i-th element form the sorted
array as we iterate through i. Then, we can use binary search to count the
number of elements which are within the bounds.

This has a time complexity of O(n log n), and a space complexity of O(n), where
n is the size of the array
"""

from collections import Counter

class Solution:
	def binaryLowBound(self, lst: list[int], val: int) -> int:
		''' finds index of the largest element that is smaller than val '''
		# binary bisection
		minn = 0
		maxx = len(lst) - 1
		while maxx - minn > 1:
			midd = (minn + maxx) // 2
			if lst[midd] >= val:
				maxx = midd
			else:
				minn = midd
		# check last values
		if lst[maxx] < val:
			return maxx
		elif lst[minn] < val:
			return minn
		else:
			return -1

	def countFairPairs(self, nums: list[int], lower: int, upper: int) -> int:
		cnt = 0
		# sort array
		sortt = nums.copy()
		sortt.sort()
		# iterate through i
		for i in nums[:-1]:
			sortt.pop(self.binaryLowBound(sortt, i) + 1)
			cnt += self.binaryLowBound(sortt, upper - i + 1)
			cnt -= self.binaryLowBound(sortt, lower - i)
		return cnt

"""
Test cases
"""
if __name__ == "__main__":
	sol = Solution()

	# test case 1
	nums = [0,1,7,4,4,5]
	lower = 3
	upper = 6
	print(f"countFairPairs({nums}, {lower}, {upper}) = " +
	   str(sol.countFairPairs(nums, lower, upper)))

	# test case 2
	nums = [1,7,9,2,5]
	lower = 11
	upper = 11
	print(f"countFairPairs({nums}, {lower}, {upper}) = " +
	   str(sol.countFairPairs(nums, lower, upper)))