/*******************************************************************************
 * 2492-Minimum_Score_of_a_Path_Between_Two_Cities.cpp
 * Billy.Ljm
 * 22 Mar 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/minimum-score-of-a-path-between-two-cities/
 * 
 * You are given a positive integer n representing n cities numbered from 1 to n.
 * You are also given a 2D array roads where roads[i] = [ai, bi, distancei]
 * indicates that there is a bidirectional road between cities ai and bi with a
 * distance equal to distancei. The cities graph is not necessarily connected.
 * The score of a path between two cities is defined as the minimum distance of
 * a road in this path. Return the minimum possible score of a path between
 * cities 1 and n.
 *
 * ===========
 * My Approach
 * ===========
 * The question is essentially asking us to find the set of cities which are
 * (indirectly) linked to cities 1 and n. We can do this using a disjoint-set
 * data structure. We then have to return the minimum distance of in the
 * aforementioned set.
 *
 * https://www.geeksforgeeks.org/union-by-rank-and-path-compression-in-union-find-algorithm/
 * We will use union by rank and path compression for our union & find, as
 * described in the website above. This would result in each union/find having
 * O(n) runtime.
 *
 * However, the implementation in the above website has a lot of overhead due to
 * the struct. Thus, we'll use a lighter union-find implmenetation here.
 *
 * Thus, the overall time complexity would be O(n*e), and space complexity be
 * O(n), where n is the number of cities and e is the number of edges.
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
	 * Finds the minimum road distance that is connected to city 1 and city n
	 *
	 * @param n index of city to connect to, other than city 1
	 * @param roads [city1, city2, distance] of each road
	 *
	 * @return minimum road distance that is connected to city 1 and city n
	 */
	int minScore(int n, std::vector<std::vector<int>>& roads) {
		// union-find
		UnionFind uf(n + 1);
		for (std::vector<int> road : roads) {
			uf.unionn(road[0], road[1]);
		}

		// check city 0 and n connected
		if (uf.find(1) != uf.find(n)) {
			return -1;
		}

		// find minimum distance of desired set
		else {
			int mindist = INT_MAX;
			for (std::vector<int> road : roads) {
				if (uf.find(road[0]) == uf.find(1)) {
					mindist = std::min(mindist, road[2]);
				}
			}
			return mindist;
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
	std::vector<std::vector<int>> roads;

	// test case 1
	n = 4;
	roads = { {1,2,9}, {2,3,6}, {2,4,5}, {1,4,7} };
	std::cout << "minScore(" << n << ", " << roads << ") = "
		<< sol.minScore(n, roads) << std::endl;

	// test case 2
	n = 4;
	roads = { {1,2,2}, {1,3,4}, {3,4,7} };
	std::cout << "minScore(" << n << ", " << roads << ") = "
		<< sol.minScore(n, roads) << std::endl;

	return 0;
}