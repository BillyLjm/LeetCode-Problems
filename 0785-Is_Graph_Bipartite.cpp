/*******************************************************************************
 * 0785-Is_Graph_Bipartite.cpp
 * Billy.Ljm
 * 19 May 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/is-graph-bipartite/
 *
 * There is an undirected graph with n nodes, where each node is numbered
 * between 0 and n - 1. You are given a 2D array graph, where graph[u] is an
 * array of nodes that node u is adjacent to. More formally, for each v in
 * graph[u], there is an undirected edge between node u and node v. The graph
 * has the following properties:
 *
 * - There are no self-edges (graph[u] does not contain u).
 * - There are no parallel edges (graph[u] does not contain duplicate values).
 * - If v is in graph[u], then u is in graph[v] (the graph is undirected).
 * - The graph may not be connected, meaning there may be two nodes u and v such
 *   that there is no path between them.
 *
 * A graph is bipartite if the nodes can be partitioned into two independent
 * sets A and B such that every edge in the graph connects a node in set A and a
 * node in set B.
 *
 * Return true if and only if it is bipartite.
 *
 * ===========
 * My Approach
 * ===========
 * We can start from any node, label it A, traverse to all its neighbours, then
 * label them B and so on. If there is any contradiction in the labelling, then
 * the graph is not bipartite. If all nodes have been traversed and there is no
 * contradiction, then the graph is bipartite.
 *
 * This has a time complexity of O(e) and space complexity of O(v), where e is
 * the number of edges and v is the number of vertices.
 ******************************************************************************/

#include <iostream>
#include <vector>

/**
 * Solution
 */
class Solution {
private:
	/**
	 * Recursively label a node and traverse its neighbours
	 *
	 * @param node node to label
	 * @param label label for node
	 * @param graph graph[i] lists neighbours of node i
	 * @param visited visited[i] is true if node i has been visited
	 * @param labelled labelled[i] is the label for node i
	 *
	 * @return false if there is contradiction in labels, true if no problem
	 */
	bool recurse(int node, bool label, std::vector<std::vector<int>>& graph,
		std::vector<bool>& visited, std::vector<bool>& labelled) {
		// check labels of visited node
		if (visited[node]) {
			return labelled[node] == label;
		}
		// label unvisited nodes and recurse
		else {
			// label current node
			visited[node] = true;
			labelled[node] = label;
			// recursively label all neighbours
			for (int i : graph[node]) {
				if (not recurse(i, !label, graph, visited, labelled)) {
					return false; // reecho any contradiction
				}
			}
			// all neighbours labelled w/ no issues
			return true;
		}
	}

public:
	/**
	 * Checks if a graph is bipartite
	 *
	 * @param graph graph[i] lists neighbours of node i
	 *
	 * @return true if graph is bipartite, false if its not bipartite
	 */
	bool isBipartite(std::vector<std::vector<int>>& graph) {
		// remember if node is visited and if which bipartite its labelled as
		std::vector<bool> visited (graph.size(), false);
		std::vector<bool> labelled(graph.size());

		// traverse all nodes if unvisited
		for (int i = 0; i < graph.size(); i++) {
			if (not visited[i]) {
				if (not recurse(i, true, graph, visited, labelled)) {
					return false; // contradiction found, return false
				}
			}
		}

		// all node traversed w/o contradiction
		return true;
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
	std::vector<std::vector<int>> graph;

	// test case 1
	graph = { {1, 2, 3}, {0, 2}, {0, 1, 3}, {0, 2} };
	std::cout << std::boolalpha << "isBipartite(" << graph << ") = " <<
		sol.isBipartite(graph) << std::endl;

	// test case 2
	graph = { {1, 3}, {0, 2}, {1, 3}, {0, 2} };
	std::cout << std::boolalpha << "isBipartite(" << graph << ") = " <<
		sol.isBipartite(graph) << std::endl;

	return 0;
}