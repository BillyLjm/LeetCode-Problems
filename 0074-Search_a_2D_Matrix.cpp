/*******************************************************************************
 * 0074-Search_a_2D_Matrix.cpp
 * Billy.Ljm
 * 07 August 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/search-a-2d-matrix/
 *
 * You are given an m x n integer matrix matrix with the following two properties:
 * - Each row is sorted in non-decreasing order.
 * - The first integer of each row is greater than the last integer of the
 *   previous row.
 *
 * Given an integer target, return true if target is in matrix or false otherwise.
 *
 * You must write a solution in O(log(m * n)) time complexity.
 *
 * ===========
 * My Approach
 * ===========
 * The matrix is essentially a sorted list reshaped into a matrix. So we can use
 * binary search to find the desired target easily and efficiently
 *
 * This has a time complexity of O(log(m*n)), and a space complexity of  O(1),
 * where m and n are the height and width of the matrix respecitvely.
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
	for (int i = 0; i < v.size(); i++) {
		os << v[i] << ",";
	}
	os << "\b]";
	return os;
}

/**
 * Solution
 */
class Solution {
public:
	bool searchMatrix(vector<vector<int>>& matrix, int target) {
		size_t nrow = matrix.size(), ncol = matrix[0].size();
		int start = 0, end = nrow * ncol - 1, mid;

		// binary search
		while (end - start > 1) {
			mid = (start + end) / 2;
			if (target > matrix[mid / ncol][mid % ncol]) start = mid;
			else end = mid;
		}

		// check last two elements
		if (target == matrix[end / ncol][end % ncol]) return true;
		else if (target == matrix[start / ncol][start % ncol]) return true;
		else return false;
	}
};

/**
 * Test cases
 */
int main(void) {
	Solution sol;
	vector<vector<int>> matrix;
	int target;

	// test case 1
	matrix = { {1,3,5,7},{10,11,16,20},{23,30,34,60} };
	target = 3;
	std::cout << "searchMatrix(" << matrix << "," << target << ") = ";
	std::cout << std::boolalpha << sol.searchMatrix(matrix, target) << std::endl;

	// test case 2
	matrix = { {1,3,5,7},{10,11,16,20},{23,30,34,60} };
	target = 13;
	std::cout << "searchMatrix(" << matrix << "," << target << ") = ";
	std::cout << std::boolalpha << sol.searchMatrix(matrix, target) << std::endl;

	// test case 3
	matrix = { {1, 1} };
	target = 13;
	std::cout << "searchMatrix(" << matrix << "," << target << ") = ";
	std::cout << std::boolalpha << sol.searchMatrix(matrix, target) << std::endl;

	return 0;
}