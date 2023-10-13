/*******************************************************************************
 * 0746-Min_Cost_Climbing_Stairs.cpp
 * Billy.Ljm
 * 13 October 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/min-cost-climbing-stairs/
 *
 * You are given an integer array cost where cost[i] is the cost of ith step on
 * a staircase. Once you pay the cost, you can either climb one or two steps.
 *
 * You can either start from the step with index 0, or the step with index 1.
 *
 * Return the minimum cost to reach the top of the floor.
 *
 * ===========
 * My Approach
 * ===========
 * We will use dynamic programming to calculate the minimum cost to climb up to
 * each step. To reach each step, we can climb from one or two steps before it.
 *
 * This has a time complexity of O(n), and space complexity of O(n), where n is
 * the number of steps
 ******************************************************************************/

#include <iostream>
#include <vector>

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
	int minCostClimbingStairs(vector<int>& cost) {
		vector<int> dp(cost.size() + 1, INT_MAX);
		dp[0] = 0;
		dp[1] = 0;

		for (int i = 2; i <= cost.size(); i++) {
			dp[i] = min(dp[i], dp[i - 1] + cost[i - 1]);
			dp[i] = min(dp[i], dp[i - 2] + cost[i - 2]);
		}

		return dp.back();
	}
};

/**
 * Test cases
 */
int main(void) {
	Solution sol;
	vector<int> cost;

	// test case 1
	cost = { 10,15,20 };
	std::cout << "minCostClimbingStairs(" << cost << ") = ";
	std::cout << sol.minCostClimbingStairs(cost) << std::endl;

	// test case 2
	cost = { 1,100,1,1,1,100,1,1,100,1 };
	std::cout << "minCostClimbingStairs(" << cost << ") = ";
	std::cout << sol.minCostClimbingStairs(cost) << std::endl;

	return 0;
}