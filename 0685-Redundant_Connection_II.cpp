/*******************************************************************************
 * 0685-Redundant_Connection_II.cpp
 * Billy.Ljm
 * 03 June 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/redundant-connection-ii/
 *
 * In this problem, a rooted tree is a directed graph such that, there is
 * exactly one node (the root) for which all other nodes are descendants of this
 * node, plus every node has exactly one parent, except for the root node which
 * has no parents.
 *
 * The given input is a directed graph that started as a rooted tree with n
 * nodes (with distinct values from 1 to n), with one additional directed edge
 * added. The added edge has two different vertices chosen from 1 to n, and was
 * not an edge that already existed.
 *
 * The resulting graph is given as a 2D-array of edges. Each element of edges is
 * a pair [ui, vi] that represents a directed edge connecting nodes ui and vi,
 * where ui is a parent of child vi.
 *
 * Return an edge that can be removed so that the resulting graph is a rooted
 * tree of n nodes. If there are multiple answers, return the answer that occurs
 * last in the given 2D-array.
 *
 * ===========
 * My Approach
 * ===========
 * We'll assume that we can always make a rooted tree by removing one edge.
 * Then, adding back the removed edge will increase the in-degree of either
 * (1) a non-root node, or (2) the root node. In case (1), we can identify this
 * non-root node with an in-degree of 2, and try removing either edges until
 * there are no cycles and a tree is formed. In case (2), we have to find the
 * cycle and remove the last edge in the cycle.
 *
 * To find the cycle efficiently, we'll use the union-find algorithm where we
 * iterate through the edges and update the root of each node progressively. A
 * cycle will be formed when the two nodes to be unioned already have the same
 * root. Then, we just have to remove this edge to break the cycle.
 *
 * This has a time complexity of O(n) and space complexity of O(n), where n is
 * the number of nodes (and edges).
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
	 *
	 * @return true if x, y are already in the same disjoint set
	 */
	bool unionn(int x, int y) {
		int xroot = find(x);
		int yroot = find(y);

		// already in same set
		if (xroot == yroot) {
			return true;
		}
		// otherwise combine sets
		else {
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
			return false;
		}
	}
};

/**
 * Solution
 */
class Solution {
public:
	/**
	 * Finds the redundant edge which when removed will result in a rooted tree
	 *
	 * @param edges edges of graph as [from_node, to_node]
	 *
	 * @return last edge which has to be removed to make a rooted tree
	 */
	std::vector<int> findRedundantDirectedConnection(
		std::vector<std::vector<int>>& edges) {
		// count in-degree up to 1, removing any extra edge
		std::vector<bool> indeg(edges.size() + 1, false); // in-degree
		std::vector<int> removed = { }; // any edge that's removed
		for (int i = 0; i < edges.size(); i++) {
			// if indeg 1, count indegree
			if (indeg[edges[i][1]] == 0) { 
				indeg[edges[i][1]] = 1;
			}
			// if indeg 2, remove edge and store it separately
			else { 
				removed = edges[i];
				edges.erase(edges.begin() + i);
				i--;
			}
		}

		// find cycle in graph
		std::vector<int> loopedge = { }; // edge which causes the loop
		UnionFind uf(edges.size() + 2); // n nodes, but edges may now be n-1 long
		for (std::vector<int> edge : edges) {
			if (uf.unionn(edge[0], edge[1])) {
				// loop found
				loopedge = edge;
				break;
			}
		}

		// if edge removed, and theres no loop after, return removed edge
		if (not removed.empty() && loopedge.empty()) {
			return removed;
		}
		// if edge removed, but theres still a loop, return non-removed edge
		else if (not removed.empty()) {
			for (int i = 0; i < edges.size(); i++) {
				if (edges[i][1] == removed[1]) return edges[i];
			}
		}
		// if no edge removed, return the last edge that completes the cycles
		else {
			return loopedge;
		}
		// something went wrong
		return {};
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
	std::vector<std::vector<int>> edges;

	// test case 1
	edges = { { 1, 2 }, { 1, 3 }, { 2, 3 } };
	std::cout << "findRedundantDirectedConnection(" << edges << ") = ";
	std::cout << sol.findRedundantDirectedConnection(edges) << std::endl;

	// test case 2
	edges = { { 1, 2 }, { 2, 3 }, { 3, 4 }, { 4, 1 }, { 1, 5 } };
	std::cout << "findRedundantDirectedConnection(" << edges << ") = ";
	std::cout << sol.findRedundantDirectedConnection(edges) << std::endl;

	return 0;
}