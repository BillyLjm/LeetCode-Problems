"""
3318-Find_X-Sum_of_All_K-Long_Subarrays_I.py
Billy.Ljm
04 November 2025

=======
Problem
=======
https://leetcode.com/problems/find-x-sum-of-all-k-long-subarrays-i/

You are given an array nums of n integers and two integers k and x.

The x-sum of an array is calculated by the following procedure:

- Count the occurrences of all elements in the array.
- Keep only the occurrences of the top x most frequent elements. If two elements
  have the same number of occurrences, the element with the bigger value is
  considered more frequent.
- Calculate the sum of the resulting array.

Note that if an array has less than x distinct elements, its x-sum is the sum of
the array.

Return an integer array answer of length n - k + 1 where answer[i] is the x-sum
of the nums[i..i + k - 1].

===========
My Approach
===========
We used a rolling window to keep track of the number occurrences of each element
within each subarray. Then the x-sum is calculated as specified.

This has a time complexity of O(n*k), and a space complexity of O(k), where n is
the number of integers and  k the length of the subarray.
"""

from typing import List
from collections import Counter

class Solution:
    def findXSum(self, nums: List[int], k: int, x: int) -> List[int]:
        out = []
        ctr = Counter(nums[:k])
        for i in range(len(nums) - k + 1):
            # update rolling window
            if i != 0:
                ctr.update([nums[i+k-1]])
                ctr.subtract([nums[i-1]])
            # calculate x-sum
            out.append(0)
            cnts = sorted(ctr.items(), key=lambda x: (x[1], x[0]), reverse=True)
            for ele, cnt in cnts[:x]:
                out[-1] += ele * cnt
        return out

"""
Test cases
"""
if __name__ == "__main__":
    sol = Solution()

    # test case 1
    nums = [1,1,2,2,3,4,2,3]
    k = 6
    x = 2
    print(f"findXSum({nums}, {k}, {x}) = " +
        str(sol.findXSum(nums, k, x)))

    # test case 2
    nums = [3,8,7,8,7,5]
    k = 2
    x = 2
    print(f"findXSum({nums}, {k}, {x}) = " +
        str(sol.findXSum(nums, k, x)))
