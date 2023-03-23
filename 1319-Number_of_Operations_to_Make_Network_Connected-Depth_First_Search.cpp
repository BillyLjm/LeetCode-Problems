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
 * We can then use depth-first traversal to find all the connections of an
 * arbitrary computer. If there are still unconnected computers, we will
 * use one of the extra cables (guaranteed because of the previous check) to
 * connect the new computer to the network. And then repeat the depth-first
 * traversal to find all the newly connected nodes. This is repeated until all
 * nodes are connected.
 *
 * This has a time complexity of O(n + e) and space complexity of O(e), where
 * n is the number of computers, and e the number of connections. since we need
 * to create an adjacency matrix which will take O(e) time and space, and then
 * visit tall the nodes which will take O(n) time.
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

		// create adjacency matrix
		std::map<int, std::vector<int>> adj;
		for (std::vector<int> connection : connections) {
			adj[connection[0]].push_back(connection[1]);
			adj[connection[1]].push_back(connection[0]);
		}

		// visit all computers, connecting as needed
		int nswaps = -1;
		std::vector<bool> visited(n, false); // visited[i] = true if node i has been visited
		for (int i = 0; i < n; i++) {
			if (visited[i]) { // ignore if already visited
				;
			}
			else { // else dfs traversal for all connected nodes
				nswaps++;
				dfs(i, adj, visited);
			}
		}

		return nswaps;
	}

private:
	/**
	 * Depth-first recursive traversal of all connected computers
	 *
	 * @param node current node, whose connections are to be traversed
	 * @param adj adjacency matrix; adj[node] = vector of connected nodes
	 * @param visited visited[i] = true if node i has been visited
	 */
	void dfs(int node, std::map<int, std::vector<int>> &adj,
		std::vector<bool> &visited) {
		for (int i : adj[node]) {
			if (not visited[i]) {
				visited[i] = true;
				dfs(i, adj, visited);
			}
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