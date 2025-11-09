"""
2528-Maximize_the_Minimum_Powered_City.py
Billy.Ljm
09 November 2025

=======
Problem
=======
https://leetcode.com/problems/maximize-the-minimum-powered-city/

You are given a 0-indexed integer array stations of length n, where stations[i]
represents the number of power stations in the ith city.

Each power station can provide power to every city in a fixed range. In other
words, if the range is denoted by r, then a power station at city i can provide
power to all cities j such that |i - j| <= r and 0 <= i, j <= n - 1.

The power of a city is the total number of power stations it is being provided
power from.

The government has sanctioned building k more power stations, each of which can
be built in any city, and have the same range as the pre-existing ones.

Given the two integers r and k, return the maximum possible minimum power of a
city, if the additional power stations are built optimally.

Note that you can build the k power stations in multiple cities.

===========
My Approach
===========
We can use binary search to essentially guess and check the answer. We guess
the maxpower, iterate through the list maintaining a rolling sum of the power
available via all the power stations within range, and answer if each city has
sufficient power. If a city doesn't have enough, we can greedily construct power
stations at the furthest city in range since it covers more cities.

This has a time complexity of O(n log d) and space complexity of O(n), where n
is the number of cities, and d is the total number of power stations including k.
"""

from typing import List

class Solution:
    def isPossible(self, stations: List[int], r: int, k: int, maxPower: int) -> bool:
        """ checks if a specific maxPower is possible """
        addstations = [0] * len(stations) # num stations added at each city
        rollsum = sum(stations[:r])
        for i in range(len(stations)):
            # update rolling sum
            if (i + r) < len(stations):
                rollsum += stations[i + r]
                rollsum += addstations[i + r]
            if (i - r - 1) >= 0:
                rollsum -= stations[i - r - 1]
                rollsum -= addstations[i - r - 1]
            # check if possible
            if rollsum < maxPower:
                tmp = maxPower - rollsum
                addstations[min(i+r, len(stations)-1)] += tmp
                rollsum += tmp
                k -= tmp
                if k < 0:
                    return False
        return True

    def maxPower(self, stations: List[int], r: int, k: int) -> int:
        minn = min(stations)
        maxx = sum(stations) + k
        # binary search
        while maxx > minn + 1:
            midd = (minn + maxx) // 2
            if self.isPossible(stations, r, k, midd):
                minn = midd
            else:
                maxx = midd - 1
        # last comparison
        if self.isPossible(stations, r, k, maxx):
            return maxx
        else:
            return minn

"""
Test cases
"""
if __name__ == "__main__":
    sol = Solution()

    # test case 1
    stations = [1,2,4,5,0]
    r = 1
    k = 2
    print(f"maxPower({stations}, {r}, {k}) = " +
        str(sol.maxPower(stations, r, k)))

    # test case 2
    stations = [4,4,4,4]
    r = 0
    k = 3
    print(f"maxPower({stations}, {r}, {k}) = " +
        str(sol.maxPower(stations, r, k)))
