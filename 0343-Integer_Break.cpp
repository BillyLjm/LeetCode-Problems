/*******************************************************************************
 * 0343-Integer_Break.cpp
 * Billy.Ljm
 * 06 October 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/integer-break/
 *
 * Given an integer n, break it into the sum of k positive integers, where
 * k >= 2, and maximize the product of those integers.
 *
 * Return the maximum product you can get.
 *
 * ===========
 * My Approach
 * ===========
 * For a given k, the product will be maximised when the integer is broken into
 * equal pieces, as n = kx and product = x^k = x^(n/x). This equation is
 * maximised when x = e = 2.718; but if x has to be an integer than x = 3 yields
 * the largest product. Thus, we just have to break out integer into 3's.
 * 
 * If the number is not a multiple of 3, then we break into [3,3,...,3,4] since
 * 3^(x-1) * 4 > 3^x * 1, or into [3,3,...,3,2] since 3^x * 2 > 3^(x-2) * 4 * 4.
 *
 * This has a time complexity of O(1), and a space complexity of O(1).
 ******************************************************************************/

#include <iostream>
#include <vector>

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
	int integerBreak(int n) {
		if (n <= 3) return n - 1;
		else if (n % 3 == 0) return pow(3, n / 3);
		else if (n % 3 == 1) return pow(3, n / 3 - 1) * 4;
		else return pow(3, n / 3) * 2;
	}
};

/**
 * Test cases
 */
int main(void) {
	Solution sol;
	int n;

	// test case 1
	n = 2;
	std::cout << "integerBreak(" << n << ") = ";
	std::cout << sol.integerBreak(n) << std::endl;

	// test case 2
	n = 10;
	std::cout << "integerBreak(" << n << ") = ";
	std::cout << sol.integerBreak(n) << std::endl;

	return 0;
}