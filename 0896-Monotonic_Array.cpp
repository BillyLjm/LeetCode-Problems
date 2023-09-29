/*******************************************************************************
 * 0896-Monotonic_Array.cpp
 * Billy.Ljm
 * 29 September 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/monotonic-array/
 *
 * An array is monotonic if it is either monotone increasing or monotone
 * decreasing.
 *
 * An array nums is monotone increasing if for all i <= j, nums[i] <= nums[j].
 * An array nums is monotone decreasing if for all i <= j, nums[i] >= nums[j].
 *
 * Given an integer array nums, return true if the given array is monotonic, or
 * false otherwise.
 *
 * ===========
 * My Approach
 * ===========
 * We can just iterate through the array and check its monotonicity.
 *
 * This has a time complexity of O(n), and a space complexity of O(1), where n
 * is the size of the array.
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
	bool isMonotonic(vector<int>& nums) {
		bool incr = true ? nums.back() >= nums.front() : false;
		for (int i = 1; i < nums.size(); i++) {
			if (incr and nums[i] < nums[i - 1]) return false;
			else if (not incr and nums[i] > nums[i - 1]) return false;
		}
		return true;
	}
};

/**
 * Test cases
 */
int main(void) {
	Solution sol;
	vector<int> nums;

	// test case 1
	nums = { 1,2,2,3 };
	std::cout << "isMonotonic(" << nums << ") = ";
	std::cout << std::boolalpha << sol.isMonotonic(nums) << std::endl;

	// test case 2
	nums = { 6,5,4,4 };
	std::cout << "isMonotonic(" << nums << ") = ";
	std::cou << std::boolalphat << sol.isMonotonic(nums) << std::endl;

	// test case 3
	nums = { 1,3,2 };
	std::cout << "isMonotonic(" << nums << ") = ";
	std::cout << std::boolalpha << sol.isMonotonic(nums) << std::endl;

	return 0;
}