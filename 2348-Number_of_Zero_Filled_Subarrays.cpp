/*******************************************************************************
 * 2348-Number_of_Zero_Filled_Subarrays.cpp
 * Billy.Ljm
 * 21 Mar 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/number-of-zero-filled-subarrays/
 * Given an integer array nums, return the number of subarrays filled with 0.
 * A subarray is a contiguous non-empty sequence of elements within an array.
 *
 * ===========
 * My Approach
 * ===========
 * We can iterate through the array and count the number of consecutive 0's.
 * Each consecutive block would then contain 1+2+..+n subarrrays which are all
 * zero-filled.
 *
 * This would have a time complexity of O(n) and space complexity of O(1), where
 * n is the length of the array.
 ******************************************************************************/

#include <iostream>
#include <vector>

class Solution {
public:
	/**
	 * Count number of zero-filled subarrays
	 *
	 * @param nums array of integers
	 *
	 * @return number of zero-filled subarrays in nums
	 */
	long long zeroFilledSubarray(std::vector<int>& nums) {
		long long total = 0LL;// total number of zero-filled subarrays
		long long num0 = 0LL; // number of consecutive zero's

		for (int i = 0; i < nums.size(); i++) {
			if (nums[i] == 0) {
				num0++;
			}
			else {
				total += num0 * (num0 + 1) / 2; // 1+2+..+num0 arithmetic series
				num0 = 0;
			}
		}
		total += num0 * (num0 + 1) / 2; // trailing zeros

		return total;
	}
};

/**
 * << operator for vectors
 */
template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec) {
	os << "[";
	for (int i = 0; i < vec.size(); i++) {
		os << vec[i] << ",";
	}
	os << "\b]";
	return os;
}

/**
 * Test cases
 */
int main(void) {
	Solution sol;
	std::vector<int> nums;

	// test case 1
	nums = { 1, 3, 0, 0, 2, 0, 0, 4 };
	std::cout << "zeroFilledSubarray(" << nums << "): " <<
		sol.zeroFilledSubarray(nums) << std::endl;

	// test case 2
	nums = { 0, 0, 0, 2, 0, 0 };
	std::cout << "zeroFilledSubarray(" << nums << "): " <<
		sol.zeroFilledSubarray(nums) << std::endl;

	// test case 3
	nums = { 2, 10, 2019 };
	std::cout << "zeroFilledSubarray(" << nums << "): " <<
		sol.zeroFilledSubarray(nums) << std::endl;

	return 0;
}