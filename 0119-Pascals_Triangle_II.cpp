/*******************************************************************************
 * 0119-Pascals_Triangle_II.cpp
 * Billy.Ljm
 * 16 October 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/pascals-triangle-ii/
 *
 * Given an integer rowIndex, return the rowIndexth (0-indexed) row of the
 * Pascal's triangle.
 *
 * In Pascal's triangle, each number is the sum of the two numbers directly
 * above it.
 *
 * ===========
 * My Approach
 * ===========
 * We can just literally execute the definition of Pascal's triangle.
 *
 * This has a time complexity of O(n^2), and space complexity of O(n), where n
 * is the row index given.
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
	vector<int> getRow(int rowIndex) {
		vector<int> dp(rowIndex + 1, 1);
		int prev, tmp;

		for (int i = 0; i < rowIndex; i++) {
			// update 1st number
			prev = dp[0];
			dp[0] = 1;
			// caclulate middle numbers
			for (int j = 1; j <= i; j++) {
				tmp = dp[j];
				dp[j] += prev;
				prev = tmp;
			}
			// last number will be 1 due to out initialisation
		}

		return dp;
	}
};

/**
 * Test cases
 */
int main(void) {
	Solution sol;
	int rowIndex;

	// test case 1
	rowIndex = 3;
	std::cout << "getRow(" << rowIndex << ") = ";
	std::cout << sol.getRow(rowIndex) << std::endl;

	// test case 2
	rowIndex = 0;
	std::cout << "getRow(" << rowIndex << ") = ";
	std::cout << sol.getRow(rowIndex) << std::endl;

	// test case 3
	rowIndex = 1;
	std::cout << "getRow(" << rowIndex << ") = ";
	std::cout << sol.getRow(rowIndex) << std::endl;

	return 0;
}