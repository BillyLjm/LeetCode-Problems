"""
1611-Minimum_One_Bit_Operations_to_Make_Integers_Zero.py
Billy.Ljm
08 November 2025

=======
Problem
=======
https://leetcode.com/problems/minimum-one-bit-operations-to-make-integers-zero/

Given an integer n, you must transform it into 0 using the following operations
any number of times:

- Change the rightmost (0th) bit in the binary representation of n.
- Change the ith bit in the binary representation of n if the (i-1)th bit is set
  to 1 and the (i-2)th through 0th bits are set to 0.

Return the minimum number of operations to transform n into 0.

===========
My Approach
===========
Let's analyse the process to transform 0 into n instead, because the starting
point is fixed. Explicitly tracing the process for a small number of bits gives:

0000 >
0001 >
0011 > 0010 >
0110 > 0111 > 0101 > 0100
1100 > 1101 > 1111 > 1110 > 1010 > 1011 > 1001 > 1000

Evidently, it takes sum_{k=0}^{i} 2^k steps create a 1000... i-bit string. And
for bitstrings with multiple 1's, it appears before the 1000... is created,
specifically by the same number of steps required to create the remaining ones.

For a concrete example, it takes 15 steps to create 1000 and 3 steps to create
0010. Therefore, to create 1010, we take 15 steps to 1000, then take 3 steps
back to insert 0010.

Thus, we just have to calculate this. And we can do it with a rolling sum, and
in the opposite direction of least to most significant bit for better runtime

This has a time complexity of O(log n), and a space complexity of O(1), where n
is the number given.
"""

from typing import List

class Solution:
    def minimumOneBitOperations(self, n: int) -> int:
        bitstr = bin(n)[2:]
        rollsum = 0
        out = 0
        for i in range(len(bitstr)):
            rollsum += 2**i
            if bitstr[-1-i] == '1':
                out = rollsum - out
        return out

"""
Test cases
"""
if __name__ == "__main__":
    sol = Solution()

    # test case 1
    n = 3
    print(f"minimumOneBitOperations({n}) = " +
        str(sol.minimumOneBitOperations(n)))

    # test case 2
    n = 6
    print(f"minimumOneBitOperations({n}) = " +
        str(sol.minimumOneBitOperations(n)))
