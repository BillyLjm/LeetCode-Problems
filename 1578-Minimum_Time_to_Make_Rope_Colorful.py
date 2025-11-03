"""
1578-Minimum_Time_to_Make_Rope_Colorful.py
Billy.Ljm
03 November 2025

=======
Problem
=======
https://leetcode.com/problems/minimum-time-to-make-rope-colorful/

Alice has n balloons arranged on a rope. You are given a 0-indexed string colors
where colors[i] is the color of the ith balloon.

Alice wants the rope to be colorful. She does not want two consecutive balloons
to be of the same color, so she asks Bob for help. Bob can remove some balloons
from the rope to make it colorful. You are given a 0-indexed integer array
neededTime where neededTime[i] is the time (in seconds) that Bob needs to remove
the ith balloon from the rope.

Return the minimum time Bob needs to make the rope colorful.

===========
My Approach
===========
We have to identify consecutive clusters of similar colours, then remove all
but the highest neededTime element.

This has a time complexity of O(n), and a space complexity of O(1), where n is
the number of balloons.
"""

from typing import List
import numpy as np

class Solution:
    def minCost(self, colors: str, neededTime: List[int]) -> int:
        cost = 0
        idx = 0 # index of start of cluster
        # iterate through balloons
        for i in range(1, len(colors)):
            if colors[i] != colors[i-1]:
                cost += sum(neededTime[idx:i]) - max(neededTime[idx:i])
                idx = i
        # check last element
        if len(colors) > 1 and colors[-1] == colors[-2]:
            cost += sum(neededTime[idx:]) - max(neededTime[idx:])
        return cost

"""
Test cases
"""
if __name__ == "__main__":
    sol = Solution()

    # test case 1
    colors = "abaac"
    neededTime = [1,2,3,4,5]
    print(f"minCost({colors}, {neededTime}) = " +
        str(sol.minCost(colors, neededTime)))

    # test case 2
    colors = "abc"
    neededTime = [1,2,3]
    print(f"minCost({colors}, {neededTime}) = " +
        str(sol.minCost(colors, neededTime)))

    # test case 3
    colors = "aabaa"
    neededTime = [1,2,3,4,1]
    print(f"minCost({colors}, {neededTime}) = " +
        str(sol.minCost(colors, neededTime)))