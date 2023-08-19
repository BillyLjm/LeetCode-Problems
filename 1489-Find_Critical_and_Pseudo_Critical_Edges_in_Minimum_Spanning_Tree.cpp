/*******************************************************************************
 * 1489-Find_Critical_and_Pseudo_Critical_Edges_in_Minimum_Spanning_Tree.cpp
 * Billy.Ljm
 * 19 August 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/find-critical-and-pseudo-critical-edges-in-minimum-spanning-tree/
 *
 * Given a weighted undirected connected graph with n vertices numbered from 0
 * to n - 1, and an array edges where edges[i] = [ai, bi, weighti] represents a
 * bidirectional and weighted edge between nodes ai and bi. A minimum spanning
 * tree (MST) is a subset of the graph's edges that connects all vertices
 * without cycles and with the minimum possible total edge weight.
 *
 * Find all the critical and pseudo-critical edges in the given graph's minimum
 * spanning tree (MST). An MST edge whose deletion from the graph would cause
 * the MST weight to increase is called a critical edge. On the other hand, a
 * pseudo-critical edge is that which can appear in some MSTs but not all.
 *
 * Note that you can return the indices of the edges in any order.
 *
 * ===========
 * My Approach
 * ===========
 * We'll use Kruskal's algorithm to find the minimum spanning trees (MST). First, 
 * we'll find the weight of all the MSTs. Then, we'll try removing each edge and
 * finding the MST again, if the weight is larger, then the edge is critical.
 * Lastly, we'll try forcing the edge into the MST, if the weight is the same,
 * then it is pseudo-critical
 *
 * This has a time complexity of O(n * e), and a space complexity of O(e^2 log e)
 * ,where n is the number of nodes and e is the number of edges.
 ******************************************************************************/

#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

/**
 * << operator for vectors
 */
template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& v) {
	os << "[";
	for (const auto elem : v) {
		os << elem << ",";
	}
	if (v.size() > 0) os << "\b";
	os << "]";
	return os;
}

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
	vector<vector<int>> findCriticalAndPseudoCriticalEdges(
		int n, vector<vector<int>>& edges) {
		// sort edges, remembering original index
		for (int i = 0; i < edges.size(); i++) edges[i].push_back(i);
		sort(edges.begin(), edges.end(), [](auto& left, auto& right) {
				return left[2] < right[2];
			});

		// find weight of the MST's
		UnionFind uf(n);
		int nedges = 0; // number of edges already added
		int mstweight = 0; // weight of MST
		for (vector<int> edge : edges) {
			if (nedges == n - 1) break;
			else if (uf.find(edge[0]) == uf.find(edge[1])) continue;
			else {
				uf.unionn(edge[0], edge[1]);
				nedges++;
				mstweight = mstweight + edge[2];
			}
		}
		if (nedges != n - 1) return { {}, {} }; // no mst

		// check if each edge is critical or pseudo critical
		vector<int> crit, pcrit;
		int currweight;
		for (int i = 0; i < edges.size(); i++) {
			// check if critical edge, by removing it
			uf = UnionFind(n);
			nedges = 0;
			currweight = 0;
			for (vector<int> edge : edges) {
				if (nedges == n - 1) break;
				else if (edge == edges[i]) continue; // don't add current edge
				else if (uf.find(edge[0]) == uf.find(edge[1])) continue;
				else {
					uf.unionn(edge[0], edge[1]);
					nedges++;
					currweight = currweight + edge[2];
				}
			}
			if (nedges != n - 1 or currweight > mstweight) {
				crit.push_back(edges[i][3]);
				continue;
			}

			// check if pseudo-critical edge, by adding it
			uf = UnionFind(n);
			uf.unionn(edges[i][0], edges[i][1]); // add current edge
			nedges = 1;
			currweight = edges[i][2];
			for (vector<int> edge : edges) {
				if (nedges == n) break;
				else if (uf.find(edge[0]) == uf.find(edge[1])) continue;
				else {
					uf.unionn(edge[0], edge[1]);
					nedges++;
					currweight = currweight + edge[2];
				}
			}
			if (nedges == n - 1 and currweight == mstweight) {
				pcrit.push_back(edges[i][3]);
			}
		}

		return { crit, pcrit };
	}
};

/**
 * Test cases
 */
int main(void) {
	Solution sol;
	int n;
	vector<vector<int>> edges;

	// test case 1
	n = 5;
	edges = { {0,1,1},{1,2,1},{2,3,2},{0,3,2},{0,4,3},{3,4,3},{1,4,6} };
	std::cout << "findCriticalAndPseudoCriticalEdges(" << n << "," << edges << ") = ";
	std::cout << sol.findCriticalAndPseudoCriticalEdges(n, edges) << std::endl;

	// test case 2
	n = 4;
	edges = { {0,1,1},{1,2,1},{2,3,1},{0,3,1} };
	std::cout << "findCriticalAndPseudoCriticalEdges(" << n << "," << edges << ") = ";
	std::cout << sol.findCriticalAndPseudoCriticalEdges(n, edges) << std::endl;

	return 0;
}