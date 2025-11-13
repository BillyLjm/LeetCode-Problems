"""
3228-Maximum_Number_of_Operations_to_Move_Ones_to_the_End.py
Billy.Ljm
13 November 2025

=======
Problem
=======
https://leetcode.com/problems/maximum-number-of-operations-to-move-ones-to-the-end/

You are given a binary string s.

You can perform the following operation on the string any number of times:
- Choose any index i from the string where i + 1 < s.length such that
  s[i] == '1' and s[i + 1] == '0'.
- Move the character s[i] to the right until it reaches the end of the string or
  another '1'. For example, for s = "010010", if we choose i = 1, the resulting
  string will be s = "000110".

Return the maximum number of operations that you can perform.

===========
My Approach
===========
The solution is to iterate from left to right an apply the operation on every
"10". Additionally it accumulates since applying it on "110" will create "100"
which can then be operated on again. So we just iterate from left to right,
counting the number of 1's and adding that number to the operations every time
we encounter a "10".

This has a time complexity of O(n) and space complexity of O(1), where n is the
length of the binary string
"""

class Solution:
    def maxOperations(self, s: str) -> int:
        numops = 0
        num1 = 0
        for i in range(len(s) - 1):
            if s[i] == '1':
                num1 += 1
                if s[i:i+1] == '0':
                    numops += num1
        return numops

"""
Test cases
"""
if __name__ == "__main__":
    sol = Solution()

    # test case 1
    s = "1001101"
    print(f"maxOperations({s}) = " +
        str(sol.maxOperations(s)))

    # test case 2
    s = "00111"
    print(f"maxOperations({s}) = " +
        str(sol.maxOperations(s)))
