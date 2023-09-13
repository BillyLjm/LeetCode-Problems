/*******************************************************************************
 * 0135-Candy.cpp
 * Billy.Ljm
 * 14 September 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/candy/
 *
 * There are n children standing in a line. Each child is assigned a rating
 * value given in the integer array ratings.
 *
 * You are giving candies to these children subjected to the following
 * requirements:
 * - Each child must have at least one candy.
 * - Children with a higher rating get more candies than their neighbors.
 *
 * Return the minimum number of candies you need to have to distribute the
 * candies to the children.
 *
 * ===========
 * My Approach
 * ===========
 * We will do two passes of the array. Iterating first from left to right to
 * enforce the requirement with respect to their left neighbours, then from
 * right to left to enforce with respect to right neighbours. There cannot be
 * any overlap between strictly increasing segments and strictly decreasing
 * segments (except of the ends), so the two passes will no overwrite each other.
 *
 * This has a time complexity of O(n), and a space complexity of O(n), where
 * n is the number of children.
 ******************************************************************************/

#include <iostream>
#include <vector>
#include <numeric>

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
	int candy(vector<int>& ratings) {
		vector<int> candies(ratings.size(), 1);

		// left to right pass
		for (int i = 1; i < candies.size(); i++) {
			if (ratings[i] > ratings[i - 1]) candies[i] = candies[i - 1] + 1;
		}
		// right to left pass
		for (int i = candies.size() - 2; i >= 0; i--) {
			if (ratings[i] > ratings[i + 1]) {
				candies[i] = max(candies[i], candies[i + 1] + 1);
			}
		}

		return accumulate(candies.begin(), candies.end(), 0);
	}
};

/**
 * Test cases
 */
int main(void) {
	Solution sol;
	vector<int> ratings;

	// test case 1
	ratings = { 1,0,2 };
	std::cout << "candy(" << ratings << ") = ";
	std::cout << sol.candy(ratings) << std::endl;

	// test case 2
	ratings = { 1,2,2 };
	std::cout << "candy(" << ratings << ") = ";
	std::cout << sol.candy(ratings) << std::endl;

	return 0;
}