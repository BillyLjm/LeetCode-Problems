/*******************************************************************************
 * 1482-Minimum_Number_of_Days_to_Make_m_Bouquets.cpp
 * Billy.Ljm
 * 19 June 2024
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/minimum-number-of-days-to-make-m-bouquets/
 *
 * You are given an integer array `bloomDay`, an integer `m` and an integer `k`.
 *
 * You want to make m bouquets. To make a bouquet, you need to use k adjacent
 * flowers from the garden.
 *
 * The garden consists of n flowers, the ith flower will bloom in the
 * bloomDay[i] and then can be used in exactly one bouquet.
 *
 * Return the minimum number of days you need to wait to be able to make m
 * bouquets from the garden. If it is impossible to make m bouquets return -1.
 *
 * ===========
 * My Approach
 * ===========
 * The numbers of flowers in bloom and thus the number of bouquets we can make
 * increases monotonically. Thus, we can just binary search to find the minimum
 * days to make m bouquets.
 *
 * This has a time complexity of O(n log m) and space complexity of O(1), where
 * n is the length of the argument `bloomDay` and m is the argument `m`
 ******************************************************************************/

#include <iostream>
#include <vector>
#include <algorithm>

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
	int minDays(vector<int>& bloomDay, int m, int k) {
		int min, max, mid; // for binary search
		int nflowers, nwreaths; // to calculate wreaths

		// see if solution possible
		if (1L * m * k > bloomDay.size()) {
			return -1;
		}

		// binary search
		min = 0;
		max = *max_element(bloomDay.begin(), bloomDay.end());
		while (max > min) {
			mid = (min + max) / 2;
			// count number of wreaths
			nflowers = 0;
			nwreaths = 0;
			for (int bloom : bloomDay) {
				if (mid >= bloom) {
					nflowers++;
					if (nflowers >= k) {
						nwreaths++;
						nflowers = 0;
					}
					if (nwreaths >= m) {
						break;
					}
				}
				else {
					nflowers = 0;
				}
			}
			// adjust binary search
			if (nwreaths < m) {
				min = mid + 1;
			}
			else {
				max = mid;
			}
		}

		return min;
	}
};

/**
 * Test cases
 */
int main(void) {
	Solution sol;
	int m, k;
	vector<int> bloomDay;

	// test case 1
	m = 3;
	k = 1;
	bloomDay = { 1,10,3,10,2 };
	std::cout << "minDays(" << bloomDay << ", " << m << ", " << k << ") = ";
	std::cout << sol.minDays(bloomDay, m, k) << std::endl;

	// test case 2
	m = 3;
	k = 2;
	bloomDay = { 1,10,3,10,2 };
	std::cout << "minDays(" << bloomDay << ", " << m << ", " << k << ") = ";
	std::cout << sol.minDays(bloomDay, m, k) << std::endl;

	// test case 3
	m = 2;
	k = 3;
	bloomDay = { 7,7,7,7,12,7,7 };
	std::cout << "minDays(" << bloomDay << ", " << m << ", " << k << ") = ";
	std::cout << sol.minDays(bloomDay, m, k) << std::endl;

	return 0;
}