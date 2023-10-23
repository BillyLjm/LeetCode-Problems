/*******************************************************************************
 * 0342-Power_of_Four.cpp
 * Billy.Ljm
 * 23 October 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/power-of-four/
 *
 * Given an integer n, return true if it is a power of four. Otherwise, return
 * false.
 *
 * An integer n is a power of four, if there exists an integer x such that
 * n == 4^x.
 *
 * ===========
 * My Approach
 * ===========
 * We can rewrite the condition n == 4^x as log n = x log 4.
 *
 * This has a time complexity of O(1), and space complexity of O(1).
 ******************************************************************************/

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

/**
 * << operator for vectors
 */
template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& v) {
	os << "[";
	for (const auto elem : v) {
		os << elem << ",";
	}
	if (v.size() > 0) os << "\b";
	os << "]";
	return os;
}

/**
 * Solution
 */
class Solution {
public:
	bool isPowerOfFour(int n) {
		double tmp;
		if (n == 0) return false;
		else return (modf(log(n) / log(4), &tmp) < 0.0001);
	}
};

/**
 * Test cases
 */
int main(void) {
	Solution sol;
	int n;

	// test case 1
	n = 16;
	std::cout << "isPowerOfFour(" << n << ") = ";
	std::cout << std::boolalpha << sol.isPowerOfFour(n) << std::endl;

	// test case 2
	n = 5;
	std::cout << "isPowerOfFour(" << n << ") = ";
	std::cout << std::boolalpha << sol.isPowerOfFour(n) << std::endl;

	// test case 3
	n = 1;
	std::cout << "isPowerOfFour(" << n << ") = ";
	std::cout << std::boolalpha << sol.isPowerOfFour(n) << std::endl;

	return 0;
}