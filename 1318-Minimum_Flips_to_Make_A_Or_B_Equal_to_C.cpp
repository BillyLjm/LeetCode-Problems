/*******************************************************************************
 * 1318-Minimum_Flips_to_Make_A_Or_B_Equal_to_C.cpp
 * Billy.Ljm
 * 07 June 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/minimum-flips-to-make-a-or-b-equal-to-c/
 *
 * Given 3 positives numbers a, b and c. Return the minimum flips required in
 * some bits of a and b to make ( a OR b == c ). (bitwise OR operation).
 *
 * Flip operation consists of change any single bit 1 to 0 or change the bit 0
 * to 1 in their binary representation.
 *
 * ===========
 * My Approach
 * ===========
 * We'll use bitwise operations to do this efficiently. We'll calculate (a|b)^c
 * to find the bit indices that are different and have to be flipped. Then we
 * iterate through each index and count how many bits have to be flipped. If
 * bot a and b are 1's then flip twice, otherwise flip once.
 *
 * This has a time complexity of O(1) and space complexity of O(1).
 ******************************************************************************/

#include <iostream>
#include <vector>

/**
 * Solution
 */
class Solution {
public:
	/**
	 * Finds the minimum number of bit flips (in a and b) to make a|b = c.
	 *
	 * @param a to make a|b = c
	 * @param b to make a|b = c
	 * @param c to make a|b = c
	 *
	 * @return minimum number of flips to make a|b = c
	 */
	int minFlips(int a, int b, int c) {
		int count = 0;
		int num = (a | b) ^ c;
		while (num > 0) {
			if (num % 2 == 1) {
				count++;
				if (a % 2 == 1 && b % 2 == 1) count++;
			}
			num /= 2;
			a /= 2;
			b /= 2;
		}
		return count;
	}
};

/**
 * Test cases
 */
int main(void) {
	Solution sol;
	int a, b, c;

	// test case 1
	a = 2;
	b = 6;
	c = 5;
	std::cout << "minFlips(" << a << "," << b << "," << c << ") = "
		<< sol.minFlips(a, b, c) << std::endl;

	// test case 2
	a = 4;
	b = 2;
	c = 7;
	std::cout << "minFlips(" << a << "," << b << "," << c << ") = "
		<< sol.minFlips(a, b, c) << std::endl;

	// test case 2
	a = 1;
	b = 2;
	c = 3;
	std::cout << "minFlips(" << a << "," << b << "," << c << ") = "
		<< sol.minFlips(a, b, c) << std::endl;

	return 0;
}