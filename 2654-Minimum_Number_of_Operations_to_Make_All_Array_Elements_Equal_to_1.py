"""
2654-Minimum_Number_of_Operations_to_Make_All_Array_Elements_Equal_to_1.py
Billy.Ljm
12 November 2025

=======
Problem
=======
https://leetcode.com/problems/minimum-number-of-operations-to-make-all-array-elements-equal-to-1/

You are given a 0-indexed array nums consisting of positive integers. You can
do the following operation on the array any number of times:

- Select an index i such that 0 <= i < n - 1 and replace either of nums[i] or
  nums[i+1] with their gcd value.

Return the minimum number of operations to make all elements of nums equal to 1.
If it is impossible, return -1.

The gcd of two integers is the greatest common divisor of the two integers.

===========
My Approach
===========
The solution is to find a subarray where the GCD of all elements in 1, then do
the operation of each pair within the subarray to create a 1 element, then
spread this 1 across the subarray by operating it with adjacent elements. If the
subarray is of length L, then the creation will take L-1 steps, and the spread
will take n-1 steps, yielding a total of L+n-2 steps.

To find the subarray, we creation we can find the gcd of the first pair, then
find the gcd of this gcd with the next element, yielding the gcd of the 3
elements. However, we will have to check every subarray to determine the shortest
subarray.

This has a time complexity of O(n^2 log(m)) and space complexity of O(1), where
n is the number of integers and m is the max integer.
"""

from typing import List
from collections import Counter
from math import gcd

class Solution:
    def minOperations(self, nums: List[int]) -> int:
        # trivial case
        cnt = Counter(nums)
        if 1 in cnt:
            return len(nums) - cnt[1]

        # find shortest subarray with gcd of 1
        minlenn = len(nums) + 1
        for i in range(len(nums) - 1):
            gcdd = nums[i]
            for j in range(i+1, len(nums)):
                gcdd = gcd(gcdd, nums[j])
                if gcdd == 1:
                    minlenn = min(minlenn, j-i+1)
                    break # other subarrays will be longer

        # calculate number of steps
        if minlenn <= len(nums):
            return len(nums) + minlenn - 2
        else:
            return -1

"""
Test cases
"""
if __name__ == "__main__":
    sol = Solution()

    # test case 1
    nums = [2,6,3,4]
    print(f"minOperations({nums}) = " +
        str(sol.minOperations(nums)))

    # test case 2
    nums = [2,10,6,14]
    print(f"minOperations({nums}) = " +
        str(sol.minOperations(nums)))
