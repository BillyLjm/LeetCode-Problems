/*******************************************************************************
 * 0118-Pascals_Triangle.cpp
 * Billy.Ljm
 * 08 September 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/pascals-triangle/
 *
 * Given an integer numRows, return the first numRows of Pascal's triangle.
 *
 * ===========
 * My Approach
 * ===========
 * We'll just compute the rows one by one.
 *
 * This has a time complexity of O(n^2), and a space complexity of O(1), where
 * n is the number of rows to be generated.
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
	vector<vector<int>> generate(int numRows) {
		// init first row
		vector<vector<int>> out = vector<vector<int>>(numRows);
		out[0] = { 1 };

		// generate rows
		for (int i = 1; i < numRows; i++) {
			out[i] = vector<int>(out[i - 1].size() + 1, 1);
			for (int j = 1; j < out[i - 1].size(); j++) {
				out[i][j] = out[i - 1][j];
				out[i][j] = out[i][j] + out[i - 1][j - 1];
			}
		}

		// return
		return out;
	}
};

/**
 * Test cases
 */
int main(void) {
	Solution sol;
	int numRows;

	// test case 1
	numRows = 5;
	std::cout << "generate(" << numRows << ") = ";
	std::cout << sol.generate(numRows) << std::endl;

	// test case 2
	numRows = 1;
	std::cout << "generate(" << numRows << ") = ";
	std::cout << sol.generate(numRows) << std::endl;

	return 0;
}