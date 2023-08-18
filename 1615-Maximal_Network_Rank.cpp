/*******************************************************************************
 * 1615-Maximal_Network_Rank.cpp
 * Billy.Ljm
 * 18 August 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/maximal-network-rank/
 *
 * There is an infrastructure of n cities with some number of roads connecting
 * these cities. Each roads[i] = [ai, bi] indicates that there is a
 * bidirectional road between cities ai and bi.
 *
 * The network rank of two different cities is defined as the total number of
 * directly connected roads to either city. If a road is directly connected to
 * both cities, it is only counted once.
 *
 * The maximal network rank of the infrastructure is the maximum network rank of
 * all pairs of different cities.
 *
 * Given the integer n and the array roads, return the maximal network rank of
 * the entire infrastructure.
 *
 * ===========
 * My Approach
 * ===========
 * We just have to count the in-degree of each node, and choose the two nodes
 * with the highest in-degree. If there is a edge going between the two chosen
 * nodes, then the maximal network rank will be the sum of the two in-degrees
 * minus 1, which will still be higher or equal than any other node with lower
 * in-degree. However, is there are multiple nodes with the maximum in-degree,
 * we will have to iterate through all pairs until we find one without a common
 * road.
 *
 * This has a time complexity of O(n^2 + m), and a space complexity of  O(n + m)
 * ,where n is the number of nodes and m is the number of edges.
 ******************************************************************************/

#include <iostream>
#include <vector>
#include <set>
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
 * Solution
 */
class Solution {
public:
	int maximalNetworkRank(int n, vector<vector<int>>& roads) {
		vector<int> indeg (n, 0); // in-degree of each node
		vector<set<int>> adj (n); // adjacency matrix
		int maxrank;

		// parse roads
		for (vector<int> road : roads) {
			indeg[road[0]]++;
			indeg[road[1]]++;
			adj[road[0]].insert(road[1]);
			adj[road[1]].insert(road[0]);
		}

		// find max in-degrees
		vector<int> nidx(n);
		iota(nidx.begin(), nidx.end(), 0);
		sort(nidx.begin(), nidx.end(), [&](int i, int j) {
				return indeg[i] > indeg[j];
			});

		// calculate possible max rank
		maxrank = indeg[nidx[0]] + indeg[nidx[1]];
		if (adj[nidx[0]].find(nidx[1]) != adj[nidx[0]].end()) maxrank--;

		// check other nodes of similar in-degree
		for (int i = 0; i < n; i++) {
			if (indeg[nidx[i]] < indeg[nidx[0]]) break;
			for (int j = i + 1; j < n; j++) {
				if (indeg[nidx[j]] < indeg[nidx[1]]) break;
				// found similar in-degree, without common road
				if (adj[nidx[i]].find(nidx[j]) == adj[nidx[i]].end()) {
					maxrank = indeg[nidx[i]] + indeg[nidx[j]];
					return maxrank;
				}
			}
		}

		return maxrank;
	}
};

/**
 * Test cases
 */
int main(void) {
	Solution sol;
	int n;
	vector<vector<int>> roads;

	// test case 1
	n = 4;
	roads = { {0,1},{0,3},{1,2},{1,3} };
	std::cout << "maximalNetworkRank(" << n << "," << roads << ") = ";
	std::cout << sol.maximalNetworkRank(n, roads) << std::endl;

	// test case 2
	n = 5;
	roads = { {0,1},{0,3},{1,2},{1,3},{2,3},{2,4} };
	std::cout << "maximalNetworkRank(" << n << "," << roads << ") = ";
	std::cout << sol.maximalNetworkRank(n, roads) << std::endl;

	// test case 3
	n = 8;
	roads = { {0,1},{1,2},{2,3},{2,4},{5,6},{5,7} };
	std::cout << "maximalNetworkRank(" << n << "," << roads << ") = ";
	std::cout << sol.maximalNetworkRank(n, roads) << std::endl;

	return 0;
}