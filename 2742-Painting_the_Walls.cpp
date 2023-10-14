/*******************************************************************************
 * 2742-Painting_the_Walls.cpp
 * Billy.Ljm
 * 14 October 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/painting-the-walls/
 *
 * You are given two 0-indexed integer arrays, cost and time, of size n
 * representing the costs and the time taken to paint n different walls
 * respectively. There are two painters available:
 * - A paid painter that paints the ith wall in time[i] units of time and takes
 *   cost[i] units of money.
 * - A free painter that paints any wall in 1 unit of time at a cost of 0. But
 *   the free painter can only be used if the paid painter is already occupied.
 *
 * Return the minimum amount of money required to paint the n walls.
 *
 * ===========
 * My Approach
 * ===========
 * We want to paint n walls in the end. And if we choose to use the paid painter
 * on wall[i], then the free painter can be used for time[i] number of walls,
 * resulting in a total of (time[i] + 1) number of walls painted for cost[i].
 * So, we can use dynamic programming to calculate the minimum cost to paint
 * n walls by iterating through each wall, and considering assigning it to the
 * paid painter or not.
 *
 * This has a time complexity of O(n^2), and space complexity of O(n), where n
 * is the number of walls.
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
	int paintWalls(vector<int>& cost, vector<int>& time) {
		vector<int> dp(cost.size() + 1, INT_MAX);
		dp[0] = 0;

		// try painting i-th wall, and remember minimum costs
		for (int i = 0; i < cost.size(); i++) {
			// in reverse so that dp[j] uses dp[j-k] from the previous iter
			for (int j = dp.size() - 1; j >= 0; j--) {
				if (j - 1 - time[i] < 0) {
					dp[j] = min(dp[j], cost[i]);
				}
				else if (dp[j - 1 - time[i]] != INT_MAX) {
					dp[j] = min(dp[j], dp[j - 1 - time[i]] + cost[i]);
				}
			}
		}

		return dp.back();
	}
};

/**
 * Test cases
 */
int main(void) {
	Solution sol;
	vector<int> cost, time;

	// test case 1
	cost = { 1,2,3,2 };
	time = { 1,2,3,2 };
	std::cout << "paintWalls(" << cost << "," << time << ") = ";
	std::cout << sol.paintWalls(cost, time) << std::endl;

	// test case 2
	cost = { 2,3,4,2 };
	time = { 1,1,1,1 };
	std::cout << "paintWalls(" << cost << "," << time << ") = ";
	std::cout << sol.paintWalls(cost, time) << std::endl;

	return 0;
}