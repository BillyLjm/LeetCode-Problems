/*******************************************************************************
 * 1466-Reorder_Routes_to_Make_All_Paths_Lead_to_the_City_Zero.cpp
 * Billy.Ljm
 * 24 Mar 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/reorder-routes-to-make-all-paths-lead-to-the-city-zero/
 * There are n cities numbered from 0 to n - 1 and n - 1 roads such that there
 * is only one way to travel between two different cities (this network form a
 * tree). Last year, The ministry of transport decided to orient the roads in
 * one direction because they are too narrow. Roads are represented by
 * connections where connections[i] = [ai, bi] represents a road from city ai to
 * city bi. This year, there will be a big event in the capital (city 0), and
 * many people want to travel to this city. Your task consists of reorienting
 * some roads such that each city can visit the city 0. Return the minimum
 * number of edges changed. It's guaranteed that each city can reach city 0
 * after reorder.
 *
 * ===========
 * My Approach
 * ===========
 * We just have to traverse the entire tree (n-1 edges b/w n nodes) starting
 * form city 0, and count the number of roads with opposite direction. I'll
 * use breadth-first traversal here.
 *
 * This will have a time complexity of O(n) and space complexity of O(n), where
 * n is the number of cities.
 ******************************************************************************/

#include <iostream>
#include <vector>
#include <queue>

class Solution {
public:
	/**
	 * Finds the number of road reversals to make all roads end at city 0.
	 *
	 * @param n The number of cities.
	 * @param connections The roads between cities, as [from_city, to_city]
	 *
	 * @return number of road direction reversals
	 */
	int minReorder(int n, std::vector<std::vector<int>>& connections) {
		int count = 0; // number of road direction reversals

		// create adjacency matrix
		std::vector<std::vector<int>> adj(n);
		for (std::vector<int> connection : connections) {
			adj[connection[0]].push_back(connection[1]); // have to reverse
			adj[connection[1]].push_back(-connection[0]); // don't reverse
		}

		// breadth-first traversal
		int city; // current city
		std::vector<bool> visited(n, false); // true if city is visited
		std::queue<int> queue; // depth-first queue
		queue.push(0);
		while (not queue.empty()) {
			city = queue.front();
			queue.pop();
			visited[city] = true;
			for (int next_city : adj[city]) {
				if (not visited[abs(next_city)]) {
					if (next_city > 0) {
						count++;
					}
					queue.push(abs(next_city));
				}
			}
		}

		return count;
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
	std::vector<std::vector<int>> connections;

	// test case 1
	n = 6;
	connections = { {0,1},{1,3},{2,3},{4,0},{4,5} };
	std::cout << "minReorder(" << n << ", " << connections << ") = "
		<< sol.minReorder(n, connections) << std::endl;

	// test case 2
	n = 5;
	connections = { {1,0}, {1,2}, {3,2}, {3,4} };
	std::cout << "minReorder(" << n << ", " << connections << ") = "
		<< sol.minReorder(n, connections) << std::endl;

	// test case 3
	n = 3;
	connections = { {1,0}, {2,0} };
	std::cout << "minReorder(" << n << ", " << connections << ") = "
		<< sol.minReorder(n, connections) << std::endl;

    return 0;
}