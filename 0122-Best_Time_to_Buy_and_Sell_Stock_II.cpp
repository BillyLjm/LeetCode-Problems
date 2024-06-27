/*******************************************************************************
 * 0122-Best_Time_to_Buy_and_Sell_Stock_II.cpp
 * Billy.Ljm
 * 27 June 2024
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/best-time-to-buy-and-sell-stock-ii/
 *
 * You are given an integer array prices where prices[i] is the price of a given
 * stock on the ith day.
 *
 * On each day, you may decide to buy and/or sell the stock. You can only hold
 * at most one share of the stock at any time. However, you can buy it then \
 * immediately sell it on the same day.
 *
 * Find and return the maximum profit you can achieve.
 *
 * ===========
 * My Approach
 * ===========
 * We want to buy before the price goes up and sell immediately after.
 *
 * This has a time complexity of O(n) and space complexity of O(1), where n is
 * the length of the array.
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
	int maxProfit(vector<int>& prices) {
		int profit = 0;

		for (int i = 0; i < prices.size() - 1; i++) {
			if (prices[i + 1] > prices[i]) {
				profit += prices[i + 1] - prices[i];
			}
		}

		return profit;
	}
};

/**
 * Test cases
 */
int main(void) {
	Solution sol;
	vector<int> prices;

	// test case 1
	prices = { 7,1,5,3,6,4 };
	std::cout << "maxProfit(" << prices << ") = ";
	std::cout << sol.maxProfit(prices) << std::endl;

	// test case 2
	prices = { 1,2,3,4,5 };
	std::cout << "maxProfit(" << prices << ") = ";
	std::cout << sol.maxProfit(prices) << std::endl;

	// test case 3
	prices = { 7,6,4,3,1 };
	std::cout << "maxProfit(" << prices << ") = ";
	std::cout << sol.maxProfit(prices) << std::endl;

	return 0;
}