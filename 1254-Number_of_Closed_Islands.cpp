/*******************************************************************************
 * 1254-Number_of_Closed_Islands.cpp
 * Billy.Ljm
 * 06 Apr 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/number-of-closed-islands/
 * Given a 2D grid consists of 0s (land) and 1s (water).  An island is a maximal
 * 4-directionally connected group of 0s and a closed island is an island
 * totally (all left, top, right, bottom) surrounded by 1s.
 *
 * Return the number of closed islands.
 *
 * ===========
 * My Approach
 * ===========
 * To find a closed island, we can start at any land cell and flood fill its
 * neighbouring land cells. We then just have to iterate through all cells and
 * check if its water or part of any already-identified island, otherwise we
 * flood fill it and increment the counter.
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
	 * Finds the number of closed island in a grid of land (0s) and water (1s)
	 *
	 * @param grid The grid of land and water
	 *
	 * @return number of closed islands in grid
	 */
	int closedIsland(std::vector<std::vector<int>>& grid) {
		int numislands = 0;
		 
		for (size_t i = 0; i < grid.size(); i++) {
			for (size_t j = 0; j < grid[0].size(); j++) {
				if (grid[i][j] == 0) {
					numislands++;
					numislands -= int(floodfill(grid, i, j));
				}
			}
		}

		return numislands;
	}

private:
	/**
	 * Flood fills from grid[i][j] with 1s
	 *
	 * @param grid grid to flood fill
	 * @param i row index
	 * @param j column index
	 *
	 * @return true if flood fill reaches edge of grid, false otherwise
	 */
	bool floodfill(std::vector<std::vector<int>>&  grid, size_t i, size_t j) {
		// if flood fill reached edge
		bool edge = (i == 0 || i == grid.size() - 1 ||
			j == 0 || j == grid[0].size() - 1);
		
		// flood fill
		grid[i][j] = 1;
		if (j > 0 && grid[i][j - 1] == 0) {
			edge = floodfill(grid, i, j - 1) || edge;
		}
		if (j < grid[0].size() - 1 && grid[i][j + 1] == 0) {
			edge = floodfill(grid, i, j + 1) || edge;
		}
		if (i > 0 && grid[i - 1][j] == 0) {
			edge = floodfill(grid, i - 1, j) || edge;
		}
		if (i < grid.size() - 1 && grid[i + 1][j] == 0) {
			edge = floodfill(grid, i + 1, j) || edge;
		}

		return edge;
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
	grid = { {1,1,1,1,1,1,1,0}, {1,0,0,0,0,1,1,0}, {1,0,1,0,1,1,1,0},
		{1,0,0,0,0,1,0,1}, {1,1,1,1,1,1,1,0} };
	std::cout << "closedIsland(" << grid << ") = ";
	std::cout << sol.closedIsland(grid) << std::endl;

	// test case 2
	grid = { {0,0,1,0,0}, {0,1,0,1,0}, {0,1,1,1,0} };
	std::cout << "closedIsland(" << grid << ") = ";
	std::cout << sol.closedIsland(grid) << std::endl;

	// test case 2
	grid = { {1,1,1,1,1,1,1},
		{1,0,0,0,0,0,1},
		{1,0,1,1,1,0,1},
		{1,0,1,0,1,0,1},
		{1,0,1,1,1,0,1},
		{1,0,0,0,0,0,1},
		{1,1,1,1,1,1,1} };
	std::cout << "closedIsland(" << grid << ") = ";
	std::cout << sol.closedIsland(grid) << std::endl;

	return 0;
}