/*******************************************************************************
 * 2360-Longest_Cycle_in_a_Graph.cpp
 * Billy.Ljm
 * 26 Mar 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/longest-cycle-in-a-graph/
 * You are given a directed graph of n nodes numbered from 0 to n - 1, where
 * each node has at most one outgoing edge. The graph is represented with a
 * given 0-indexed array edges of size n, indicating that there is a directed
 * edge from node i to node edges[i]. If there is no outgoing edge from node i,
 * then edges[i] == -1. Return the length of the longest cycle in the graph. If
 * no cycle exists, return -1. A cycle is a path that starts and ends at the
 * same node.
 *
 * ===========
 * My Approach
 * ===========
 * We'll use Kahn's algorithm to sort/remove all acylcic nodes, by iteratively
 * removing edge nodes with zero in-degree. Then, we'll visit all the remaining
 * cyclic nodes to find the longest cycle.
 *
 * This will have a time complexity of O(n) and space complexity of O(n),
 * where n is the number of nodes.
 ******************************************************************************/

#include <iostream>
#include <vector>
#include <queue>

class Solution {
public:
	/**
	 * Finds the longest cycle in a directed graph
	 *
	 * @param edges edges[i] = j represents a direct edge from node i to j
	 *
	 * @return number of nodes in the longest cycle
	 */
	int longestCycle(std::vector<int>& edges) {
		int node; // node crawler

		// in-degree of each node
		std::vector<int> in(edges.size(), 0);
		for (int edge : edges) {
			if (edge != -1) {
				in[edge]++;
			}
		}

		// Kahn's algorithm
		std::queue<int> qq;
		for (int i = 0; i < edges.size(); i++) {
			if (in[i] == 0) {
				qq.push(i);
			}
		}
		while (not qq.empty()) {
			node = qq.front();
			qq.pop();
			if (edges[node] != -1) {
				in[edges[node]]--;
				if (in[edges[node]] == 0) {
					qq.push(edges[node]);
				}
			}
		}

		// find longest cycle
		// we'll reuse in-degree to track visited nodes, by setting it to zero
		int maxlen = 0;
		int currlen;
		for (int i = 0; i < edges.size(); i++) {
			// only visit cyclic and unvisited nodes
			if (in[i] != 0) {
				// check for loops from node i
				node = i;
				in[i] = 0; // mark as visited
				currlen = 0;

				// iteratively traverse & check for loops
				while (true) {
					node = edges[node];
					if (node == -1) { // not a loop, abort
						currlen = 0;
						break;
					}
					else if (node == i) { // loop found
						currlen++; // add last edge
						break;
					}
					else {
						in[node] = 0; // mark new node as visited
						currlen++; // add edge to new node
					}
				}

				// remember max loop
				if (currlen > maxlen) {
					maxlen = currlen;
				}
			}
		}

		return (maxlen == 0) ? -1 : maxlen;
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
	std::vector<int> edges;

	// test case 1
	edges = { 3, 3, 4, 2, 3 };
	std::cout << "longestCycle(" << edges << ") = "
		<< sol.longestCycle(edges) << std::endl;

	// test case 2
	edges = { 2, -1, 3, 1 };
	std::cout << "longestCycle(" << edges << ") = "
		<< sol.longestCycle(edges) << std::endl;

	return 0;
}