"""
3272-Find_the_Count_of_Good_Integers.py
Billy.Ljm
12 April 2025

=======
Problem
=======
https://leetcode.com/problems/find-the-count-of-good-integers/

You are given two positive integers n and k.

An integer x is called k-palindromic if:
- x is a palindrome
- x is divisible by k.

An integer is called good if its digits can be rearranged to form a
k-palindromic integer. For example, for k = 2, 2020 can be rearranged to form
the k-palindromic integer 2002, whereas 1010 cannot be rearranged to form a
k-palindromic integer.

Return the count of good integers containing n digits.

Note that any integer must not have leading zeros, neither before nor after
rearrangement. For example, 1010 cannot be rearranged to form 101.

===========
My Approach
===========
We can iterate through each number, make them palindromic by mirroring while
padding with zeros in the middle until it is of the required lengths. Then we
just have to check if it is still divisible by k to ensure its k-palindromic.
If it is, then any permutation of these numbers will be good integers and we
count the permutations.

This has a time complexity of O(10**(math.ceil(n/2)), and a space complexity of
O(n), where n is the length of the integers.
"""

import math

class Solution:
	def countGoodIntegers(self, n: int, k: int) -> int:
		# find all k-palindromes
		sett = set()
		for i in range(10**(math.ceil(n/2))):
			num = str(i).rjust(math.ceil(n/2), '0') # pad zeros
			if n % 2 == 0: # make palindrome
				num = num[::-1] + num
			else:
				num = num[:0:-1] + num
			if (num[0] != '0') & (int(num) % k == 0): # k-palindrome
				# count number of each digit
				cnt = [0] * 10
				for i in num: cnt[int(i)] += 1
				sett.add(tuple(cnt))

		# count permutations of palindromes
		out = 0
		for cnt in sett:
			out += (n - cnt[0]) * math.factorial(n-1) / \
				   math.prod([math.factorial(i) for i in cnt])
		return int(out)

"""
Test cases
"""
if __name__ == "__main__":
	sol = Solution()

	# test case 1
	n = 3
	k = 5
	print(f"countGoodIntegers({n}, {k}) = " +
	   str(sol.countGoodIntegers(n, k)))

	# test case 2
	n = 1
	k = 4
	print(f"countGoodIntegers({n}, {k}) = " +
	   str(sol.countGoodIntegers(n, k)))


	# test case 3
	n = 5
	k = 6
	print(f"countGoodIntegers({n}, {k}) = " +
	   str(sol.countGoodIntegers(n, k)))
