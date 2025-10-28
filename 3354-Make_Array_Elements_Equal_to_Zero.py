"""
3354-Make_Array_Elements_Equal_to_Zero.py
Billy.Ljm
28 October 2025

=======
Problem
=======
https://leetcode.com/problems/make-array-elements-equal-to-zero/

You are given an integer array nums.

Start by selecting a starting position curr such that nums[curr] == 0, and
choose a movement direction of either left or right.

After that, you repeat the following process:
- If curr is out of the range [0, n - 1], this process ends.
- If nums[curr] == 0, move in the current direction by incrementing curr if you
  are moving right, or decrementing curr if you are moving left.
- Else if nums[curr] > 0:
  - Decrement nums[curr] by 1.
  - Reverse your movement direction (left becomes right and vice versa).
        Take a step in your new direction.

A selection of the initial position curr and movement direction is considered
valid if every element in nums becomes 0 by the end of the process.

Return the number of possible valid selections.

===========
My Approach
===========
We will iterate through the array and simply compare the left and right sum.
The array will be zero if the left and right sum differ by -1, 0 or 1. This is
because the sums represent the number of times we can bounce off each side, and
all bounces will be consumed and elements made zero when the bounces on each
side differ by at most 1.

This has a time complexity of O(n), and a space complexity of O(n), where n is
the size of the array.
"""

class Solution(object):
    def countValidSelections(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        out = 0
        leftsum = 0
        rightsum = sum(nums)
        for i in range(len(nums)):
            if i-1 >= 0: leftsum += nums[i-1]
            rightsum -= nums[i]
            if nums[i] == 0:
                if leftsum - rightsum == 0: # both directions work
                    out += 2
                elif abs(leftsum - rightsum) == 1: # only 1 direction works
                    out += 1
        return out

"""
Test cases
"""
if __name__ == "__main__":
    sol = Solution()

    # test case 1
    nums = [1,0,2,0,3]
    print(f"countValidSelections({nums}) = " +
       str(sol.countValidSelections(nums)))

    # test case 2
    nums = [2,3,4,0,4,1,0]
    print(f"countValidSelections({nums}) = " +
       str(sol.countValidSelections(nums)))