"""
1526-Minimum_Number_of_Increments_on_Subarrays_to_Form_a_Target_Array.py
Billy.Ljm
01 November 2025

=======
Problem
=======
https://leetcode.com/problems/minimum-number-of-increments-on-subarrays-to-form-a-target-array/

You are given an integer array target. You have an integer array initial of the
same size as target with all elements initially zeros.

In one operation you can choose any subarray from initial and increment each
value by one.

Return the minimum number of operations to form a target array from initial.

The test cases are generated so that the answer fits in a 32-bit integer.

===========
My Approach
===========
For a peaked subarray where the integers only increase and decrease, we need a
number of operations identical to the largest integer in the subarray. If there
is another subsequent peak array, we then need the number of operations equal to
the difference in the two peaks. This is equivalent to counting when adjacent
integers increase, and we can use numpy to calculate this quickly with vectors.

This has a time complexity of O(n), and a space complexity of O(1), where n is
the size of the target list.
"""

from typing import List
import numpy as np

class Solution:
    def minNumberOperations(self, target: List[int]) -> int:
        numops = target[0]
        diff = np.diff(target)
        numops += np.sum(diff[diff > 0])
        return int(numops)

"""
Test cases
"""
if __name__ == "__main__":
    sol = Solution()

    # test case 1
    target = [1,2,3,2,1]
    print(f"minNumberOperations({target}) = " +
       str(sol.minNumberOperations(target)))

    # test case 2
    target = [3,1,1,2]
    print(f"minNumberOperations({target}) = " +
       str(sol.minNumberOperations(target)))

    # test case 3
    target = [3,1,5,4,2]
    print(f"minNumberOperations({target}) = " +
       str(sol.minNumberOperations(target)))
