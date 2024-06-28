/*******************************************************************************
 * 2285-Maximum_Total_Importance_of_Roads.cpp
 * Billy.Ljm
 * 28 June 2024
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/maximum-total-importance-of-roads/
 *
 * You are given an integer n denoting the number of cities in a country. The
 * cities are numbered from 0 to n - 1.
 *
 * You are also given a 2D integer array roads where roads[i] = [ai, bi] denotes
 * that there exists a bidirectional road connecting cities ai and bi.
 *
 * You need to assign each city with an integer value from 1 to n, where each
 * value can only be used once. The importance of a road is then defined as the
 * sum of the values of the two cities it connects.
 *
 * Return the maximum total importance of all roads possible after assigning the
 * values optimally.
 *
 * ===========
 * My Approach
 * ===========
 * We will greedily assign the largest integer values to the most connected
 * road. We just have to find the degree of each node and assign it accordingly.
 *
 * This has a time complexity of O(n+m) and space complexity of O(n), where
 * n is the number of cities and m is the number of roads.
 ******************************************************************************/

#include <iostream>
#include <vector>
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
	long long maximumImportance(int n, vector<vector<int>>& roads) {
		// count indegrees
		vector<int> indeg(n, 0);
		for (vector<int> road : roads) {
			indeg[road[0]]++;
			indeg[road[1]]++;
		}

		// assign the largest weight to the most connected road
		long long impt = 0LL;
		sort(indeg.begin(), indeg.end(), less<int>());
		for (int i = 0; i < indeg.size(); i++) {
			impt += 1LL * (i + 1) * indeg[i];
		}
		return impt;
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
	n = 5;
	roads = { {0,1},{1,2},{2,3},{0,2},{1,3},{2,4} };
	std::cout << "maximumImportance(" << n << "," << roads << ") = ";
	std::cout << sol.maximumImportance(n, roads) << std::endl;

	// test case 2
	n = 5;
	roads = { {0,3},{2,4},{1,3} };
	std::cout << "maximumImportance(" << n << "," << roads << ") = ";
	std::cout << sol.maximumImportance(n, roads) << std::endl;

	return 0;
}