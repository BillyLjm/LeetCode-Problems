/*******************************************************************************
 * 1376-Time_Needed_to_Inform_All_Employees.cpp
 * Billy.Ljm
 * 03 June 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/time-needed-to-inform-all-employees/
 *
 * A company has n employees with a unique ID for each employee from 0 to n - 1.
 * The head of the company is the one with headID.
 *
 * Each employee has one direct manager given in the manager array where
 * manager[i] is the direct manager of the i-th employee, manager[headID] = -1.
 * Also, it is guaranteed that the subordination relationships have a tree
 * structure.
 *
 * The head of the company wants to inform all the company employees of an
 * urgent piece of news. He will inform his direct subordinates, and they will
 * inform their subordinates, and so on until all employees know about the
 * urgent news.
 *
 * The i-th employee needs informTime[i] minutes to inform all of his direct
 * subordinates (i.e., After informTime[i] minutes, all his direct subordinates
 * can start spreading the news).
 *
 * Return the number of minutes needed to inform all the employees about the
 * urgent news.
 *
 * ===========
 * My Approach
 * ===========
 * We'll use a depth-first search to simulate the informing of every employee.
 * In each recursion call, we'll remember the total informTime to reach the last
 * employee, and we'll return the maximum informTime.
 *
 * This has a time complexity of O(n) and space complexity of O(n), where n is
 * the number of employees.
 ******************************************************************************/

#include <iostream>
#include <vector>

/**
 * Solution
 */
class Solution {
private:
	/**
	 * Depth-first search through a tree
	 *
	 * @param idx the index of the current node
	 * @param adj the adjacency list of the tree
	 * @param weight the weight of each node
	 *
	 * @return the maximum sum of weights from the current node to last node
	 */
	int dfs(int idx, std::vector<std::vector<int>>& adj, std::vector<int>& weight) {
		int maxsum = 0;
		for (int i = 0; i < adj[idx].size(); i++) {
			maxsum = std::max(maxsum, dfs(adj[idx][i], adj, weight));
		}
		maxsum += weight[idx];
		return maxsum;
	}

public:
	/**
	 * Returns the maximum number of minutes to inform all employees
	 *
	 * @param n the number of employees
	 * @param headID the ID of the head of the company
	 * @param manager manager[i] = manger of employee[i]
	 * @param informTime informTime[i] = time for employee[i] to inform subordinates
	 *
	 * @return maximum time to inform all employees
	 */
	int numOfMinutes(int n, int headID, std::vector<int>& manager,
		std::vector<int>& informTime) {
		// convert the manager array into an adjacency list
		std::vector<std::vector<int>> adj(n);
		for (int i = 0; i < manager.size(); i++) {
			if (manager[i] != -1) adj[manager[i]].push_back(i);
		}

		// depth first search through tree
		return dfs(headID, adj, informTime);
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
	int n, headID;
	std::vector<int> manager, informTime;

	// test case 1
	n = 1;
	headID = 0;
	manager = { -1 };
	informTime = { 0 };
	std::cout << "numOfMinutes(" << n << "," << headID << "," << manager << ","
		<< informTime << ") = " << sol.numOfMinutes(n, headID, manager, informTime)
		<< std::endl;

	// test case 2
	n = 6;
	headID = 2;
	manager = { 2, 2, -1, 2, 2, 2 };
	informTime = { 0, 0, 1, 0, 0, 0 };
	std::cout << "numOfMinutes(" << n << "," << headID << "," << manager << ","
		<< informTime << ") = " << sol.numOfMinutes(n, headID, manager, informTime)
		<< std::endl;

	return 0;
}