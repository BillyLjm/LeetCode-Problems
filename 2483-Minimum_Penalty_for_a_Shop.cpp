/*******************************************************************************
 * 2483-Minimum_Penalty_for_a_Shop.cpp
 * Billy.Ljm
 * 29 August 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/minimum-penalty-for-a-shop/
 *
 * You are given the customer visit log of a shop represented by a 0-indexed
 * string customers consisting only of characters 'N' and 'Y':
 * - if the ith character is 'Y', it means that customers come at the ith hour
 * - whereas 'N' indicates that no customers come at the ith hour.
 *
 * If the shop closes at the jth hour (0 <= j <= n), the penalty is calculated
 * as follows:
 * - For every hour when the shop is open and no customers come, the penalty
 *   increases by 1.
 * - For every hour when the shop is closed and customers come, the penalty
 *   increases by 1.
 *
 * Return the earliest hour at which the shop must be closed to incur a minimum
 * penalty.
 *
 * ===========
 * My Approach
 * ===========
 * We just have to iterate through each time step and calculate the penalty if
 * the shop were to close immediately. Then, we just have to find the minimum
 * penalty among all time steps.
 *
 * This has a time complexity of O(n), and a space complexity of O(1), where n
 * is the length of the customer visit log.
 ******************************************************************************/

#include <iostream>
#include <vector>
#include <queue>

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
	int bestClosingTime(string customers) {
		int currpenalty = 0,  minpenalty = 0, mintime = 0;
		for (int i = 0; i < customers.size(); i++) {
			// calculate penalty
			if (customers[i] == 'N') currpenalty++;
			else currpenalty--;
			// remember min penalty
			if (currpenalty < minpenalty) {
				minpenalty = currpenalty;
				mintime = i + 1;
			}
		}

		return mintime;
	}
};

/**
 * Test cases
 */
int main(void) {
	Solution sol;
	string customers;

	// test case 1
	customers = "YYNY";
	std::cout << "bestClosingTime(" << customers << ") = ";
	std::cout << sol.bestClosingTime(customers) << std::endl;

	// test case 2
	customers = "NNNNN";
	std::cout << "bestClosingTime(" << customers << ") = ";
	std::cout << sol.bestClosingTime(customers) << std::endl;

	// test case 3
	customers = "YYYY";
	std::cout << "bestClosingTime(" << customers << ") = ";
	std::cout << sol.bestClosingTime(customers) << std::endl;

	return 0;
}