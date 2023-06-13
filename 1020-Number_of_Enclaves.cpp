/*******************************************************************************
 * 1020-Number_of_Encalves.cpp
 * Billy.Ljm
 * 07 Apr 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/number-of-enclaves/
 * You are given an m x n binary matrix grid, where 0 represents a sea cell and
 * 1 represents a land cell.
 *
 * A move consists of walking from one land cell to another adjacent
 * (4-directionally) land cell or walking off the boundary of the grid.
 *
 * Return the number of land cells in grid for which we cannot walk off the
 * boundary of the grid in any number of moves.
 *
 * ===========
 * My Approach
 * ===========
 * We can start at any land cell and flood fill its neighbouring land cells. We
 * count the number of cells filled, and add it to a cumulative sum if the fill
 * doesn't go off the edge. We then just have to iterate through all cells and
 * until all cells have been filled.
 *
 * This has a time complexity of O(n) since each cell is visited/marked once,
 * and a space complexity of O(1) since we reuse/mutate the input grid, where n
 * is the size of the 2D grid.
 ******************************************************************************/

#include <iostream>
#include <vector>

class Solution {
public:
	/**
	 * Finds the number of land cells not connected to the boundary, in a grid
	 * of water (0s) and land (1s)
	 *
	 * @param grid The grid of land and water
	 *
	 * @return number of land cells that are disconnected from the grid edges
	 */
	int numEnclaves(std::vector<std::vector<int>>& grid) {
		int numcells = 0;

		for (size_t i = 0; i < grid.size(); i++) {
			for (size_t j = 0; j < grid[0].size(); j++) {
				if (grid[i][j] == 1) {
					numcells += floodfill(grid, i, j);
				}
			}
		}

		return numcells;
	}

private:
	/**
	 * Flood fills from grid[i][j] with 0s
	 *
	 * @param grid grid to flood fill
	 * @param i row index
	 * @param j column index
	 *
	 * @return number of cells filled; if it goes off the edge return 0
	 */
	int floodfill(std::vector<std::vector<int>>& grid, size_t i, size_t j) {
		int tmp, numcells;

		// flood fill current site
		grid[i][j] = 0;
		if (i == 0 || i == grid.size() - 1 || j == 0 || j == grid[0].size() - 1) {
			numcells = 0;
		}
		else {
			numcells = 1;
		}

		// flood fill adjacent sites
		if (j > 0 && grid[i][j - 1] == 1) {
			tmp = floodfill(grid, i, j - 1);
			if (tmp != 0 && numcells != 0) {
				numcells += tmp;
			}
			else {
				numcells = 0;
			}
		}
		if (j < grid[0].size() - 1 && grid[i][j + 1] == 1) {
			tmp = floodfill(grid, i, j + 1);
			if (tmp != 0 && numcells != 0) {
				numcells += tmp;
			}
			else {
				numcells = 0;
			}
		}
		if (i > 0 && grid[i - 1][j] == 1) {
			tmp = floodfill(grid, i - 1, j);
			if (tmp != 0 && numcells != 0) {
				numcells += tmp;
			}
			else {
				numcells = 0;
			}
		}
		if (i < grid.size() - 1 && grid[i + 1][j] == 1) {
			tmp = floodfill(grid, i + 1, j);
			if (tmp != 0 && numcells != 0) {
				numcells += tmp;
			}
			else {
				numcells = 0;
			}
		}

		return numcells;
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
	grid = { {0,0,0,0},{1,0,1,0},{0,1,1,0},{0,0,0,0} };
	std::cout << "numEnclaves(" << grid << ") = ";
	std::cout << sol.numEnclaves(grid) << std::endl;

	// test case 2
	grid = { {0,1,1,0},{0,0,1,0},{0,0,1,0},{0,0,0,0} };
	std::cout << "numEnclaves(" << grid << ") = ";
	std::cout << sol.numEnclaves(grid) << std::endl;

	return 0;
}