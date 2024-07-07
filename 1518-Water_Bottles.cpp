/*******************************************************************************
 * 1518-Water_Bottles.cpp
 * Billy.Ljm
 * 07 July 2024
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/water-bottles/
 *
 * There are numBottles water bottles that are initially full of water. You can
 * exchange numExchange empty water bottles from the market with one full water
 * bottle.
 *
 * The operation of drinking a full water bottle turns it into an empty bottle.
 *
 * Given the two integers numBottles and numExchange, return the maximum number
 * of water bottles you can drink.
 *
 * ===========
 * My Approach
 * ===========
 * You can drink n*k bottles every step and exchange them for n filled bottles.
 * Repeat this until you have less than k bottles left, and just drink the rest.
 *
 * This has a time complexity of O(log_k n) and space complexity of O(1), where n
 * is numBottles and k is numExchange.
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
	int numWaterBottles(int numBottles, int numExchange) {
		int mult;
		int cnt = 0;
		while (numBottles >= numExchange) {
			mult = numBottles / numExchange;
			cnt += mult * numExchange;
			numBottles -= mult * (numExchange - 1);
		}
		return cnt + numBottles;
	}
};

/**
 * Test cases
 */
int main(void) {
	Solution sol;
	int numBottles, numExchange;

	// test case 1
	numBottles = 9;
	numExchange = 3;
	std::cout << "numWaterBottles(" << numBottles << ", " << numExchange << ") = ";
	std::cout << sol.numWaterBottles(numBottles, numExchange) << std::endl;

	// test case 2
	numBottles = 15;
	numExchange = 4;
	std::cout << "numWaterBottles(" << numBottles << ", " << numExchange << ") = ";
	std::cout << sol.numWaterBottles(numBottles, numExchange) << std::endl;

	return 0;
}