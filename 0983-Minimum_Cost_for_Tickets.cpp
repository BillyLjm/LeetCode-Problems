/*******************************************************************************
 * 0983-Minimum_Cost_for_Tickets.cpp
 * Billy.Ljm
 * 28 Mar 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/minimum-cost-for-tickets/
 * You have planned some train traveling one year in advance. The days of the
 * year in which you will travel are given as an integer array days. Each day is
 * an integer from 1 to 365. Train tickets are sold in three different ways:
 *
 * - a 1-day pass is sold for costs[0] dollars,
 * - a 7-day pass is sold for costs[1] dollars, and
 * - a 30-day pass is sold for costs[2] dollars.
 *
 * The passes allow that many days of consecutive travel. For example, if we get
 * a 7-day pass on day 2, then we can travel for 7 days: 2, 3, 4, 5, 6, 7, and
 * 8. Return the minimum number of dollars you need to travel every day in the
 * given list of days.
 *
 * ===========
 * My Approach
 * ===========
 * Buying 7 1-day passes is the same as buying 1 7-day pass, so we only have to
 * consider the cheaper option for all subsequent days. Thus, we can use dynamic
 * programming to compare across these equivalent options and calculate the
 * minimum cost efficiently.
 *
 * This has a time complexity of O(n) and space complexity of O(n), where n is
 * the number of days travelled.
 ******************************************************************************/

#include <iostream>
#include <vector>
#include <algorithm>

class Solution {
public:
	/**
	 * Finds the minimum cost to travel in the given list of days.
	 *
	 * @param days The list of days to travel.
	 * @param costs the costs of [1-day, 7-day, 30-day] passes.
	 *
	 * @return minimum cost to travel in the given list of days.
	 */
	int mincostTickets(std::vector<int>& days, std::vector<int>& costs) {
		// find cheapest pass
		int mincosts = costs[0];
		for (int i = 1; i < 3; i++) {
			mincosts = std::min(mincosts, costs[i]);
		}

		// cost to travel to days[i]
		std::vector<int> totcost(days.size(), costs[0] * 365);
		for (int i = 0; i < days.size(); i++) {

			// cost to travel to days[i-1]
			int prevcost = (i == 0) ? 0 : totcost[i - 1];

			// 1 day pass (w/ cheapest pass)
			totcost[i] = std::min(totcost[i], prevcost + mincosts);

			// check for multiple days w/ 7 days pass
			for (int j = i; j < days.size(); j++) {
				if (days[j] - days[i] > 6) {
					break;
				}
				else {
					totcost[j] = std::min(totcost[j], prevcost + costs[1]);
				}
			}

			// check for multiple days w/ 30 days pass
			for (int j = i; j < days.size(); j++) {
				if (days[j] - days[i] > 29) {
					break;
				}
				else {
					totcost[j] = std::min(totcost[j], prevcost + costs[2]);
				}
			}
		}

		return totcost.back();
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
	std::vector<int> days;
	std::vector<int> costs;

	// test case 1
	days = { 1,4,6,7,8,20 };
	costs = { 2,7,15 };
	std::cout << "mincostTickets(" << days << ", " << costs << ") = "
		<< sol.mincostTickets(days, costs) << std::endl;

	// test case 2
	days = { 1,2,3,4,5,6,7,8,9,10,30,31 };
	costs = { 2,7,15 };
	std::cout << "mincostTickets(" << days << ", " << costs << ") = "
		<< sol.mincostTickets(days, costs) << std::endl;

	return 0;
}