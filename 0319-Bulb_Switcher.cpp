/*******************************************************************************
 * 0319-Bulb_Switcher.cpp
 * Billy.Ljm
 * 27 Apr 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/bulb-switcher/
 * There are n bulbs that are initially off. You first turn on all the bulbs,
 * then you turn off every second bulb.
 *
 * On the third round, you toggle every third bulb (turning on if it's off or
 * turning off if it's on). For the ith round, you toggle every i bulb. For the
 * nth round, you only toggle the last bulb.
 *
 * Return the number of bulbs that are on after n rounds.
 *
 * ===========
 * My Approach
 * ===========
 * For bulb i, we iterate j=[1,i] and check if j is a factor of i. If it is, we
 * toggle the blub, and at the end we see if the bulb is on or off.
 *
 * We can simplify with maths, by noting that most numbers are factorised into
 * two distinct numbers. For example, 6 = 1x6 = 2x3. This means that they have
 * an even number of factors, will be toggled an even number of times, and end
 * up turned off. The only exception are perfect squares like 4 = 2x2, which
 * have and odd number of factors, will be toggled an odd number of times and
 * end up turned on.
 *
 * Thus, we just have to count the number of perfect squares less than n. These
 * perfect squares are 1x1, 2x2, 3x3, ..., < sqrt(n)xsqrt(n) = n. Thus, it will
 * just be the answer will just be floor(sqrt(n)).
 *
 * This has a time complexity of O(1) and space complexity of (1).
 ******************************************************************************/

#include <iostream>

class Solution {
public:
	/**
	 * Given n bulbs, we iterate i = [1,n] and toggle on/off every i-th bulb.
	 * This finds the number of bulbs that remain on after n rounds.
	 *
	 * @param n number of bulbs
	 *
	 * @return number of bulbs that remain n turned on
	 */
	int bulbSwitch(int n) {
		return int(sqrt(n));
	}
};

/**
 * Test cases
 */
int main(void) {
	Solution sol;
	int n;

	// test case 1
	n = 3;
	std::cout << "bulbSwitch(" << n << ") = " << sol.bulbSwitch(n) << std::endl;

	// test case 2
	n = 0;
	std::cout << "bulbSwitch(" << n << ") = " << sol.bulbSwitch(n) << std::endl;

	// test case 3
	n = 1;
	std::cout << "bulbSwitch(" << n << ") = " << sol.bulbSwitch(n) << std::endl;

	return 0;
}