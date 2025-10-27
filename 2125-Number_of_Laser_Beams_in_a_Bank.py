"""
2125-Number_of_Laser_Beams_in_a_Bank.py
Billy.Ljm
27 October 2025

=======
Problem
=======
https://leetcode.com/problems/number-of-laser-beams-in-a-bank/

Anti-theft security devices are activated inside a bank. You are given a 0-indexed
binary string array bank representing the floor plan of the bank, which is an
m x n 2D matrix. bank[i] represents the ith row, consisting of '0's and '1's.
'0' means the cell is empty, while'1' means the cell has a security device.

There is one laser beam between any two security devices if both conditions are met:
- The two devices are located on two different rows: r1 and r2, where r1 < r2.
- For each row i where r1 < i < r2, there are no security devices in the ith row.

Laser beams are independent, i.e., one beam does not interfere nor join with another.

Return the total number of laser beams in the bank.

===========
My Approach
===========
We can simply iterate through each row and count the number of laser beams
between them. If there are no security devices in that row, then we just ignore
it and move onto the next one.

This has a time complexity of O(mn), and a space complexity of O(mn), where m
and n are the number of rows and columns respectively.
"""

class Solution(object):
    def numberOfBeams(self, bank):
        """
        :type bank: List[str]
        :rtype: int
        """
        tot = 0
        prev = 0
        for row in bank:
            curr = row.count('1')
            if curr != 0:
                tot += prev * curr
                prev = curr
        return tot

"""
Test cases
"""
if __name__ == "__main__":
	sol = Solution()

	# test case 1
	bank = ["011001","000000","010100","001000"]
	print(f"numberOfBeams({bank}) = " +
	   str(sol.numberOfBeams(bank)))

	# test case 2
	bank = ["000","111","000"]
	print(f"numberOfBeams({bank}) = " +
	   str(sol.numberOfBeams(bank)))
