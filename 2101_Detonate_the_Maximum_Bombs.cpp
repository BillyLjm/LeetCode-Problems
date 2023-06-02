/*******************************************************************************
 * 2101_Detonate_the_Maximum_Bombs.cpp
 * Billy.Ljm
 * 02 June 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/detonate-the-maximum-bombs/
 *
 * You are given a list of bombs. The range of a bomb is defined as the area
 * where its effect can be felt. This area is in the shape of a circle with the
 * center as the location of the bomb.
 *
 * The bombs are represented by a 0-indexed 2D integer array bombs where
 * bombs[i] = [xi, yi, ri]. xi and yi denote the X-coordinate and Y-coordinate
 * of the location of the ith bomb, whereas ri denotes the radius of its range.
 *
 * You may choose to detonate a single bomb. When a bomb is detonated, it will
 * detonate all bombs that lie in its range. These bombs will further detonate
 * the bombs that lie in their ranges.
 *
 * Given the list of bombs, return the maximum number of bombs that can be
 * detonated if you are allowed to detonate only one bomb.
 *
 * ===========
 * My Approach
 * ===========
 * We just have to brute-force the solution, starting from each bomb and counting
 * the number of chain explosion. To find the chain, we will use depth-first
 * search to count the number of connected bombs. To optimise it slightly, we 
 * can use a sweepline algorithm to sort the bombs by x-coordinate, and then only 
 * search for bombs with x-distances less than the radius.
 *
 * This has a time complexity of O(n^2) and space complexity of O(n^2), where
 * n is the number of bombs.
 ******************************************************************************/

#include <iostream>
#include <vector>
#include <algorithm>

/**
 * Solution
 */
class Solution {
private:
	/**
	 * Depth-first search of all chained bombs for bombs[idx]
	 *
	 * @param idx index of bomb to explode
	 * @param bombs list of bombs sorted by x-coordinate, as [x, y, radius]
	 * @param visited visited[i] = true if bombs[i] has been visited
	 *
	 * @return number of bombs in chain explosion
	 */
	int dfs(int idx, std::vector<std::vector<int>>& bombs,
		std::vector<bool>& visited) {
		int nbombs = 1; // number of bombs in chain explosion
		visited[idx] = true; // mark bomb as visited

		// dfs bombs with larger x
		for (int i = idx + 1; i < bombs.size(); i++) {
			// x distance > r
			if (bombs[i][0] - bombs[idx][0] > bombs[idx][2]) {
				break;
			}
			// already visited
			else if (visited[i]) {
				continue;
			}
			// distance > r
			else if (std::pow(bombs[i][1] - bombs[idx][1], 2) +
				std::pow(bombs[i][0] - bombs[idx][0], 2) >
				std::pow(bombs[idx][2], 2)) {
				continue;
			}
			else {
				nbombs += dfs(i, bombs, visited);
			}
		}

		// dfs bombs with smaller x
		for (int i = idx - 1; i >= 0; i--) {
			// x distance > r
			if (bombs[idx][0] - bombs[i][0] > bombs[idx][2]) {
				break;
			}
			// already visited
			else if (visited[i]) {
				continue;
			}
			// distance > r
			else if (std::pow(bombs[i][1] - bombs[idx][1], 2) +
				std::pow(bombs[i][0] - bombs[idx][0], 2) >
				std::pow(bombs[idx][2], 2)) {
				continue;
			}
			else {
				nbombs += dfs(i, bombs, visited);
			}
		}

		return nbombs;
	}

public:
	/**
	 * Finds the largest chain explosion attainable with a set of bombs
	 *
	 * @param bombs list of bomb's [x position, y position, explosive radius]
	 *
	 * @return number of bombs in largest chain explosion
	 */
	int maximumDetonation(std::vector<std::vector<int>>& bombs) {
		// sort bombs by x position (for sweepline)
		std::sort(bombs.begin(), bombs.end(),
			[](const std::vector<int>& a, const std::vector<int>& b) {
				return a[0] < b[0];
			}
		);

		// depth first search for each starting bomb
		int maxbombs = INT_MIN;
		std::vector<bool> visited;
		for (int i = 0; i < bombs.size(); i++) {
			visited = std::vector<bool>(bombs.size(), false);
			maxbombs = std::max(maxbombs, dfs(i, bombs, visited));
		}

		return maxbombs;
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
	std::vector<std::vector<int>> bombs;

	// test case 1
	bombs = { {2, 1, 3}, { 6, 1, 4 } };
	std::cout << "maximumDetonation(" << bombs << ") = ";
	std::cout << sol.maximumDetonation(bombs) << std::endl;

	// test case 2
	bombs = { {1, 1, 5}, { 10, 10, 5 } };
	std::cout << "maximumDetonation(" << bombs << ") = ";
	std::cout << sol.maximumDetonation(bombs) << std::endl;

	// test case 3
	bombs = { {1, 2, 3}, { 2, 3, 1 }, { 3, 4, 2 }, { 4, 5, 3 }, { 5, 6, 4 } };
	std::cout << "maximumDetonation(" << bombs << ") = ";
	std::cout << sol.maximumDetonation(bombs) << std::endl;

	return 0;
}