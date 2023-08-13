/*******************************************************************************
 * 2369-Check_if_There_is_a_Valid_Parition_For_The_Array.cpp
 * Billy.Ljm
 * 13 August 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/check-if-there-is-a-valid-partition-for-the-array/
 *
 * You are given a 0-indexed integer array nums. You have to partition the array
 * into one or more contiguous subarrays.
 *
 * We call a partition of the array valid if each of the obtained subarrays
 * satisfies one of the following conditions:
 * - The subarray consists of exactly 2 equal elements. For example, the
 *   subarray [2,2] is good.
 * - The subarray consists of exactly 3 equal elements. For example, the
 *   subarray [4,4,4] is good.
 * - The subarray consists of exactly 3 consecutive increasing elements, that is,
 *   the difference between adjacent elements is 1. For example, the subarray
 *   [3,4,5] is good, but the subarray [1,3,5] is not.
 *
 * Return true if the array has at least one valid partition. Otherwise, return
 * false.
 *
 * ===========
 * My Approach
 * ===========
 * We just have to iterate through the array and greedily try to partition into
 * the specified subarrays. The only thing to note is that when encountering 3
 * equal elements, you could partition all of them into one subarray, or partition
 * it into a subarray of 2 equal elements and use the last equal element to pair
 * into the next subarray.
 *
 * This situation can result in double calculation since partitioning into 2 and
 * 3-long subarrays converges to partitioning into 3 and 2-long subarrays. Thus,
 * we can use dynamic programming to make it more efficient.
 *
 * This has a time complexity of O(n), and a space complexity of  O(n), where 
 * n is the length of the array.
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
	bool validPartition(vector<int>& nums) {
		vector<bool> dp(nums.size() + 1, false); // true if nums[:i] can be paritioned

		// base case
		dp[0] = true;
		dp[1] = false;
		dp[2] = (nums[0] == nums[1]);

		// dynamic programming
		for (int i = 3; i <= nums.size(); i++) {
			if (nums[i - 1] == nums[i - 2] and dp[i - 2]) {
				dp[i] = true;
			}
			else if (nums[i - 1] == nums[i - 2] and nums[i - 1] == nums[i - 3]
				and dp[i - 3]) {
				dp[i] = true;
			}
			else if (nums[i - 1] == nums[i - 2] + 1 and
				nums[i - 2] == nums[i - 3] + 1 and dp[i - 3]) {
				dp[i] = true;
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

	// test case 1
	nums = { 4,4,4,5,6 };
	std::cout << "validPartition(" << nums << ") = ";
	std::cout << std::boolalpha << sol.validPartition(nums) << std::endl;

	// test case 2
	nums = { 1,1,1,2 };
	std::cout << "validPartition(" << nums << ") = ";
	std::cout << std::boolalpha << sol.validPartition(nums) << std::endl;

	return 0;
}