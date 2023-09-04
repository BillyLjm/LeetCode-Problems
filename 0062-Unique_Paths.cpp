/*******************************************************************************
 * 0062-Unique_Paths.cpp
 * Billy.Ljm
 * 03 September 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/unique-paths/
 *
 * There is a robot on an m x n grid. The robot is initially located at the
 * top-left corner (i.e., grid[0][0]). The robot tries to move to the
 * bottom-right corner (i.e., grid[m - 1][n - 1]). The robot can only move
 * either down or right at any point in time.
 *
 * Given the two integers m and n, return the number of possible unique paths
 * that the robot can take to reach the bottom-right corner.
 *
 * The test cases are generated so that the answer will be less than or equal to
 * 2 * 109.
 *
 * ===========
 * My Approach
 * ===========
 * We'll use dynamic programming to count the number of paths to reach each grid
 * space. npaths[i][j] = npaths[i-1] + npaths[j-1], and we just repeat for
 * increasing i and j.
 *
 * This has a time complexity of O(n*m), and a space complexity of O(n*m), where
 * n and m are the length and breadth of the grid respectively.
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
	int uniquePaths(int m, int n) {
		vector<vector<int>> dp(m, vector<int>(n, 1));

		for (int i = 1; i < dp.size(); i++) {
			for (int j = 1; j < dp[0].size(); j++) {
				dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
			}
		}

		return dp[m - 1][n - 1];
	}
};

/**
 * Test cases
 */
int main(void) {
	Solution sol;
	int m, n;

	// test case 1
	m = 3;
	n = 7;
	std::cout << "uniquePaths(" << m << "," << n << ") = ";
	std::cout << sol.uniquePaths(m, n) << std::endl;

	// test case 2
	m = 3;
	n = 2;
	std::cout << "uniquePaths(" << m << "," << n << ") = ";
	std::cout << sol.uniquePaths(m, n) << std::endl;

	return 0;
}