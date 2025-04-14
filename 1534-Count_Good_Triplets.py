"""
1534-Count_Good_Triplets.py
Billy.Ljm
14 April 2025

=======
Problem
=======
https://leetcode.com/problems/count-good-triplets/

Given an array of integers arr, and three integers a, b and c. You need to find
the number of good triplets.

A triplet (arr[i], arr[j], arr[k]) is good if the following conditions are true:

- 0 <= i < j < k < arr.length
- |arr[i] - arr[j]| <= a
- |arr[j] - arr[k]| <= b
- |arr[i] - arr[k]| <= c

Where |x| denotes the absolute value of x.

Return the number of good triplets.

===========
My Approach
===========
We can iterate for increasing values of j gradually counting and updating the
frequency of each number in the indices lower than j. Then, we will immediately
know how many (1) |arr[i] - arr[j]| <= a since we already have the counts. All
that is left is to iterate through values of k, similarly calculate the number
of (3) |arr[i] - arr[k]| <= c, and check (2) |arr[j] - arr[k]| <= b

This has a time complexity of O(n^2), and a space complexity of O(m), where n
is the size and m is the maximum element of the array.
"""

import numpy as np

class Solution:
	def countGoodTriplets(self, arr: list[int], a: int, b: int, c: int) -> int:
		cnt = 0 # count of good triplets
		freq = [0] * (max(arr) + 1) # frequency of each number

		for j in range(1,len(arr)):
			# update frequency
			freq[arr[j-1]] += 1
			csum = np.cumsum(freq)
			# choose k
			for k in range(j + 1, len(arr)):
				if np.abs(arr[j] - arr[k]) <= b:
					# arr[i] <= arr[j] + a, arr[k] + c
					maxx = np.min([len(csum)-1, arr[j] + a, arr[k] + c])
					# arr[i] >= arr[j] - a, arr[k] - c
					minn = np.max([0, arr[j] - a, arr[k] - c])
					# immediately count the number of possible i
					if (minn > maxx):
						continue
					elif (minn != 0):
						cnt += csum[maxx] - csum[minn - 1]
					else:
						cnt += csum[maxx]
		return cnt

"""
Test cases
"""
if __name__ == "__main__":
	sol = Solution()

	# test case 1
	arr = [3,0,1,1,9,7]
	a = 7
	b = 2
	c = 3
	print(f"countGoodTriplets({arr}, {a}, {b}, {c}) = " +
	   str(sol.countGoodTriplets(arr, a, b, c)))

	# test case 2
	arr = [1,1,2,2,3]
	a = 0
	b = 0
	c = 1
	print(f"countGoodTriplets({arr}, {a}, {b}, {c}) = " +
	   str(sol.countGoodTriplets(arr, a, b, c)))