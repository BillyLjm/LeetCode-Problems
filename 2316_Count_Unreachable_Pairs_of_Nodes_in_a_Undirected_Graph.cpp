/*******************************************************************************
 * 2316_Count_Unreachable_Pairs_of_Nodes_in_a_Undirected_Graph.cpp
 * Billy.Ljm
 * 25 Mar 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/count-unreachable-pairs-of-nodes-in-an-undirected-graph/
 * 
 * You are given an integer n. There is an undirected graph with n nodes,
 * numbered from 0 to n - 1. You are given a 2D integer array edges where
 * edges[i] = [ai, bi] denotes that there exists an undirected edge connecting
 * nodes ai and bi. Return the number of pairs of different nodes that are
 * unreachable from each other.
 *
 * ===========
 * My Approach
 * ===========
 * We'll use union-find to find the number of disjoint sets in the graph. Then,
 * pairs from disjoint sets would be unreachable from each other.
 *
 * This will have a time complexity of O(n+e) and space complexity of O(n),
 * where n is the number of nodes, and e is the number of edges.
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
};

/**
 * Solution
 */
class Solution {
public:
	/**
	 * Counts the number of pairs of nodes that are disjoint in a graph
	 *
	 * @param n number of nodes
	 * @param edges edges specified as [i,j] for node i to node j
	 *
	 * @return number of disjoint pairs
	 */
	long long countPairs(int n, std::vector<std::vector<int>>& edges) {
		// union-find algorithm
		UnionFind uf(n);
		for (std::vector<int> edge : edges) {
			uf.unionn(edge[0], edge[1]);
		}

		// count members in each disjoint set
		std::vector<int> members(n, 0);
		for (int i = 0; i < n; i++) {
			members[uf.find(i)]++;
		}

		// count pairs across each disjoint subset
		long long pairs = 0LL; // number of pairs
		long long sum = 0LL; // cumulative sum
		for (int c : members) {
			pairs += sum * c;
			sum += c;
		}
		return pairs;
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
	n = 3;
	edges = { {0, 1}, {0, 2}, {1, 2} };
	std::cout << "countPairs(" << n << ", " << edges << ") = "
		<< sol.countPairs(n, edges) << std::endl;

	// test case 2
	n = 7;
	edges = { {0,2}, {0,5}, {2,4}, {1,6}, {5,4} };
	std::cout << "countPairs(" << n << ", " << edges << ") = "
		<< sol.countPairs(n, edges) << std::endl;

	return 0;
}