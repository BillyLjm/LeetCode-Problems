/*******************************************************************************
 * 1351-Count_Negative_Numbers_in_a_Sorted_Matrix.cpp
 * Billy.Ljm
 * 08 June 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/count-negative-numbers-in-a-sorted-matrix/
 *
 * Given a m x n matrix grid which is sorted in non-increasing order both
 * row-wise and column-wise, return the number of negative numbers in grid.
 *
 * ===========
 * My Approach
 * ===========
 * We'll iterate row-wise, checking if each element is negative. If we find a
 * negative number, we can be assured that all the subsequent numbers will be
 * negative since the matrix is sorted. When checking the next row, we can also
 * be assured that the first negative number will occur at an earlier index.
 * Thus, we can skip checking a few elements.
 *
 * This has a time complexity of O(m*n) and space complexity of O(1), where m
 * and n are the number of rows and columns of the matrix.
 ******************************************************************************/

#include <iostream>
#include <vector>

/**
 * Solution
 */
class Solution {
public:
	/**
	 * Counts the number of negative elements in a sorted matrix.
	 * The matrix has to be sorted in descending order row-wise and column-wise.
	 *
	 * @params grid matrix elements
	 *
	 * @return number of negative elements in the matrix
	 */
	int countNegatives(std::vector<std::vector<int>>& grid) {
		int negnum = 0;
		int colnum = grid[0].size();
		int negcol = colnum; // index of first negative in current row

		// check each row
		for (std::vector<int> row : grid) {
			for (int i = 0; i < negcol; i++) {
				if (row[i] < 0) {
					negcol = i;
					break;
				}
			}
			negnum += colnum - negcol;
		}

		return negnum;
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
	grid = { {4, 3, 2, -1}, {3, 2, 1, -1}, {1, 1, -1, -2}, {-1, -1, -2, -3} };
	std::cout << "countNegatives(" << grid << ") = ";
	std::cout << sol.countNegatives(grid) << std::endl;

	// test case 2
	grid = { {3, 2}, {1, 0} };
	std::cout << "countNegatives(" << grid << ") = ";
	std::cout << sol.countNegatives(grid) << std::endl;

	return 0;
}