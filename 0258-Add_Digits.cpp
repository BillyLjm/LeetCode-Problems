/*******************************************************************************
 * 0258-Add_Digits.cpp
 * Billy.Ljm
 * 26 Apr 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/add-digits/
 * Given an integer num, repeatedly add all its digits until the result has only
 * one digit, and return it.
 *
 * ===========
 * My Approach
 * ===========
 * We can use clever math to solve this problem.
 * n = d_0 * 1 + d_1 + 10 + d_2 * 100 + d_3 1000 ...
 *   = d_0 * 1 + d_1 + (9+1) + d_2 * (9*11+1) + d_3 * (9*111+1) + ...
 * n mod 9 = d_0 + d_1 + d_2 + d_3 + ...
 *
 * This has a time complexity of O(1), and a space complexity of O(1).
 ******************************************************************************/

#include <iostream>

class Solution {
public:
	/**
	 * Finds the digital root of a number (i.e. summing each digit repeatedly
	 * until one digit is left)
	 *
	 * @param num The number to find the digital root of
	 *
	 * @return The digital root of the number
	 */
	int addDigits(int num) {
		if (num == 0) {
			return 0;
		}
		else {
			int out = num % 9;
			return out == 0 ? 9 : out;
		}
	}
};

/**
 * Test cases
 */
int main(void) {
	Solution sol;
	int num;

	// test case 1
	num = 38;
	std::cout << "addDigits(" << num << ") = " << sol.addDigits(num) << std::endl;

	// test case 2
	num = 0;
	std::cout << "addDigits(" << num << ") = " << sol.addDigits(num) << std::endl;

	return 0;
}