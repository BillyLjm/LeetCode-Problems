/*******************************************************************************
 * 0064-Minimum_Path_Sum.cpp
 * Billy.Ljm
 * 27 Mar 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/minimum-path-sum/
 * Given a m x n grid filled with non-negative numbers, find a path from top
 * left to bottom right, which minimizes the sum of all numbers along its path.
 *
 * ===========
 * My Approach
 * ===========
 * We'll use dynamic programming to calculate the minimum path sum to endpoints
 * that are increasingly downwards and rightwards. This avoids recalculating
 * overlapping paths, such as DR, RD, etc.
 *
 * This would have a time complexity of O(m*n), where m and n are the width and
 * height of the grid respectively. And I'll overwrite/mutate the input grid to
 * achieve a space complexity of O(1).
 ******************************************************************************/

#include <iostream>
#include <vector>
#include <algorithm>

class Solution {
public:
	/**
	 * Finds the path from the top left of a grid of integers to the bottom right,
	 * which minimises the sum of elements along the path
	 *
	 * @param grid grid of integers to traverse
	 *
	 * @return minimum sum of elements connecting grid[0][0] to grid[m][n]
	 */
	int minPathSum(std::vector<std::vector<int>>& grid) {
		int m = grid[0].size(); // width of grid
		int n = grid.size(); // height of grid
		std::cout << m << ",," << n << std::endl;
		for (int steps = 1; steps < m + n - 1; steps++) { // total down+right steps
			for (int i = 0; i < std::min(n, steps + 1); i++) { // downards steps
				int j = steps - i; // rightwards steps
				// fill up grid[i][j]
				if (j >= m) {
					continue;
				}
				else  if (i == 0) {
					grid[i][j] += grid[i][j - 1];
				}
				else if (j == 0) {
					grid[i][j] += grid[i - 1][j];
				}
				else {
					grid[i][j] += std::min(grid[i - 1][j], grid[i][j - 1]);
				}
			}
		}

		return grid[n-1][m-1];
	}
};

/**
 * << operator for vectors
 */
template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& v) {
	os << "[";
	for (int i = 0; i < v.size(); i++) {
		os << v[i] << ",";
	}
	os << "\b]";
	return os;
}

/**
 * Test cases
 */
int main(void) {
	Solution sol;
	std::vector<std::vector<int>> grid;

	// test case 1
	grid = { {1,3,1}, {1,5,1}, {4,2,1} };
	std::cout << "minPathSum(" << grid << ") = "
		<< sol.minPathSum(grid) << std::endl;

	// test case 2
	grid = { {1,2,3}, {4,5,6} };
	std::cout << "minPathSum(" << grid << ") = "
		<< sol.minPathSum(grid) << std::endl;

	return 0;
}