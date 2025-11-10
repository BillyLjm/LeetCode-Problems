"""
3542-Minimum_Operations_to_Convert_All_Elements_to_Zero.py
Billy.Ljm
10 November 2025

=======
Problem
=======
https://leetcode.com/problems/minimum-operations-to-convert-all-elements-to-zero/

You are given an array nums of size n, consisting of non-negative integers. Your
task is to apply some (possibly zero) operations on the array so that all
elements become 0.

In one operation, you can select a subarray[i, j] (where 0 <= i <= j < n) and
set all occurrences of the minimum non-negative integer in that subarray to 0.

Return the minimum number of operations required to make all elements in the
array 0.

===========
My Approach
===========
The optimal solution would be to select the entire array, set the minimum to 0,
then repeat for every non-zero subarray. Thus, if adjacent values increase, it
would constitute any extra move to set the new value to zero. And if adjacent
values decreases, it would split the array into two subarrays up to the height
of the new value. And of course, if the values are the same then they can be
removed together. This can be tracked with a monotonic stack, where increases
are added to the stack, and decreases causes popping up to the new value.

This has a time complexity of O(n) and space complexity of O(n), where n is the
size of the array.
"""

from typing import List

class Solution:
    def minOperations(self, nums: List[int]) -> int:
        nmoves = 0
        stack = []
        for num in nums:
            # peak decreased, create new subarray up to height
            while len(stack) > 0 and num < stack[-1]:
                stack.pop()
            # peak increases, need extra move
            if (len(stack) == 0 or num > stack[-1]) and num != 0:
                stack.append(num)
                nmoves += 1
        return nmoves

"""
Test cases
"""
if __name__ == "__main__":
    sol = Solution()

    # test case 1
    nums = [0,2]
    print(f"minOperations({nums}) = " +
        str(sol.minOperations(nums)))

    # test case 2
    nums = [3,1,2,1]
    print(f"minOperations({nums}) = " +
        str(sol.minOperations(nums)))

     # test case 3
    nums = [1,2,1,2,1,2]
    print(f"minOperations({nums}) = " +
        str(sol.minOperations(nums)))

