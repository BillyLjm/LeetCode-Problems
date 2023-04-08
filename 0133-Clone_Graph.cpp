/*******************************************************************************
 * 0133-Clone_Graph.cpp
 * Billy.Ljm
 * 08 Apr 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/clone-graph/
 * Given a reference of a node in a connected undirected graph.
 *
 * Return a deep copy (clone) of the graph.
 *
 * Each node in the graph contains a value (int) and a list (List[Node]) of its
 * neighbors.
 *
 * ===========
 * My Approach
 * ===========
 * Recursively traverse the graph and create an adjacency list of the graph.
 * Then iterate through the adjacency list, create a copy and connect the graph.
 *
 * This has a time complexity of O(n) and space complexity of O(n) since each
 * node is visited and copied once, where n is the number of nodes.
 ******************************************************************************/

#include <iostream>
#include <vector>
#include <unordered_set>

/**
 * Definition for a Node
 */
class Node {
public:
	int val;
	std::vector<Node*> neighbors;
	Node() {
		val = 0;
		neighbors = std::vector<Node*>();
	}
	Node(int _val) {
		val = _val;
		neighbors = std::vector<Node*>();
	}
	Node(int _val, std::vector<Node*> _neighbors) {
		val = _val;
		neighbors = _neighbors;
	}
};

class Solution {
public:
	/**
	 * Creates a deep copy of a graph
	 *
	 * @param node root of graph to copy
	 */
	Node* cloneGraph(Node* node) {
		std::vector<std::vector<int>> adjList;
		std::unordered_set<int> visited;

		if (node == nullptr) {
			return nullptr;
		}
		else {
			this->getAdjList(node, adjList, visited);
			return this->createGraph(adjList);
		}
	}

	/**
	 * Create adjacency list from graph
	 *
	 * @param node root of graph
	 * @param adjList vector to fill adjacency list in
	 * @param visited set of nodes that have already been visited
	 */
	void getAdjList(Node* node, std::vector<std::vector<int>>& adjList,
		std::unordered_set<int>& visited) {
		// if empty graph
		if (node == nullptr) {
			adjList = { {} };
			return;
		}

		// extend adjacency list to include current node
		while (adjList.size() < node->val) {
			adjList.push_back(std::vector<int>());
		}

		// fill currrent node
		for (Node* neighbour : node->neighbors) {
			adjList[node->val - 1].push_back(neighbour->val);
		}

		// recursively traverse graph
		visited.insert(node->val);
		for (Node* neighbour : node->neighbors) {
			if (visited.find(neighbour->val) == visited.end()) {
				getAdjList(neighbour, adjList, visited);
			}
		}
	}

	/**
	 * Create a graph from an adjacency list
	 *
	 * @param adjList adjacency list, where adjList[i] is the neigbours of node[i+1]
	 *
	 * @return pointer to node[0]
	 */
	Node* createGraph(std::vector<std::vector<int>> adjList) {
		// if empty graph
		if (adjList.empty()) {
			return nullptr;
		}

		// create nodes
		std::vector<Node*> nodes;
		for (int i = 0; i < adjList.size(); i++) {
			nodes.push_back(new Node(i + 1));
		}

		// add neighbours
		for (int i = 0; i < adjList.size(); i++) {
			for (int j = 0; j < adjList[i].size(); j++) {
				nodes[i]->neighbors.push_back(nodes[adjList[i][j] - 1]);
			}
		}

		return nodes[0];
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
	Node* root;
	Node* copy;
	std::vector<std::vector<int>> adjList;
	std::unordered_set<int> visited;

	// test case 1
	adjList = { {2,4}, {1,3}, {2,4}, {1,3} };
	root = sol.createGraph(adjList);
	copy = sol.cloneGraph(root);
	// print results
	std::cout << "cloneGraph(" << adjList << ") = ";
	adjList.clear();
	visited.clear();
	sol.getAdjList(copy, adjList, visited);
	std::cout << adjList << std::endl;
	

	// test case 2
	adjList = { {} };
	std::cout << adjList.empty();
	std::cout << "cloneGraph(" << adjList << ") = ";
	root = sol.createGraph(adjList);
	copy = sol.cloneGraph(root);
	// print results
	std::cout << "cloneGraph(" << adjList << ") = ";
	adjList.clear();
	visited.clear();
	sol.getAdjList(copy, adjList, visited);
	std::cout << adjList << std::endl;

	// test case 3
	adjList = {};
	std::cout << adjList.empty();
	std::cout << "cloneGraph(" << adjList << ") = ";
	root = sol.createGraph(adjList);
	copy = sol.cloneGraph(root);
	// print results
	std::cout << "cloneGraph(" << adjList << ") = ";
	adjList.clear();
	visited.clear();
	sol.getAdjList(copy, adjList, visited);
	std::cout << adjList << std::endl;

	return 0;
}