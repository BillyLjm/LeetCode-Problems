"""
1513_Number_of_Substrings_With_Only_1s.py
Billy.Ljm
16 November 2025

=======
Problem
=======
https://leetcode.com/problems/number-of-substrings-with-only-1s/

Given a binary string s, return the number of substrings with all characters 1's.
Since the answer may be too large, return it modulo 10^9 + 7.

===========
My Approach
===========
If there are k consecutive 1's, then there are k(k+1)/2 = k + (k-1) + ... + 1
substrings of 1's. Thus, we just have to iterate and count consecutive 1's.

This has a time complexity of O(n) and space complexity of O(1), where n is the
length of the binary string
"""

class Solution:
    def __init__(self):
        self.modd = 1E9 + 7 # value to modulo over

    def numSub(self, s: str) -> int:
        out = 0
        num1 = 0
        for char in s:
            if char == '1':
                num1 += 1
            else:
                out += (num1 * (num1 + 1) / 2) % self.modd
                out %= self.modd
                num1 = 0
        # last set of 1's
        out += (num1 * (num1 + 1) / 2) % self.modd
        out %= self.modd
        return int(out)

"""
Test cases
"""
if __name__ == "__main__":
    sol = Solution()

    # test case 1
    s = "0110111"
    print(f"numSub({s}) = " +
        str(sol.numSub(s)))

    # test case 2
    s = "101"
    print(f"numSub({s}) = " +
        str(sol.numSub(s)))

    # test case 3
    s = "111111"
    print(f"numSub({s}) = " +
        str(sol.numSub(s)))
