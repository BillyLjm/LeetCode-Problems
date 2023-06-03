/*******************************************************************************
 * 1319-Number_of_Operations_to_Make_Network_Connected.cpp
 * Billy.Ljm
 * 23 Mar 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/number-of-operations-to-make-network-connected
 * 
 * There are n computers numbered from 0 to n - 1 connected by ethernet cables
 * connections forming a network where connections[i] = [ai, bi] represents a
 * connection between computers ai and bi. Any computer can reach any other
 * computer directly or indirectly through the network.
 *
 * You are given an initial computer network connections. You can extract
 * certain cables between two directly connected computers, and place them
 * between any pair of disconnected computers to make them directly connected.
 *
 * Return the minimum number of times you need to do this in order to make all
 * the computers connected. If it is not possible, return -1.
 *
 * ===========
 * My Approach
 * ===========
 * We can check if all the computers can be connected by simply ensuring the
 * number of cables/connections is larger than the number of computers.
 *
 * We then simply have to find the disjoint sets in the network, and connect
 * them together using an extra cable, which will always be available to us
 * since we already did the aforementioned check. These disjoint sets can be
 * found using the disjoint-set/union-find data structure.
 *
 * This would have a time complexity of O(n + e) and a space complexity of O(n),
 * where n is the number of computers/nodes, and e is the number of wires/edges.
 ******************************************************************************/

#include <iostream>
#include <vector>
#include <numeric>

/**
 * Union-find/Disjoint-set data structure
 */
class UnionFind {
private:
	std::vector<int> parent, rank;

public:
	/**
	 * Class Constructor
	 *
	 * @param size total number of nodes
	 */
	UnionFind(int size) {
		parent = std::vector<int>(size);
		std::iota(std::begin(parent), std::end(parent), 0);
		rank = std::vector<int>(size, 0);
	}

	/**
	 * Find set of node. Uses path compression.
	 *
	 * @param i node to find parent of
	 *
	 * @return parent of node[i]
	 */
	int find(int i) {
		if (parent[i] != i) {
			parent[i] = find(parent[i]);
		}
		return parent[i];
	}

	/**
	 * Union of connected cities. Uses union by rank.
	 *
	 * @param x node to union with y
	 * @param y node to union with x
	 */
	void unionn(int x, int y) {
		int xroot = find(x);
		int yroot = find(y);

		if (rank[xroot] < rank[yroot]) {
			parent[xroot] = yroot;
		}
		else if (rank[xroot] > rank[yroot]) {
			parent[yroot] = xroot;
		}
		else {
			parent[yroot] = xroot;
			rank[xroot]++;
		}
	}

	/**
	 * Count number of disjoint subsets
	 *
	 * @return number of disjoint subsets
	 */
	int count() {
		int size = 0;
		for (int i = 0; i < parent.size(); i++) {
			if (parent[i] == i) {
				size++;
			}
		}
		return size;
	}
};

/**
 * Solution
 */
class Solution {
public:
	/**
	 * Find the number of edge swaps needed to connect all nodes in a network
	 *
	 * @param n number of nodes
	 * @param connections vector of the edges at [node1, node2]
	 *
	 * @return number of edge/connection swaps for complete connection
	 */
	int makeConnected(int n, std::vector<std::vector<int>>& connections) {
		// check number of cables is larger than number of computers
		if (connections.size() < n - 1) {
			return -1;
		}

		// disjoint-set union find
		UnionFind uf(n);
		for (const std::vector<int> connection : connections) {
			uf.unionn(connection[0], connection[1]);
		}

		return uf.count() - 1;
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
	std::vector<std::vector<int>> connections;

	// test case 1
	n = 4;
	connections = { {0,1}, {0,2}, {1,2} };
	std::cout << "makeConnected(" << n << ", " << connections << ") = "
		<< sol.makeConnected(n, connections) << std::endl;

	// test case 2
	n = 6;
	connections = { {0,1}, {0,2}, {0,3}, {1,2}, {1,3} };
	std::cout << "makeConnected(" << n << ", " << connections << ") = "
		<< sol.makeConnected(n, connections) << std::endl;

	// test case 3
	n = 6;
	connections = { {0,1}, {0,2}, {0,3}, {1,2} };
	std::cout << "makeConnected(" << n << ", " << connections << ") = "
		<< sol.makeConnected(n, connections) << std::endl;

	return 0;
}