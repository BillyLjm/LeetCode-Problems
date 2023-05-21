/*******************************************************************************
 * 0934-Shortest_Bridge.cpp
 * Billy.Ljm
 * 21 May 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/shortest-bridge/
 *
 * You are given an n x n binary matrix grid where 1 represents land and 0
 * represents water.
 *
 * An island is a 4-directionally connected group of 1's not connected to any
 * other 1's. There are exactly two islands in grid.
 *
 * You may change 0's to 1's to connect the two islands to form one island.
 *
 * Return the smallest number of 0's you must flip to connect the two islands.
 *
 * ===========
 * My Approach
 * ===========
 * We'll use breadth-first search to find the shortest bridge. We start from one
 * of the islands, extend 1 cell past its perimeter, then 2 and so on until we
 * reach the other island. To execute the breadth-first search, we'll use a
 * priority queue to iterate through cells that progressively further from the
 * first island.
 *
 * This has a time complexity of O(n^2) and space complexity of O(1), where n
 * is the width and breadth of the grid to search.
 ******************************************************************************/

#include <iostream>
#include <vector>
#include <queue>

/**
 * Solution
 */
class Solution {
private:
	/**
	 * Recrusively explore a land mass and add coasts to a queue
	 *
	 * @param i explore from grid[i][j]
	 * @param j explore from grid[i][j]
	 * @param grid map of the area, where 1 represents land and 0 water
	 * @param qq queue to insert coasts into, by flattened queue index
	 */
	void findLand(int i, int j, std::vector<std::vector<int>>& grid,
		std::queue<int>& qq) {
		size_t n = grid[0].size(); // size of grid
		
		grid[i][j] = 2; // mark grid as visited

		// check if coast
		if ((i + 1 < n and grid[i + 1][j] == 0) or
			(i - 1 >= 0 and grid[i - 1][j] == 0) or
			(j + 1 < n and grid[i][j + 1] == 0) or
			(j - 1 >= 0 and grid[i][j - 1] == 0)) {
			qq.push(i * n + j);
		}

		// visit univisted neighbours
		if (i + 1 < n and grid[i + 1][j] == 1) {
			findLand(i + 1, j, grid, qq);
		}
		if (i - 1 >= 0 and grid[i - 1][j] == 1) {
			findLand(i - 1, j, grid, qq);
		}
		if (j + 1 < n and grid[i][j + 1] == 1) {
			findLand(i, j + 1, grid, qq);
		}
		if (j - 1 >= 0 and grid[i][j - 1] == 1) {
			findLand(i, j - 1, grid, qq);
		}
	}

public:
	/**
	 * Finds the length of the shortest bridge between two islands in a grid map
	 *
	 * @param grid map of the area, where 1 represents land and 0 water
	 *
	 * @return length of the shortest bridge between two islands
	 */
	int shortestBridge(std::vector<std::vector<int>>& grid) {
		size_t n = grid[0].size();
		std::queue<int> qq; // BFS queue
		int elem; // qq element

		// find first land mass, and mark it as 2 in grid
		for (int i = 0; i < grid.size(); i++) {
			for (int j = 0; j < grid[0].size(); j++) {
				if (grid[i][j] == 1) {
					findLand(i, j, grid, qq);
					break;
				}
			}
			if (not qq.empty()) break; // break out of both loops
		}

		// breadth-first search
		while (not qq.empty()) {
			// get top element
			elem = qq.front(); 
			int i = elem / n;
			int j = elem % n;
			qq.pop();

			// explore i+1, i-1
			for (int ii : {i + 1, i - 1}) {
				if (ii < 0 or ii >= n) {
					; // out of bounds, ignore
				}
				else if (grid[ii][j] == 1) { // other island found, return
					return grid[i][j] - 2;
				}
				else if (grid[ii][j] == 0) { // else increment distance
					grid[ii][j] = grid[i][j] + 1;
					qq.push(ii * n + j);
				}
			}

			// explore j+1, j-1
			for (int jj : {j + 1, j - 1}) {
				if (jj < 0 or jj >= n) {
					; // out of bounds, ignore
				}
				else if (grid[i][jj] == 1) { // other island found, return
					return grid[i][j] - 2;
				}
				else if (grid[i][jj] == 0) { // else increment distance
					grid[i][jj] = grid[i][j] + 1;
					qq.push(i * n + jj);
				}
			}
		}

		// can't find other island
		return -1;
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
	grid = { {0, 1}, {1, 0} };
	std::cout << "shortestBridge(" << grid << ") = ";
	std::cout << sol.shortestBridge(grid) << std::endl;

	// test case 2
	grid = { {0, 1, 0}, {0, 0, 0}, {0, 0, 1} };
	std::cout << "shortestBridge(" << grid << ") = ";
	std::cout << sol.shortestBridge(grid) << std::endl;

	// test case 3
	grid = { {1,1,1,1,1}, {1,0,0,0,1}, {1,0,1,0,1}, {1,0,0,0,1}, {1,1,1,1,1} };
	std::cout << "shortestBridge(" << grid << ") = ";
	std::cout << sol.shortestBridge(grid) << std::endl;

	return 0;
}