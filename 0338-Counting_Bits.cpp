/*******************************************************************************
 * 0338-Counting_Bits.cpp
 * Billy.Ljm
 * 01 September 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/counting-bits/
 *
 * Given an integer n, return an array ans of length n + 1 such that for each i
 * (0 <= i <= n), ans[i] is the number of 1's in the binary representation of i.
 *
 * ===========
 * My Approach
 * ===========
 * So, ans[0] = 0 and ans[1] = 1. Then ans[2] = 1+ans[0] and ans[3] = 1+ans[1].
 * Subsequently, ans[4] = 1+ans[0], ans[5] = 1+ans[1], ans[6] = 1+ans[2] and so
 * on. Thus, we can build up the vector this way.
 *
 * This has a time complexity of O(n), and a space complexity of O(1), where
 * n is the integer
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
	vector<int> countBits(int n) {
		vector<int> out;

		// base case
		if (n == 0) out = { 0 };
		else out = { 0, 1 };

		// recursively build output vector
		int tmp; // to remember output vector size between recrusion
		while (true) {
			tmp = out.size();
			for (int i = 0; i < tmp; i++) {
				if (out.size() == n + 1) return out;
				else out.push_back(1 + out[i]);
			}
		}
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
	std::cout << "countBits(" << n << ") = ";
	std::cout << sol.countBits(n) << std::endl;

	// test case 2
	n = 5;
	std::cout << "countBits(" << n << ") = ";
	std::cout << sol.countBits(n) << std::endl;

	return 0;
}