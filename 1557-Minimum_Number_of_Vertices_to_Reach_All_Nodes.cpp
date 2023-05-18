/*******************************************************************************
 * 1557-Minimum_Number_of_Vertices_to_Reach_All_Nodes.cpp
 * Billy.Ljm
 * 18 May 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/minimum-number-of-vertices-to-reach-all-nodes/
 *
 * Given a directed acyclic graph, with n vertices numbered from 0 to n-1, and
 * an array edges where edges[i] = [fromi, toi] represents a directed edge from
 * node fromi to node toi.
 *
 * Find the smallest set of vertices from which all nodes in the graph are
 * reachable. It's guaranteed that a unique solution exists.
 *
 * Notice that you can return the vertices in any order.
 *
 * ===========
 * My Approach
 * ===========
 * We'll count the in-degree of each node. Then, we simply have to count the
 * number of nodes with zero in-degree, since they must be started from
 * otherwise they would be unreachable. All other nodes with non-zero in-degree
 * can be reached from some other node. Note that this assumes there are no
 * cycles in the direct graph, since a unique solution is guaranteed to exist.
 *
 * To optimise the space further, we just need to remember if the in-degree is
 * zero or non-zero with a boolean.
 *
 * This has a time complexity of O(e) and space complexity of O(v + e), where
 * e is the number of edges and v is the number of vertices.
 ******************************************************************************/

#include <iostream>
#include <vector>

/**
 * Solution
 */
class Solution {
public:
	/**
	 * Finds the smallest set of vertices from which all other vertices are
	 * accessible in a directed graph.
	 *
	 * @param n number of vertices in graph
	 * @param edges directed edges of the graph, where edges[i] = [from_i, to_i]
	 *
	 * @return vector of the minimal set of vertices
	 */
	std::vector<int> findSmallestSetOfVertices(int n,
		std::vector<std::vector<int>>& edges) {
		// calculate in-degree
		std::vector<bool> indeg(n, false);
		for (std::vector<int> edge : edges) {
			indeg[edge[1]] = true;
		}

		// find minimal vertices to access whole graph
		std::vector<int> minvert;
		for (int i = 0; i < n; i++) {
			if (indeg[i] == false) {
				minvert.push_back(i);
			}
		}

		return minvert;
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
	int n;
	std::vector<std::vector<int>> edges;

	// test case 1
	n = 6;
	edges = { {0, 1}, {0, 2}, {2, 5}, {3, 4}, {4, 2} };
	std::cout << "findSmallestSetOfVertices(" << n << "," << edges << ") = "
		<< sol.findSmallestSetOfVertices(n, edges) << std::endl;

	// test case 2
	n = 5;
	edges = { {0, 1}, {2, 1}, {3, 1}, {1, 4}, {2, 4} };
	std::cout << "findSmallestSetOfVertices(" << n << "," << edges << ") = "
		<< sol.findSmallestSetOfVertices(n, edges) << std::endl;

	return 0;
}