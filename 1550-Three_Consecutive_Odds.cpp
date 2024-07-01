/*******************************************************************************
 * 1550-Three_Consecutive_Odds.cpp
 * Billy.Ljm
 * 01 July 2024
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/three-consecutive-odds/
 *
 * Given an integer array arr, return true if there are three consecutive odd
 * numbers in the array. Otherwise, return false.
 *
 * ===========
 * My Approach
 * ===========
 * We just have to iterate through the array, counting the number of consecutive
 * odd numbers along the way.
 *
 * This has a time complexity of O(n) and space complexity of O(1), where n is
 * the length of the array
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
	bool threeConsecutiveOdds(vector<int>& arr) {
		int cnt = 0;

		for (int ele : arr) {
			if (ele % 2 == 1) cnt++;
			else cnt = 0;
			if (cnt > 2) return true;
		}

		return false;
	}
};

/**
 * Test cases
 */
int main(void) {
	Solution sol;
	vector<int> arr;

	// test case 1
	arr = { 2,6,4,1 };
	std::cout << "threeConsecutiveOdds(" << arr << ") = ";
	std::cout << std::boolalpha << sol.threeConsecutiveOdds(arr) << std::endl;

	// test case 2
	arr = { 1,2,34,3,4,5,7,23,12 };
	std::cout << "threeConsecutiveOdds(" << arr << ") = ";
	std::cout << std::boolalpha << sol.threeConsecutiveOdds(arr) << std::endl;

	return 0;
}