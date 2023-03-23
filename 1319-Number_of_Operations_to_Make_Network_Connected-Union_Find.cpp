/*******************************************************************************
 * 1319-Number_of_Operations_to_Make_Network_Connected.cpp
 * Billy.Ljm
 * 23 Mar 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/number-of-operations-to-make-network-connected
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
#include <map>

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

		// create disjoint-set data structure
		int nsets = n;
		std::map<int, subset> subsets; // {computer: set}
		for (int i = 0; i < n; i++) {
			subsets[i] = { i, 0 };
		}

		// disjoint-set union-find algorithm
		for (const std::vector<int> connection : connections) {
			nsets = unionn(subsets, find(subsets, connection[0]),
				find(subsets, connection[1]), nsets);
		}

		return nsets - 1;
	}

private:
	/**
	 * Disjoint-set data structure
	 * https://www.geeksforgeeks.org/union-by-rank-and-path-compression-in-union-find-algorithm/
	 */
	struct subset {
		int parent;
		int rank;
	};

	/**
	 * Find set of city. Uses path compression.
	 * https://www.geeksforgeeks.org/union-by-rank-and-path-compression-in-union-find-algorithm/
	 *
	 * @param subsets disjoint-set {child/city: parent/set}
	 * @param i city to find
	 *
	 * @return parent of city i
	 */
	int find(std::map<int, subset>& subsets, int i) {
		if (subsets[i].parent != i) {
			subsets[i].parent = find(subsets, subsets[i].parent);
		}
		return subsets[i].parent;
	}

	/**
	 * Union of connected cities. Uses union by rank.
	 * https://www.geeksforgeeks.org/union-by-rank-and-path-compression-in-union-find-algorithm/
	 * Also updates the count of the number of disjoint sets
	 *
	 * @param subsets disjoint-set {child/city: parent/set}
	 * @param xroot parent of city x
	 * @param yroot parent of city y
	 * @param nsets number of disjoint sets before union
	 *
	 * @return number of disjoint sets after union
	 */
	int unionn(std::map<int, subset>& subsets, int xroot, int yroot, int nsets) {
		if (xroot == yroot) {
			return nsets;
		}
		else {
			if (subsets[xroot].rank < subsets[yroot].rank) {
				subsets[xroot].parent = yroot;
			}
			else if (subsets[xroot].rank > subsets[yroot].rank) {
				subsets[yroot].parent = xroot;
			}
			else {
				subsets[yroot].parent = xroot;
				subsets[xroot].rank++;
			}
			return nsets - 1;
		}
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