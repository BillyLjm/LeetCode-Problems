/*******************************************************************************
 * 1091-Shortest_Path_in_Binary_Matrix.cpp
 * Billy.Ljm
 * 01 June 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/shortest-path-in-binary-matrix/
 *
 * Given an n x n binary matrix grid, return the length of the shortest clear
 * path in the matrix. If there is no clear path, return -1.
 *
 * A clear path in a binary matrix is a path from the top-left cell
 * (i.e., (0, 0)) to the bottom-right cell (i.e., (n - 1, n - 1)) such that:
 * - All the visited cells of the path are 0.
 * - All the adjacent cells of the path are 8-directionally connected (i.e.,
 *   they are different and they share an edge or a corner).
 *
 * The length of a clear path is the number of visited cells of this path.
 *
 * ===========
 * My Approach
 * ===========
 * We'll use breadth-first search to explore paths starting from the top-left
 * cell until we reach the bottom-right cell.
 *
 * This has a time complexity of O(n^2) and space complexity of O(n^2), where
 * n is the width of the square matrix.
 ******************************************************************************/

#include <iostream>
#include <vector>
#include <queue>

/**
 * Solution
 */
class Solution {
public:
	int shortestPathBinaryMatrix(std::vector<std::vector<int>>& grid) {
		// visited cells will be marked by grid[i][j] > 1
		std::queue<std::pair<int, int>> qq; // queue of cells to visit next
		std::pair<int, int> crawler(0, 0); // cell being visited
		int nsteps = 1; // number of steps

		// enqueue first cell
		if (grid[0][0] == 0) qq.push(std::pair<int, int>(0, 0));
		grid[0][0] = 2; // mark as visited

		// breadth-first search
		while (!qq.empty()) {
			// pop only the current nsteps
			int qsize = qq.size();
			for (int i = 0; i < qsize; i++) {
				// visit next cell
				crawler = qq.front();
				qq.pop();
				// if destination reached, return
				if (crawler == std::pair<int, int>(grid[0].size() - 1, grid.size() - 1)) return nsteps;
				// else queue neighbours
				for (int nx : {crawler.first - 1, crawler.first, crawler.first + 1}) {
					for (int ny : {crawler.second - 1, crawler.second, crawler.second + 1}) {
						// check if new indices are valid
						if (nx == crawler.first && ny == crawler.second) continue;
						if (nx < 0 || nx >= grid[0].size()) continue;
						if (ny < 0 || ny >= grid[0].size()) continue;
						if (grid[nx][ny] != 0) continue;
						if (grid[nx][ny] > 1) continue; // means visited
						// queue neighbours
						qq.push(std::pair<int, int>(nx, ny));
						grid[nx][ny] = 2; //mark as visited
					}
				}
			}
			// increment nsteps
			nsteps++;
		}

		// no path found
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
	std::cout << "shortestPathBinaryMatrix(" << grid << ") = ";
	std::cout << sol.shortestPathBinaryMatrix(grid) << std::endl;

	// test case 2
	grid = { {0, 0, 0}, {1, 1, 0}, {1, 1, 0} };
	std::cout << "shortestPathBinaryMatrix(" << grid << ") = ";
	std::cout << sol.shortestPathBinaryMatrix(grid) << std::endl;

	// test case 3
	grid = { {1, 0, 0},{1, 1, 0},{1, 1, 0} };
	std::cout << "shortestPathBinaryMatrix(" << grid << ") = ";
	std::cout << sol.shortestPathBinaryMatrix(grid) << std::endl;

	return 0;
}