/*******************************************************************************
 * 2316_Count_Unreachable_Pairs_of_Nodes_in_a_Undirected_Graph.cpp
 * Billy.Ljm
 * 25 Mar 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/count-unreachable-pairs-of-nodes-in-an-undirected-graph/
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
#include <algorithm>

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
		std::vector<subset> subsets(n); // disjoint-set {child/city: parent/set}
		std::vector<int> count(n, 1); // count of cities in each set
		for (int i = 0; i < n; i++) {
			subsets[i] = { i, 0 };
		}
		for (const std::vector<int> edge : edges) {
			unionn(subsets, count, find(subsets, edge[0]),
				find(subsets, edge[1]));
		}

		// count number of pairs across disjoint sets
		long long pairs = 0LL; // number of pairs
		long long sum = 0LL; // cumulative sum
		for (int c : count) {
			pairs += sum * c;
			sum += c;
		}
		return pairs;
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
	int find(std::vector<subset>& subsets, int i) {
		if (subsets[i].parent != i) {
			subsets[i].parent = find(subsets, subsets[i].parent);
		}
		return subsets[i].parent;
	}

	/**
	 * Union of connected cities. Uses union by rank.
	 * https://www.geeksforgeeks.org/union-by-rank-and-path-compression-in-union-find-algorithm/
	 * and updates the count of cities in each set.
	 *
	 * @param subsets disjoint-set {city: set}
	 * @param count count of cities in each set {set: count}
	 * @param xroot parent of city x
	 * @param yroot parent of city y
	 */
	void unionn(std::vector<subset> &subsets, std::vector<int>& count,
		int xroot, int yroot) {
		if (xroot != yroot) {
			if (subsets[xroot].rank < subsets[yroot].rank) {
				subsets[xroot].parent = yroot;
				count[yroot] += count[xroot];
				count[xroot] = 0;
			}
			else if (subsets[xroot].rank > subsets[yroot].rank) {
				subsets[yroot].parent = xroot;
				count[xroot] += count[yroot];
				count[yroot] = 0;
			}
			else {
				subsets[yroot].parent = xroot;
				count[xroot] += count[yroot];
				count[yroot] = 0;
				subsets[xroot].rank++;
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