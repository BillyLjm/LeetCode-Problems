/*******************************************************************************
 * 1857-Largest_Color_Value_in_Directed_Graph.cpp
 * Billy.Ljm
 * 09 Apr 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/largest-color-value-in-a-directed-graph/
 * There is a directed graph of n colored nodes and m edges. The nodes are
 * numbered from 0 to n - 1.
 *
 * You are given a string colors where colors[i] is a lowercase English letter
 * representing the color of the ith node in this graph (0-indexed). You are
 * also given a 2D array edges where edges[j] = [aj, bj] indicates that there is
 * a directed edge from node aj to node bj.
 *
 * A valid path in the graph is a sequence of nodes x1 -> x2 -> x3 -> ... -> xk
 * such that there is a directed edge from xi to xi+1 for every 1 <= i < k. The
 * color value of the path is the number of nodes that are colored the most
 * frequently occurring color along that path.
 *
 * Return the largest color value of any valid path in the given graph, or -1 if
 * the graph contains a cycle.
 *
 * ===========
 * My Approach
 * ===========
 * We can use Kahn's topological sorting algorithm to traverse the directed
 * graph starting from nodes with no incoming edges. For each node, we remember
 * the color value for the path traversed thus far, and at the end we return the
 * maximum color value across all paths/nodes and color. If there are cycles in
 * the graph, there will be unpopped nodes and we can return -1.
 *
 * This has a time complexity of O(n + e) and space complexity of O(n + e), 
 * where n is the number of nodes and e is the number of edges.
 ******************************************************************************/

#include <iostream>
#include <vector>
#include <string>
#include <queue>

class Solution {
public:
	/**
	 * Finds the largest color value of any valid path in a directed graph. The
	 * color value is the number of nodes that are colored in the specific color
	 * across a acyclic path in the graph.
	 *
	 * @param colors colors[i] is the color of node[i], in lowercase English
	 * @param edges listed of directed edges from edges[i][0] to edges[i][1]
	 *
	 * @return the largest color value of any acyclic path in the graph, or -1 if
	 * there is a cycle in the graph
	 */
	int largestPathValue(std::string colors,
		std::vector<std::vector<int>>& edges) {

		// pre-process data
		size_t n = colors.length(); // number of nodes
		std::vector<int> inDeg(n, 0); // indegree of each node
		std::vector<std::vector<int>> adjList(n, std::vector<int>()); // adjacency list
		for (std::vector<int> edge : edges) {
			adjList[edge[0]].push_back(edge[1]);
			inDeg[edge[1]]++;
		}

		// Kahn's topological sorting algorithm
		std::queue<int> qq; // queue of nodes to pop
		std::vector<std::vector<int>> colorVal(n, std::vector<int>(26, 0)); // color values of each node
		// start with nodes w/o incoming edges
		for (int i = 0; i < n; i++) {
			if (inDeg[i] == 0) {
				qq.push(i);
				colorVal[i][colors[i] - 'a']++;
			}
		}
		// traverse graph
		while (!qq.empty()) {
			// dequeue node
			int node = qq.front();
			qq.pop();
			// enqueue neighbors
			for (int neighbor : adjList[node]) {
				// update color values
				for (int i = 0; i < 26; i++) {
					colorVal[neighbor][i] = std::max(colorVal[neighbor][i],
						colorVal[node][i] + (colors[neighbor] - 'a' == i));
				}
				// decrement indegree
				inDeg[neighbor]--;
				// if indegree is 0, push to queue
				if (inDeg[neighbor] == 0) {
					qq.push(neighbor);
				}
			}
		}

		// check for any remaining cycles
		for (int i = 0; i < n; i++) {
			if (inDeg[i] > 0) {
				return -1;
			}
		}

		// calculate maximum color value
		int maxColorVal = 0;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < 26; j++) {
				maxColorVal = std::max(maxColorVal, colorVal[i][j]);
			}
		}
		return maxColorVal;
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
	std::string colors;
	std::vector<std::vector<int>> edges;

	// test case 1
	colors = "abaca";
	edges = { {0, 1}, {0, 2}, {2, 3}, {3, 4} };
	std::cout << "largestPathValue(" << colors << "," << edges << ") = "
		<< sol.largestPathValue(colors, edges) << std::endl;

	// test case 2
	colors = "a";
	edges = { {0, 0} };
	std::cout << "largestPathValue(" << colors << "," << edges << ") = "
		<< sol.largestPathValue(colors, edges) << std::endl;

	return 0;
}