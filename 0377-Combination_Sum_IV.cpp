/*******************************************************************************
 * 0377-Combination_Sum_IV.cpp
 * Billy.Ljm
 * 09 September 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/combination-sum-iv/
 *
 * Given an array of distinct integers nums and a target integer target, return
 * the number of possible combinations that add up to target.
 *
 * The test cases are generated so that the answer can fit in a 32-bit integer.
 *
 * ===========
 * My Approach
 * ===========
 * Since target <= 1000 and is relatively small, we can use dynamic programming
 * to calculate the combinations that sum to all integers up to the target,
 * where dp[i] = dp[i - num] for each num in nums.
 *
 * This has a time complexity of O(n*m), and a space complexity of O(n), where
 * n is the target integer and m is the length of the array of integers.
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
	int combinationSum4(vector<int>& nums, int target) {
		// dynamic programming table
		vector<unsigned int> dp(target + 1, 0);
		dp[0] = 1;

		// fill up table
		for (int i = 0; i < dp.size(); i++) {
			for (int num : nums) {
				if (i - num < 0) continue;
				else dp[i] += dp[i - num];
			}
		}

		return dp.back();
	}
};

/**
 * Test cases
 */
int main(void) {
	Solution sol;
	vector<int> nums;
	int target;

	// test case 1
	nums = { 1,2,3 };
	target = 4;
	std::cout << "combinationSum4(" << nums << "," << target << ") = ";
	std::cout << sol.combinationSum4(nums, target) << std::endl;

	// test case 2
	nums = { 9 };
	target = 3;
	std::cout << "combinationSum4(" << nums << "," << target << ") = ";
	std::cout << sol.combinationSum4(nums, target) << std::endl;

	return 0;
}