/*******************************************************************************
 * 1139-Largest_1-Bordered_Square.cpp
 * Billy.Ljm
 * 27 June 2024
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/largest-1-bordered-square/
 *
 * Given a 2D grid of 0s and 1s, return the number of elements in the largest
 * square subgrid that has all 1s on its border, or 0 if such a subgrid doesn't
 * exist in the grid.
 *
 * ===========
 * My Approach
 * ===========
 * We want to start form the largest square, check if it is 1-bordered, and if
 * not move on to the next largest square. This is done with plain iteration.
 * To efficiently check if a square is 1-bordered, we can pre-count the number
 * of consecutive 1's across the rows and the columns. Then we can immediately
 * check if a square if 1-bordered by accessing the pre-counted values for the
 * 4 corners.
 *
 * This has a time complexity of O(n*m^2) and space complexity of O(n*m), where
 * n and m are the large and smaller dimensions of the grid respectively.
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
	int largest1BorderedSquare(vector<vector<int>>& grid) {
		vector<vector<int>> cntrows(grid.size(), vector<int>(grid[0].size()));
		vector<vector<int>> cntcols(grid.size(), vector<int>(grid[0].size()));

		// pre-count consecutive 1's across rows
		for (int j = 0; j < grid[0].size(); j++) {
			cntrows[0][j] = grid[0][j];
		}
		for (int i = 1; i < grid.size(); i++) {
			for (int j = 0; j < grid[0].size(); j++) {
				cntrows[i][j] = grid[i][j] * (cntrows[i - 1][j] + 1);
			}
		}

		// pre-count consecutive 1's across cols
		for (int j = 0; j < grid.size(); j++) {
			cntcols[j][0] = grid[j][0];
		}
		for (int i = 1; i < grid[0].size(); i++) {
			for (int j = 0; j < grid.size(); j++) {
				cntcols[j][i] = grid[j][i] * (cntcols[j][i - 1] + 1);
			}
		}

		// check progressively smaller square
		for (int dimm = min(grid.size(), grid[0].size()); dimm >= 0; dimm--) {
			for (int i = 0; i < grid.size() - dimm; i++) {
				for (int j = 0; j < grid[0].size() - dimm; j++) {
					if (cntrows[i + dimm][j] > dimm &&
						cntrows[i + dimm][j + dimm] > dimm &&
						cntcols[i][j + dimm] > dimm &&
						cntcols[i + dimm][j + dimm] > dimm) {
						return (dimm + 1) * (dimm + 1);
					}
				}
			}
		}

		// no 1-bordered square found
		return 0;
	}
};

/**
 * Test cases
 */
int main(void) {
	Solution sol;
	vector<vector<int>> grid;

	// test case 1
	grid = { {1,1,1},{1,0,1},{1,1,1} };
	std::cout << "largest1BorderedSquare(" << grid << ") = ";
	std::cout << sol.largest1BorderedSquare(grid) << std::endl;

	// test case 2
	grid = { {1,1,0,0} };
	std::cout << "largest1BorderedSquare(" << grid << ") = ";
	std::cout << sol.largest1BorderedSquare(grid) << std::endl;

	return 0;
}