/*******************************************************************************
 * 0059-Spiral_Matrix_II.cpp
 * Billy.Ljm
 * 10 May 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/spiral-matrix-ii/
 *
 * Given a positive integer n, generate an n x n matrix filled with elements
 * from 1 to n^2 in spiral order.
 *
 * ===========
 * My Approach
 * ===========
 * We need to create a new matrix and traverse it in a spiral order while
 * filling it up. Instead of hard-coding the spiral order, I opted to create a
 * index-crawling robot where I specify a direction and when to turn.
 *
 * This has a time complexity of O(n^2) and space complexity of O(n^2), where
 * n is the given positive integer.
 ******************************************************************************/

#include <iostream>
#include <vector>
#include <algorithm>

 /**
  * Solution
  */
class Solution {
public:
	/**
	 * Creates n x n matrix filled with [1, ..., n^2] in spiral order
	 *
	 * @param n size of the desired matrix
	 *
	 * @return n x n matrix filled with [1, ..., n^2] in spiral order
	 */
	std::vector<std::vector<int>> generateMatrix(int n) {
		std::vector<std::vector<int>> mat(n, std::vector<int>(n, 0)); // matrix
		int dir = 0; // 0 right, 1 down, 2 left, 3 up
		size_t i = 0; // crawler will be at mat[i][j]
		size_t j = 0;

		for (int k = 1; k <= n * n; k++) {
			// fill up element
			mat[i][j] = k;

			// check for direction changes
			if ((dir == 0 && (j + 1 == n || mat[i][j + 1] != 0)) ||
				(dir == 1 && (i + 1 == n || mat[i + 1][j] != 0)) ||
				(dir == 2 && (j == 0 || mat[i][j - 1] != 0)) ||
				(dir == 3 && (i == 0 || mat[i - 1][j] != 0))) {
				dir = (dir + 1) % 4;
			}

			// crawl to next index
			if (dir == 0) {
				j++;
			} else if (dir == 1) {
				i++;
			} else if (dir == 2) {
				j--;
			} else if (dir == 3) {
				i--;
			}
		}

		return mat;
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
	int n;

	// test case 1
	n = 3;
	std::cout << "generateMatrix(" << n << ") = " << sol.generateMatrix(n) << std::endl;

	// test case 2
	n = 1;
	std::cout << "generateMatrix(" << n << ") = " << sol.generateMatrix(n) << std::endl;

	return 0;
}