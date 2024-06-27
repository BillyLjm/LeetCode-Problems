/*******************************************************************************
 * 1791-Find_Center_of_Star_Graph.cpp
 * Billy.Ljm
 * 27 June 2024
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/find-center-of-star-graph/
 *
 * There is an undirected star graph consisting of n nodes labeled from 1 to n.
 * A star graph is a graph where there is one center node and exactly n - 1
 * edges that connect the center node with every other node.
 *
 * You are given a 2D integer array edges where each edges[i] = [ui, vi]
 * indicates that there is an edge between the nodes ui and vi. Return the
 * center of the given star graph.
 *
 * ===========
 * My Approach
 * ===========
 * We just have to compare 2 edges and the center node will be the only node
 * that is present in both edges
 *
 * This has a time complexity of O(1) and space complexity of O(1).
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
	int findCenter(vector<vector<int>>& edges) {
		if (edges[0][0] == edges[1][0] or edges[0][0] == edges[1][1]) {
			return edges[0][0];
		}
		else {
			return edges[0][1];
		}
	}
};

/**
 * Test cases
 */
int main(void) {
	Solution sol;
	vector<vector<int>> edges;

	// test case 1
	edges = { {1,2},{2,3},{4,2} };
	std::cout << "findCenter(" << edges << ") = ";
	std::cout << sol.findCenter(edges) << std::endl;

	// test case 2
	edges = { {1,2},{5,1},{1,3},{1,4} };
	std::cout << "findCenter(" << edges << ") = ";
	std::cout << sol.findCenter(edges) << std::endl;

	return 0;
}