/*******************************************************************************
 * 1697-Checking_Existence_of_Edge_Length_Limited_Paths.cpp
 * Billy.Ljm
 * 29 Apr 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/checking-existence-of-edge-length-limited-paths/
 * 
 * An undirected graph of n nodes is defined by edgeList, where edgeList[i] =
 * [ui, vi, disi] denotes an edge between nodes ui and vi with distance disi.
 * Note that there may be multiple edges between two nodes.
 *
 * Given an array queries, where queries[j] = [pj, qj, limitj], your task is to
 * determine for each queries[j] whether there is a path between pj and qj such
 * that each edge on the path has a distance strictly less than limitj .
 *
 * Return a boolean array answer, where answer.length == queries.length and the
 * jth value of answer is true if there is a path for queries[j] is true, and
 * false otherwise.
 *
 * ===========
 * My Approach
 * ===========
 * For each query, we can use union-find to find the groups of nodes that are 
 * connected by edge-length-limited paths. Then we can just check if the two 
 * nodes are in the same disjoint set.
 *
 * To optimise for multiple queries, we sort the queries by limit, build up the
 * union-find to the first limit, answer the first query, and the then continue
 * the union-find to the second limit, answer the second query and so on. This
 * avoids having to do a whole new union-find for each query. 
 *
 * This has a time complexity of O(n + e log n + e log e + q log q) and space
 * complexity of O(n + q) since we sort in place but have to remember the
 * unsorted indices of queries, where n is the number of node, e is the number
 * of edges, and q is the number of queries.
 ******************************************************************************/

#include <iostream>
#include <vector>
#include <string>
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
	std::vector<bool> distanceLimitedPathsExist(int n,
		std::vector<std::vector<int>>& edgeList,
		std::vector<std::vector<int>>& queries) {
		// remember original indices of queries
		for (int i = 0; i < queries.size(); i++) {
			queries[i].push_back(i);
		}

		// sort by limit
		std::sort(queries.begin(), queries.end(),
			[](const std::vector<int>& a, const std::vector<int>& b) {
				return a[2] < b[2];
			});
		std::sort(edgeList.begin(), edgeList.end(),
			[](const std::vector<int>& a, const std::vector<int>& b) {
				return a[2] < b[2];
			});

		// main loop
		std::vector<bool> out(queries.size(), false); // output 
		UnionFind uf(n); // union-find data structure
		size_t eCrawl = 0; // edgeList crawler
		for (std::vector<int> query : queries) {
			// union-find algorithm
			while (eCrawl < edgeList.size() and edgeList[eCrawl][2] < query[2]) {
				uf.unionn(edgeList[eCrawl][0], edgeList[eCrawl][1]);
				eCrawl++;
			}
			// fill output array
			if (uf.find(query[0]) == uf.find(query[1])) {
				out[query[3]] = true;
			}
		}

		return out;
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
	std::vector<std::vector<int>> edgeList;
	std::vector<std::vector<int>> queries;

	// test case 1
	n = 3;
	edgeList = { {0, 1, 2}, {1, 2, 4}, {2, 0, 8}, {1, 0, 16} };
	queries = { {0, 1, 2}, {0, 2, 5} };
	std::cout << std::boolalpha << "distanceLimitedPathsExist(" << n << " ,"
		<< edgeList << ", " << queries << ") = " <<
		sol.distanceLimitedPathsExist(n, edgeList, queries) << std::endl;

	// test case 2
	n = 5;
	edgeList = { {0, 1, 10}, {1, 2, 5}, {2, 3, 9}, {3, 4, 13} };
	queries = { {0, 4, 14}, {1, 4, 13} };
	std::cout << std::boolalpha << "distanceLimitedPathsExist(" << n << " ,"
		<< edgeList << ", " << queries << ") = " <<
		sol.distanceLimitedPathsExist(n, edgeList, queries) << std::endl;

	return 0;
}