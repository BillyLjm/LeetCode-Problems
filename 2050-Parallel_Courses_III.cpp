/*******************************************************************************
 * 2050-Parallel_Courses_III.cpp
 * Billy.Ljm
 * 18 October 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/parallel-courses-iii/
 *
 * You are given an integer n, which indicates that there are n courses labeled
 * from 1 to n. You are also given a 2D integer array relations where
 * relations[j] = [prevCoursej, nextCoursej] denotes that course prevCoursej
 * has to be completed before course nextCoursej (prerequisite relationship).
 * Furthermore, you are given a 0-indexed integer array time where time[i]
 * denotes how many months it takes to complete the (i+1)th course.
 *
 * You must find the minimum number of months needed to complete all the courses
 * following these rules:
 * - You may start taking a course at any time if the prerequisites are met.
 * - Any number of courses can be taken at the same time.
 *
 * Return the minimum number of months needed to complete all the courses.
 * 
 * Note: The test cases are generated such that it is possible to complete every
 * course (i.e., the graph is a directed acyclic graph).
 *
 * ===========
 * My Approach
 * ===========
 * So we have to start at the many roots of the graph, and traverse all its
 * children while remembering the maximum time taken to reach each node.
 * Traversing the roots and children can be done by counting the in-degree of
 * each node, similar to topological sorting. Then, to find the maximum time,
 * we can use dynamic programming to calculate the maximum time of children
 * based on their parents
 *
 * This has a time complexity of O(n + e), and space complexity of O(n + e),
 * where n is the number of nodes and e is the number of edges.
 ******************************************************************************/

#include <iostream>
#include <vector>
#include <queue>

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
	int minimumTime(int n, vector<vector<int>>& relations, vector<int>& time) {
		vector<vector<int>> adj(n, vector<int>()); // adjacency matrix
		vector<int> indeg(n, 0); // in-degree of each node
		queue<int> qq; // to iterate in topological order
		vector<int> maxtime(n, 0); // maximum time to reach each node

		// parse graph
		for (vector<int> relation : relations) {
			adj[relation[0] - 1].push_back(relation[1] - 1);
			indeg[relation[1] - 1] += 1;
		}

		// start from roots
		for (int i = 0; i < indeg.size(); i++) {
			if (indeg[i] == 0) {
				qq.push(i);
				maxtime[i] = time[i];
			}
		}

		// traverse the rest of the graph in topological order
		while (not qq.empty()) {
			for (int neigh : adj[qq.front()]) {
				// calculate minimum time for neighbours
				maxtime[neigh] = max(maxtime[neigh],
					maxtime[qq.front()] + time[neigh]);
				// update in-degree of neighbours
				indeg[neigh]--;
				if (indeg[neigh] == 0) qq.push(neigh);
			}
			qq.pop();
		}

		// return time to complete all courses
		return *max_element(maxtime.begin(), maxtime.end());
	}
};

/**
 * Test cases
 */
int main(void) {
	Solution sol;
	int n;
	vector<vector<int>> relations;
	vector<int> time;

	// test case 1
	n = 3;
	relations = { {1,3},{2,3} };
	time = { 3,2,5 };
	std::cout << "minimumTime(" << n << "," << relations << "," << time << ") = ";
	std::cout << sol.minimumTime(n, relations, time) << std::endl;

	// test case 2
	n = 5;
	relations = { {1,5},{2,5},{3,5},{3,4},{4,5} };
	time = { 1,2,3,4,5 };
	std::cout << "minimumTime(" << n << "," << relations << "," << time << ") = ";
	std::cout << sol.minimumTime(n, relations, time) << std::endl;

	return 0;
}