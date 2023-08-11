/*******************************************************************************
 * 0518-Coin_Change_II.cpp
 * Billy.Ljm
 * 11 August 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/coin-change-ii/
 *
 * You are given an integer array coins representing coins of different
 * denominations and an integer amount representing a total amount of money.
 *
 * Return the number of combinations that make up that amount. If that amount of
 * money cannot be made up by any combination of the coins, return 0.
 *
 * You may assume that you have an infinite number of each kind of coin.
 *
 * The answer is guaranteed to fit into a signed 32-bit integer.
 *
 * ===========
 * My Approach
 * ===========
 * We'll use memoised recursion, where we find the number of combinations to
 * make up a smaller amount, then use that to find the same for a larget amount.
 * 
 * However, this can lead to double counting since making an amount of 3 with 
 * coins of 1 and 2 will lead to [1]+2 and [1+1, 2]+1, where the 2+1 is double
 * counted. Thus, to avoid this, we'll prevent the use of coins smaller than the
 * previously used coin.
 *
 * This has a time complexity of O(n*m), and a space complexity of  O(n*m), where
 * n is the total amount divided by the minimum coin and m is the number of coins
 ******************************************************************************/

#include <iostream>
#include <vector>
#include <unordered_map>

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
 * << operator for map
 */
template <typename KeyType, typename ValueType>
std::ostream& operator<<(std::ostream& os,
	const std::unordered_map<KeyType, ValueType>& myMap) {
	os << "[";
	for (const auto& pair : myMap) {
		os << pair.first << ":" << pair.second << ",";
	}
	if (myMap.size() > 0) os << "\b";
	os << "]";
	return os;
}

/**
 * Solution
 */
class Solution {
	vector<unordered_map<int, int>> memo; // memo[mincoin][amt] = num combinations

public:
	int change(int amount, vector<int>& coins) {
		memo = vector<unordered_map<int, int>>(coins.size());
		return recurse(amount, coins, 0);
	}

	int recurse(int amount, vector<int>& coins, int mincoin) {
		// base case
		if (amount < 0) return 0;
		else if (amount == 0) return 1;

		// memoised
		else if (memo[mincoin].find(amount) != memo[mincoin].end()) {
			return memo[mincoin][amount];
		}

		// recurse
		else {
			memo[mincoin][amount] = 0;
			for (int i = mincoin; i < coins.size(); i++) {
				memo[mincoin][amount] += recurse(amount - coins[i], coins, i);
			}
			return memo[mincoin][amount];
		}
	}
};

/**
 * Test cases
 */
int main(void) {
	Solution sol;
	int amount;
	vector<int> coins;

	// test case 1
	amount = 5;
	coins = { 1,2,5 };
	std::cout << "change(" << amount << "," << coins << ") = ";
	std::cout << sol.change(amount, coins) << std::endl;

	// test case 2
	amount = 3;
	coins = { 2 };
	std::cout << "change(" << amount << "," << coins << ") = ";
	std::cout << sol.change(amount, coins) << std::endl;

	// test case 3
	amount = 10;
	coins = { 10 };
	std::cout << "change(" << amount << "," << coins << ") = ";
	std::cout << sol.change(amount, coins) << std::endl;

	return 0;
}