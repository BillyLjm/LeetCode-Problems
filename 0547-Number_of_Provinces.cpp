/*******************************************************************************
 * 0547-Number_of_Provinces.cpp
 * Billy.Ljm
 * 04 June 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/number-of-provinces/
 *
 * There are n cities. Some of them are connected, while some are not. If city a
 * is connected directly with city b, and city b is connected directly with city
 * c, then city a is connected indirectly with city c.
 *
 * A province is a group of directly or indirectly connected cities and no other
 * cities outside of the group.
 *
 * You are given an n x n matrix isConnected where isConnected[i][j] = 1 if the
 * ith city and the jth city are directly connected, and isConnected[i][j] = 0
 * otherwise.
 *
 * Return the total number of provinces.
 *
 * ===========
 * My Approach
 * ===========
 * This is textbook union-find. So we'll implement it with union by rank and
 * path compression, which is known have an almost-constant-time lookup.
 *
 * This has a time complexity of O(v + e) and space complexity of O(v), where v
 * is the number of vertices/cities and e the number of edges.
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
	 * Finds the number of disjoint sets in a group of cities.
	 *
	 * @param isConnected isConnected[i][j] = 1 if cities i and j are connected
	 *
	 * @return number of disjoint sets
	 */
	int findCircleNum(std::vector<std::vector<int>>& isConnected) {
		// union find algorithm
		UnionFind uf(isConnected.size());
		for (int i = 0; i < isConnected.size(); i++) {
			for (int j = i + 1; j < isConnected.size(); j++) {
				if (isConnected[i][j] == 1) {
					uf.unionn(i, j);
				}
			}
		}

		// count number of distinct sets
		int nsets = 0;
		for (int i = 0; i < isConnected.size(); i++) {
			if (uf.find(i) == i) nsets++;
		}

		return nsets;
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
	std::vector<std::vector<int>> isConnected;

	// test case 1
	isConnected = { {1, 1, 0}, {1, 1, 0}, {0, 0, 1} };
	std::cout << "findCircleNum(" << isConnected << ") = ";
	std::cout << sol.findCircleNum(isConnected) << std::endl;

	// test case 2
	isConnected = { {1, 0, 0}, {0, 1, 0}, {0, 0, 1} };
	std::cout << "findCircleNum(" << isConnected << ") = ";
	std::cout << sol.findCircleNum(isConnected) << std::endl;

	return 0;
}