"""
1922-Count_Good_Numbers.py
Billy.Ljm
13 April 2025

=======
Problem
=======
https://leetcode.com/problems/count-good-numbers/

A digit string is good if the digits (0-indexed) at even indices are even and 
the digits at odd indices are prime (2, 3, 5, or 7).

- For example, "2582" is good because the digits (2 and 8) at even positions are 
  even and the digits (5 and 2) at odd positions are prime. However, "3245" is 
  not good because 3 is at an even index but is not even.

Given an integer n, return the total number of good digit strings of length n. 
Since the answer may be large, return it modulo 10^9 + 7.

A digit string is a string consisting of digits 0 through 9 that may contain 
leading zeros.

===========
My Approach
===========
We'll just count the number of permutations. At each even index, we can choose
from 0,2,4,6,8; and at each odd index we can choose from 2,3,5,7. Thus, we just
multiply the choices to get the number of permutations, with modulo exponents.

This has a time complexity of O(1), and a space complexity of O(1).
"""

import math

class Solution:
	def countGoodNumbers(self, n: int) -> int:
		modd = int(1E9 + 7)
		neven = math.ceil(n/2)
		nodd = math.floor(n/2)
		cnt = pow(5, neven, modd)
		cnt = (cnt * pow(4, nodd, modd)) % modd
		return int(cnt)

"""
Test cases
"""
if __name__ == "__main__":
	sol = Solution()

	# test case 1
	n = 1
	print(f"countGoodNumbers({n}) = " +
	   str(sol.countGoodNumbers(n)))

	# test case 2
	n = 4
	print(f"countGoodNumbers({n}) = " +
	   str(sol.countGoodNumbers(n)))


	# test case 3
	n = 50
	print(f"countGoodNumbers({n}) = " +
	   str(sol.countGoodNumbers(n)))