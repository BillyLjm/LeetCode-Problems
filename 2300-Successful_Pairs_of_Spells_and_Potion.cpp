/*******************************************************************************
 * 2300-Successful_Pairs_of_Spells_and_Potion.cpp
 * Billy.Ljm
 * 02 Apr 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/successful-pairs-of-spells-and-potions/
 * You are given two positive integer arrays spells and potions, of length n and
 * m respectively, where spells[i] represents the strength of the ith spell and
 * potions[j] represents the strength of the jth potion.
 *
 * You are also given an integer success. A spell and potion pair is considered
 * successful if the product of their strengths is at least success.
 *
 * Return an integer array pairs of length n where pairs[i] is the number of
 * potions that will form a successful pair with the ith spell.
 *
 * ===========
 * My Approach
 * ===========
 * We'll sort both the spells and potions arrays in descending order, keeping
 * note of their original indices. Then, the spells[0] can be paired with
 * potions[:j], and spells[1] can be paired with potions[:k], where j < k.
 * Thus, we just have to iterate through spells and find the gradually
 * decreasing number of potions that can be paired with it.
 *
 * It has a time complexity of O(n log n + m log m) and a space complexity of
 * O(n) mainly due to sorting, where n is the number of spells and m is the
 * number of potions.
 ******************************************************************************/

#include <iostream>
#include <vector>
#include <algorithm>

class Solution {
public:
	/**
	 * Find the number of successful potion-spell pairs, where the strength of
	 * the potion multiplied by spell exceeds a success threshold
	 *
	 * @param spells strength of spells
	 * @param potions strength of potions
	 * @param success strength threshold for pair to be a success
	 *
	 * @return number of successful potion-spell pairs
	 */
	std::vector<int> successfulPairs(std::vector<int>& spells,
		std::vector<int>& potions, long long success) {
		// sort potions and seplls
		std::sort(potions.begin(), potions.end(), std::greater<int>());
		std::vector<std::pair<int, int>> spellss;
		for (int i = 0; i < spells.size(); i++) {
			spellss.push_back(std::make_pair(spells[i], i));
		}
		std::sort(spellss.begin(), spellss.end(),
			[](std::pair<int, int>& lhs, std::pair<int, int>& rhs) -> bool {
				return lhs.first > rhs.first;
			});

		// count number of pairs
		std::vector<int> pairs(spells.size());
		size_t crawler = potions.size() - 1;
		for (std::pair<int, int> spell : spellss) {
			while (1LL * spell.first * potions[crawler] < success
				and crawler > 0) {
				crawler--;
			}
			if (crawler > 0) {
				pairs[spell.second] = crawler + 1;
			}
			else {
				pairs[spell.second] = 1LL * spell.first * potions[0] >= success;
			}
		}

		return pairs;
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
	std::vector<int> spells, potions;
	long long success;

	// test case 1
	spells = { 5,1,3 };
	potions = { 1,2,3,4,5 };
	success = 7;
	std::cout << "successfulPairs(" << spells << ", " << potions << ", " <<
		success << ") = " << sol.successfulPairs(spells, potions, success)
		<< std::endl;

	// test case 2
	spells = { 3,1,2 };
	potions = { 8,5,8 };
	success = 16;
	std::cout << "successfulPairs(" << spells << ", " << potions << ", " <<
		success << ") = " << sol.successfulPairs(spells, potions, success)
		<< std::endl;

	return 0;
}