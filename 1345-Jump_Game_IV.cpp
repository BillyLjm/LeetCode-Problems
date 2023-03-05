/*******************************************************************************
 * 1345-Jump_Game_IV.cpp
 * Billy.Ljm
 * 05 Mar 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/jump-game-iv/
 * Given an array of integers arr, you are initially positioned at the first
 * index of the array. In one step you can jump from index i to index:
 * >> i + 1 where: i + 1 < arr.length.
 * >> i - 1 where: i - 1 >= 0.
 * >> j where: arr[i] == arr[j] and i != j.
 * Return the minimum number of steps to reach the last index of the array.
 * Notice that you can not jump outside of the array at any time.
 *
 * ===========
 * My Approach
 * ===========
 * I don't see any special structure of the jumps. So I'll use a general
 * algorithm to find the shortest path: breadth-first search.
 ******************************************************************************/

#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>

class Solution {
public:
	/**
	 * Find the minimum number of jumps between the start and end of an array
	 *
	 * @param arr array to jump across
	 *
	 * @return minimum number of jumps
	 */
	int minJumps(std::vector<int>& arr) {
		int nsize = int(arr.size());

		// group all elements w/ similar values
		std::unordered_map<int, std::vector<int>> similar;
		for (int i = 0; i < nsize; ++i) {
			similar[arr[i]].push_back(i);
		}

		// breadth first search
		std::vector<bool> visited(nsize, false); // true if index has been visited
		visited[0] = true;
		std::queue<int> queue; // index of nodes in current and next timestep
		queue.push(0);
		int step = 0; // number of steps taken

		while (queue.size() > 0) {
			// explore all nodes in current timestep
			int qsize = int(queue.size());
			for (int i = 0; i < qsize; i++) {
				int index = queue.front();
				queue.pop();
				visited[index] = true;

				// break if result found
				if (index == nsize - 1) {
					return step;
				}

				// mark adjacent nodes for expoloration
				if (index > 0 and not visited[index - 1]) { // explore i-1 next
					queue.push(index - 1);
				}
				if (index < nsize - 1 and not visited[index + 1]) { // explore i+1 next
					queue.push(index + 1);
				}
				for (int j : similar[arr[index]]) { // explore similar values
					queue.push(j);
				}
				similar[arr[index]].clear(); // don't check similar values again
			}

			step++;
		}

		return -1; // no path found
	}
};

/**
 * Print function for array
 */
template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& v) {
	os << "[";
	for (int i = 0; i < v.size(); ++i) {
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
	std::vector<int> arr;

	// test case 1
	arr = { 100, -23, -23, 404, 100, 23, 23, 23, 3, 404 };
	std::cout << "minJumps(" << arr << ") = " << sol.minJumps(arr) << std::endl;

	// test case 2
	arr = { 7 };
	std::cout << "minJumps(" << arr << ") = " << sol.minJumps(arr) << std::endl;

	// test case 3
	arr = { 7, 6, 9, 6, 9, 6, 9, 7 };
	std::cout << "minJumps(" << arr << ") = " << sol.minJumps(arr) << std::endl;
}