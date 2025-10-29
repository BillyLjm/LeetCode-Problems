"""
3370-Smallest_Number_With_All_Set_Bits.py
Billy.Ljm
29 October 2025

=======
Problem
=======
https://leetcode.com/problems/smallest-number-with-all-set-bits/

You are given a positive number n.

Return the smallest number x greater than or equal to n, such that the binary
representation of x contains only set bits.

===========
My Approach
===========
We use logarithms to determine the number of bits, then simply calculate the
value when all the bits are set.

This has a time complexity of O(1), and a space complexity of O(1).
"""

from math import log, ceil

class Solution(object):
    def smallestNumber(self, n):
        """
        :type n: int
        :rtype: int
        """
        if n == 0:
            return 0
        elif n == 1:
            return 1
        else:
            nint = ceil(log(n+1,2))
            return int(2**nint - 1)

"""
Test cases
"""
if __name__ == "__main__":
    sol = Solution()

    # test case 1
    n = 5
    print(f"smallestNumber({n}) = " +
       str(sol.smallestNumber(n)))

    # test case 2
    n = 10
    print(f"smallestNumber({n}) = " +
       str(sol.smallestNumber(n)))

    # test case 2
    n = 3
    print(f"smallestNumber({n}) = " +
       str(sol.smallestNumber(n)))