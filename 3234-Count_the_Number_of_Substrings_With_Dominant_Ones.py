"""
3234-Count_the_Number_of_Substrings_With_Dominant_Ones.py
Billy.Ljm
16 November 2025

=======
Problem
=======
https://leetcode.com/problems/count-the-number-of-substrings-with-dominant-ones/

You are given a binary string s.

Return the number of substrings with dominant ones.

A string has dominant ones if the number of ones in the string is greater than
or equal to the square of the number of zeros in the string.

===========
My Approach
===========
We will iterate through each right border of the substring, and then use two
problem-specific shortcuts for iterating through the left border. The 1st is
that we can stop early if the 0's already exceeds the length of all possible
substrings, which is especially fast because the threshold grows as num0^2.
However, if there are no 0's then it would still iterate through every element.
Thus, we have the 2nd shortcut to only iterate through elements that are zero.
This means for each right border k, we will only iterate through sqrt(k) 0's.

This has a time complexity of O(n sqrt(n)) and space complexity of O(n), where n
is the length of the binary string
"""

class Solution:
    def numberOfSubstrings(self, s: str) -> int:
        # lookup table of previous 0's idx
        prev0 = [-1,]
        for i in range(1,len(s)):
            if s[i-1] == '0':
                prev0.append(i-1)
            else:
                prev0.append(prev0[-1])

        # main loop
        out = 0
        for r in range(len(s)):
            # init left = right boundary
            num0 = 0 if s[r] != '0' else 1 # number of 0's
            l = r
            while (num0**2 <= r) and (l >= 0):
                # move left boundary to just before next 0
                numadd = l - prev0[l] # number of bits added
                num1 = r - prev0[l] - num0 # number of 1's
                out += max(0, min(numadd, num1 - num0**2 + 1))
                # move left boundary to include next 0
                l = prev0[l]
                num0 += 1
        return out

"""
Test cases
"""
if __name__ == "__main__":
    sol = Solution()

    # test case 1
    s = "00011"
    print(f"numberOfSubstrings({s}) = " +
        str(sol.numberOfSubstrings(s)))

    # test case 2
    s = "101101"
    print(f"numberOfSubstrings({s}) = " +
        str(sol.numberOfSubstrings(s)))
