"""
2537-Count_the_Number_of_Good_Subarrays.py
Billy.Ljm
16 April 2025

=======
Problem
=======
https://leetcode.com/problems/count-the-number-of-good-subarrays/

Given an integer array nums and an integer k, return the number of good 
subarrays of nums.

A subarray arr is good if there are at least k pairs of indices (i, j) such that 
i < j and arr[i] == arr[j].

A subarray is a contiguous non-empty sequence of elements within an array.

===========
My Approach
===========
We will use a sliding window to define the subarray and gradually crawl through 
the full array while ensuring the windowed subarray is good. Starting with the 
left boundary at zero, we move the right boundary until the subarray is good. 
We can then count the number of remaining elements beyond the right, since 
adding them would still yield good subarrays. Having counted these subarrays, 
we can then move our left boundary one step down, and repeat the process.


This has a time complexity of O(n), and a space complexity of O(n), where n is 
the size of the array
"""

from collections import Counter

class Solution:
	def countGood(self, nums: list[int], k: int) -> int:
		cnt = 0 # number of good subarrays
		freq = Counter() # count of numbers in subarray
		nidn = 0 # number of identical elements
		right = -1 # right boundary
		for left in range(len(nums)): # left boundary
			# extend right boundary until good subarray
			while (nidn < k):
				right += 1
				if right >= len(nums): return cnt # return if end reached
				nidn += freq[nums[right]]
				freq[nums[right]] += 1
			# count number of good subarrays
			if (nidn >= k):
				cnt += len(nums) - right
			# walk left
			freq[nums[left]] -= 1
			nidn -= freq[nums[left]]
			left += 1
		return cnt


"""
Test cases
"""
if __name__ == "__main__":
	sol = Solution()

	# test case 1
	nums = [1,1,1,1,1]
	k = 10
	print(f"countGood({nums}, {k}) = " +
	   str(sol.countGood(nums, k)))

	# test case 2
	nums = [3,1,4,3,2,2,4]
	k = 2
	print(f"countGood({nums}, {k}) = " +
	   str(sol.countGood(nums, k)))
