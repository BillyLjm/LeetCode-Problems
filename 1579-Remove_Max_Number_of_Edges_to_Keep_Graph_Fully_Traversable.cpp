/*******************************************************************************
 * 1579-Remove_Max_Number_of_Edges_to_Keep_Graph_Fully_Traversable.cpp
 * Billy.Ljm
 * 30 Apr 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/remove-max-number-of-edges-to-keep-graph-fully-traversable/
 * Alice and Bob have an undirected graph of n nodes and three types of edges:
 * - Type 1: Can be traversed by Alice only.
 * - Type 2: Can be traversed by Bob only.
 * - Type 3: Can be traversed by both Alice and Bob.
 *
 * Given an array edges where edges[i] = [typei, ui, vi] represents a
 * bidirectional edge of type typei between nodes ui and vi, find the maximum
 * number of edges you can remove so that after removing the edges, the graph
 * can still be fully traversed by both Alice and Bob. The graph is fully
 * traversed by Alice and Bob if starting from any node, they can reach all
 * other nodes.
 *
 * Return the maximum number of edges you can remove, or return -1 if Alice and
 * Bob cannot fully traverse the graph.
 *
 * ===========
 * My Approach
 * ===========
 * For each person (Alice/Bob), a fully traversable graph of n nodes has minimum
 * n-1 edges. Thus, two people requires 2*(n-1) edges for a traversable graph.
 * However, we also have type 3 edges, which connect nodes for two people with
 * just one edge. Thus, we would prefer to connect with type 3 nodes first,
 * reducing the number of edges required by one (from 2*(n-1)) for each of them.
 *
 * We can use the union-find algorithm to connect nodes, starting with type 3
 * edges first. Then, k disjoint subsets would have (n-k) type 3 edges, each of
 * which subtracts from the 2*(n-1) edges required for a fully traversable graph.
 * 
 * Then, we just have to connect the remaining edges independently for Alice and
 * Bob to check if the graph is indeed fully traversable for both.
 *
 * This has a time complexity of O(n + e log n) and space complexity of O(n)
 * for the full union-find, where n is the number of nodes and e is the number
 * of edges.
 ******************************************************************************/

#include <iostream>
#include <vector>
#include <string>
#include <numeric>
#include <algorithm>

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
	 * Creates a copy of the class
	 *
	 * @return copy of the class
	 */
	UnionFind copy() {
		UnionFind uf(parent.size());
		uf.parent = parent;
		uf.rank = rank;
		return uf;
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
	 * Finds the maximum number of edges that can be removed while keeping the
	 * graph fully traversable for both Alice and Bob
	 *
	 * @param n number of nodes in graph
	 * @param edges edge b/w nodes specified as (type, from, to), where type 1
	 *        edges connect for Alice, type 2 for Bob, and type 3 for both.
	 *
	 * @return maximum number of edges that can be removed
	 */
	int maxNumEdgesToRemove(int n, std::vector<std::vector<int>>& edges) {
		// connect type 3 edges
		UnionFind uf1(n);
		for (std::vector<int> edge : edges) {
			if (edge[0] == 3) {
				uf1.unionn(edge[1] - 1, edge[2] - 1);
			}
		}
		int k = uf1.count();

		// connect remaining edges
		UnionFind uf2 = uf1.copy(); // uf1 = Alice, uf2 = Bob
		for (std::vector<int> edge : edges) {
			if (edge[0] == 1) { // Alice
				uf1.unionn(edge[1] - 1, edge[2] - 1);
			}
			else if (edge[0] == 2) { // Bob
				uf2.unionn(edge[1] - 1, edge[2] - 1);
			}
		}

		// check if Alice/Bob are not fully traversable
		if (uf1.count() != 1 or uf2.count() != 1) {
			return -1;
		}
		// return min number of edges
		else {
			return edges.size() - n - k + 2; // edges - 2*(n-1) + (n-k)
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
	std::vector<std::vector<int>> edges;

	// test case 1
	n = 4;
	edges = { {3,1,2}, {3,2,3}, {1,1,3}, {1,2,4}, {1,1,2}, {2,3,4} };
	std::cout << "maxNumEdgesToRemove(" << n << " ," << edges << ") = " <<
		sol.maxNumEdgesToRemove(n, edges) << std::endl;

	// test case 2
	n = 4;
	edges = { {3,1,2}, {3,2,3}, {1,1,4}, {2,1,4} };
	std::cout << "maxNumEdgesToRemove(" << n << " ," << edges << ") = " <<
		sol.maxNumEdgesToRemove(n, edges) << std::endl;

	// test case 3
	n = 4;
	edges = { {3,2,3}, {1,1,2}, {2,3,4} };
	std::cout << "maxNumEdgesToRemove(" << n << " ," << edges << ") = " <<
		sol.maxNumEdgesToRemove(n, edges) << std::endl;

	// test case 3
	n = 2;
	edges = { {1,1,2}, {2,1,2} };
	std::cout << "maxNumEdgesToRemove(" << n << " ," << edges << ") = " <<
		sol.maxNumEdgesToRemove(n, edges) << std::endl;

	return 0;
}