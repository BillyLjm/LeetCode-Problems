/*******************************************************************************
 * 0054-Spiral_Matrix.cpp
 * Billy.Ljm
 * 09 May 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/spiral-matrix/
 *
 * Given an m x n matrix, return all elements of the matrix in spiral order.
 *
 * ===========
 * My Approach
 * ===========
 * We need to insert elements on the perimeter of the matrix first in spiral
 * order, and then repeat for the next layer and so on. This is naturally
 * recursive but to save on the overhead, we'll implement it iteratively.
 *
 * This has a time complexity of O(m*n) and space complexity of O(m*n), where 
 * m and n are the dimensions of the matrix.
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
	 * Returns the elements of a matrix in spiral order
	 *
	 * @param matrix matrix to take elements of
	 *
	 * @return vector of the matrix elements in spiral order
	 */
	std::vector<int> spiralOrder(std::vector<std::vector<int>>& matrix) {
		size_t n = matrix.size(); // height of matrix
		size_t m = matrix[0].size(); // width of matrix
		std::vector<int> out; // return value
		out.reserve(m * n);

		// fill up the spirals
		for (int i = 0; i < std::min(n, m) / 2.0; i++) { // for each siral
			for (int j = i; j < m - i; j++) { // insert top row
				out.push_back(matrix[i][j]);
			}
			for (int j = i + 1; j < n - i; j++) { // insert right column
				out.push_back(matrix[j][m - 1 - i]);
			}
			if (i != n - 1 - i) { // don't reinsert top row
				for (int j = m - 2 - i; j >= i; j--) { // insert bottom row
					out.push_back(matrix[n - 1 - i][j]);
				}
			}
			if (i != m - 1 - i) { // don't reinsert right column
				for (int j = n - 2 - i; j > i; j--) { // insert left column
					out.push_back(matrix[j][i]);
				}
			}
		}

		return out;
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
	std::vector<std::vector<int>> mat;

	// test case 1
	mat = { {1, 2, 3}, {4, 5, 6}, {7, 8, 9} };
	std::cout << "spiralOrder(" << mat << ") = " << sol.spiralOrder(mat) << std::endl;

	// test case 2
	mat = { {1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12} };
	std::cout << "spiralOrder(" << mat << ") = " << sol.spiralOrder(mat) << std::endl;

	return 0;
}