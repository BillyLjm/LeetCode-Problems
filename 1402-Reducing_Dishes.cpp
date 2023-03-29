/*******************************************************************************
 * 1402-Reducing_Dishes.cpp
 * Billy.Ljm
 * 29 Mar 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/reducing-dishes/
 * A chef has collected data on the satisfaction level of his n dishes. Chef can
 * cook any dish in 1 unit of time. Like-time coefficient of a dish is defined
 * as the time taken to cook that dish including previous dishes multiplied by
 * its satisfaction level i.e. time[i] * satisfaction[i]. Return the maximum sum
 * of like-time coefficient that the chef can obtain after dishes preparation.
 * Dishes can be prepared in any order and the chef can discard some dishes to
 * get this maximum value.
 *
 * ===========
 * My Approach
 * ===========
 * To maximise the like-time coefficient, we want to cook dishes with higher
 * satisfaction levels at later times. Thus, we can use a greedy algorithm,
 * cooking the highest satisfaction dish at the end, and prepending gradually
 * lower satisfaction dishes before it.
 *
 * This will have a time complexity of O(n log n) and a space complexity of
 * O(log n) due to sorting, where n is the number of dishes.
 ******************************************************************************/

#include <iostream>
#include <vector>
#include <algorithm>

class Solution {
public:
	/**
	 * Finds the maximum like-time coefficient (time[i] * satisfaction[i])
	 * achievable by reordering/discarding from a set of dishes.
	 *
	 * @param satisfaction: The satisfaction of each dish
	 *
	 * @return the maximum like-time coefficient
	 */
	int maxSatisfaction(std::vector<int>& satisfaction) {
		size_t n = satisfaction.size();
		int currsat = 0; // satisfaction cooking k most-satisfying dishes
		int currcoeff = 0; // like-time coefficient of k most-satisfying dishes
		int maxcoeff = 0; // max like-time coefficient

		std::sort(satisfaction.begin(), satisfaction.end(), std::greater<int>());
		for (int i = 0; i < n; i++) {
			currsat += satisfaction[i];
			if (currsat < 0) { // short-circuit, satisfaction will only go down
				break;
			}
			currcoeff += currsat;
			if (currcoeff > maxcoeff) {
				maxcoeff = currcoeff;
			}
		}

		return maxcoeff;
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
	std::vector<int> satisfaction;

	// test case 1
	satisfaction = { -1,-8,0,5,-9 };
	std::cout << "maxSatisfaction(" << satisfaction << ") = "
		<< sol.maxSatisfaction(satisfaction) << std::endl;

	// test case 2
	satisfaction = { 4,3,2 };
	std::cout << "maxSatisfaction(" << satisfaction << ") = "
		<< sol.maxSatisfaction(satisfaction) << std::endl;

	// test case 3
	satisfaction = { -1,-4,-5 };
	std::cout << "maxSatisfaction(" << satisfaction << ") = "
		<< sol.maxSatisfaction(satisfaction) << std::endl;

	return 0;
}