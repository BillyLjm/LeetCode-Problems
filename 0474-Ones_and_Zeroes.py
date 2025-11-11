"""
0474-Ones_and_Zeroes.py
Billy.Ljm
11 November 2025

=======
Problem
=======
https://leetcode.com/problems/ones-and-zeroes/

You are given an array of binary strings strs and two integers m and n.

Return the size of the largest subset of strs such that there are at most m 0's
and n 1's in the subset.

A set x is a subset of a set y if all elements of x are also elements of y.

===========
My Approach
===========
This is a knapsack problem of getting the most elements while keeping the
number of 0's and 1's under the threshold. Thus, we will use dynamic programming
where dp[i][j][k] is the most character when considering items up to i, with j
0's and k 1's.

This has a time complexity of O(lmn) and space complexity of O(mn), where l is
the number of integers, and m and n is the maximum number of 0's and 1's.
"""

from typing import List

class Solution:
    def findMaxForm(self, strs: List[str], m: int, n: int) -> int:
        out = 0
        dp = {(0,0): 0} # dp[(num0's, num1's)]
        for i in range(len(strs)):
            curr = (strs[i].count('0'), strs[i].count('1'))
            newdp = dp.copy()
            for prev in dp.keys():
                nextt = (curr[0] + prev[0], curr[1] + prev[1])
                if nextt[0] > m or nextt[1] > n:
                    continue
                elif nextt in dp:
                    newdp[nextt] = max(dp[nextt], dp[prev] + 1)
                else:
                    newdp[nextt] = dp[prev] + 1
                out = max(out, newdp[nextt])
            dp = newdp
        return out

"""
Test cases
"""
if __name__ == "__main__":
    sol = Solution()

    # test case 1
    strs = ["10","0001","111001","1","0"]
    m = 5
    n = 3
    print(f"findMaxForm({strs}, {m}, {n}) = " +
        str(sol.findMaxForm(strs, m, n)))

    # test case 2
    strs = ["10","0","1"]
    m = 1
    n = 1
    print(f"findMaxForm({strs}, {m}, {n}) = " +
        str(sol.findMaxForm(strs, m, n)))
