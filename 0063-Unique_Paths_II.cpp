/*******************************************************************************
 * 0063-Unique_Paths_II.cpp
 * Billy.Ljm
 * 12 August 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/unique-paths-ii/
 *
 * You are given an m x n integer array grid. There is a robot initially located
 * at the top-left corner (i.e., grid[0][0]). The robot tries to move to the
 * bottom-right corner (i.e., grid[m - 1][n - 1]). The robot can only move
 * either down or right at any point in time.
 *
 * An obstacle and space are marked as 1 or 0 respectively in grid. A path that
 * the robot takes cannot include any square that is an obstacle.
 *
 * Return the number of possible unique paths that the robot can take to reach
 * the bottom-right corner.
 *
 * The testcases are generated so that the answer <= 2 * 10^9.
 *
 * ===========
 * My Approach
 * ===========
 * The robot can only move down or right, thus we don't have to consider any
 * curved paths which greatly simplifies the problem. We just have to count
 * the number of paths for the top row and leftmost column, and propagate them
 * downwards and rightwards, to fill up the dynamic programming matrix.
 *
 * This has a time complexity of O(n*m), and a space complexity of  O(1) since
 * we reuse the arguments, where n and m are the height and width of the matrix.
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
	int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
		// start point
		if (obstacleGrid[0][0] == 1) return 0;
		else obstacleGrid[0][0] = 1;

		// count top row and leftmost column
		int npaths = 1;
		for (int i = 1; i < obstacleGrid.size(); i++) {
			if (obstacleGrid[i][0] == 1) npaths = 0;
			obstacleGrid[i][0] = npaths;
		}
		npaths = 1;
		for (int i = 1; i < obstacleGrid[0].size(); i++) {
			if (obstacleGrid[0][i] == 1) npaths = 0;
			obstacleGrid[0][i] = npaths;
		}

		// count rest of spaces
		for (int i = 1; i < obstacleGrid.size(); i++) {
			for (int j = 1; j < obstacleGrid[0].size(); j++) {
				if (obstacleGrid[i][j] == 0) {
					obstacleGrid[i][j] = obstacleGrid[i - 1][j]
						+ obstacleGrid[i][j - 1];
				}
				else {
					obstacleGrid[i][j] = 0;
				}
			}
		}

		return obstacleGrid.back().back();
	}
};

/**
 * Test cases
 */
int main(void) {
	Solution sol;
	vector<vector<int>> obstacleGrid;

	// test case 1
	obstacleGrid = { {0,0,0},{0,1,0},{0,0,0} };
	std::cout << "uniquePathsWithObstacles(" << obstacleGrid << ") = ";
	std::cout << sol.uniquePathsWithObstacles(obstacleGrid) << std::endl;

	// test case 2
	obstacleGrid = { {0,1},{0,0} };
	std::cout << "uniquePathsWithObstacles(" << obstacleGrid << ") = ";
	std::cout << sol.uniquePathsWithObstacles(obstacleGrid) << std::endl;

	return 0;
}