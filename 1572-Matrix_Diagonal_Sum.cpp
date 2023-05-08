/*******************************************************************************
 * 1572-Matrix_Diagonal_Sum.cpp
 * Billy.Ljm
 * 08 May 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/matrix-diagonal-sum/
 *
 * Given a square matrix mat, return the sum of the matrix diagonals.
 *
 * Only include the sum of all the elements on the primary diagonal and all the
 * elements on the secondary diagonal that are not part of the primary diagonal.
 *
 * ===========
 * My Approach
 * ===========
 * The only way is to iterate through each diagonal element and sum them up.
 *
 * This has a time complexity of O(n) and space complexity of O(1), where n is
 * width of the square matrix
 ******************************************************************************/

#include <iostream>
#include <vector>

/**
 * Solution
 */
class Solution {
public:
	/**
	 * Sums the diagonal elements of a square matrix
	 *
	 * @param mat matrix to sum
	 *
	 * @return sum of the diagonal elements
	 */
	int diagonalSum(std::vector<std::vector<int>>& mat) {
		int summ = 0; // sum of diagonal elements
		size_t w = mat.size() - 1; // width of matrix

		// sum diagonal elements
		for (int i = 0; i < mat.size(); i++) {
			summ = summ + mat[i][i];
			if (w - i != i) {
				summ = summ + mat[i][w - i];
			}
		}

		return summ;
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
	std::cout << "diagonalSum(" << mat << ") = " << sol.diagonalSum(mat) << std::endl;

	// test case 2
	mat = { {1, 1, 1, 1}, {1, 1, 1, 1}, {1, 1, 1, 1}, {1, 1, 1, 1} };
	std::cout << "diagonalSum(" << mat << ") = " << sol.diagonalSum(mat) << std::endl;

	// test case 3
	mat = { {5} };
	std::cout << "diagonalSum(" << mat << ") = " << sol.diagonalSum(mat) << std::endl;

	return 0;
}