/*******************************************************************************
 * 0945-Minimum_Increment_to_Make_Array_Unique.cpp
 * Billy.Ljm
 * 14 June 2024
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/minimum-increment-to-make-array-unique/
 *
 * You are given an integer array nums. In one move, you can pick an index i
 * where 0 <= i < nums.length and increment nums[i] by 1.
 *
 * Return the minimum number of moves to make every value in nums unique.
 *
 * The test cases are generated so that the answer fits in a 32-bit integer.
 *
 * ===========
 * My Approach
 * ===========
 * Since we can only increment but not decrement the values, we have to start
 * from the smallest value and increment it until its unique.
 *
 * This has a time complexity of O(n log n) and space complexity of O(1), where
 * n is the size of the array.
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
	int minIncrementForUnique(vector<int>& nums) {
		sort(nums.begin(), nums.end());
		int nmoves = 0; // number of moves to return
		int maxunique = nums[0]; // max unique element so far

		// increment smallest non-unique element to smallest unique + 1
		for (int i = 1; i < nums.size(); i++) {
			if (nums[i] <= maxunique) {
				maxunique++;
				nmoves += maxunique - nums[i];
			}
			else {
				maxunique = nums[i];
			}
		}

		return nmoves;
	}
};

/**
 * Test cases
 */
int main(void) {
	Solution sol;
	vector<int> nums;

	// test case 1
	nums = { 1,2,2 };
	std::cout << "minIncrementForUnique(" << nums << ") = ";
	std::cout << sol.minIncrementForUnique(nums) << std::endl;

	// test case 2
	nums = { 3,2,1,2,1,7 };
	std::cout << "minIncrementForUnique(" << nums << ") = ";
	std::cout << sol.minIncrementForUnique(nums) << std::endl;

	return 0;
}