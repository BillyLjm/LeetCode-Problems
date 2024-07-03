/*******************************************************************************
 * 1509-Minimum_Difference_Between_Largest_and_Smallest_Value_in_Three_Moves.cpp
 * Billy.Ljm
 * 03 July 2024
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/minimum-difference-between-largest-and-smallest-value-in-three-moves/
 *
 * You are given an integer array nums.
 *
 * In one move, you can choose one element of nums and change it to any value.
 *
 * Return the minimum difference between the largest and smallest value of nums
 * after performing at most three moves.
 *
 * ===========
 * My Approach
 * ===========
 * We can sort the array and ignore three of the largest/smallest element to
 * emulate the moves. Since we always only have 3 moves, we can just brute force
 * which elements are best to be removed.
 *
 * This has a time complexity of O(n log n) and space complexity of O(1), where
 * n is the length of the array.
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
	int minDifference(vector<int>& nums) {
		int mindiff = INT_MAX;
		if (nums.size() < 5) return 0; // edge case
		sort(nums.begin(), nums.end());
		// choose number of small elements to remove
		for (int i = 0; i < 4; i++) {
			mindiff = min(mindiff, nums[nums.size() - 4 + i] - nums[i]);
		}
		return mindiff;
	}
};

/**
 * Test cases
 */
int main(void) {
	Solution sol;
	vector<int> nums;

	// test case 1
	nums = { 5,3,2,4 };
	std::cout << "minDifference(" << nums << ") = ";
	std::cout << sol.minDifference(nums) << std::endl;

	// test case 2
	nums = { 1,5,0,10,14 };
	std::cout << "minDifference(" << nums << ") = ";
	std::cout << sol.minDifference(nums) << std::endl;

	// test case 3
	nums = { 3,100,20 };
	std::cout << "minDifference(" << nums << ") = ";
	std::cout << sol.minDifference(nums) << std::endl;

	return 0;
}