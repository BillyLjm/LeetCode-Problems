/*******************************************************************************
 * 0034-Find_First_and_Last_Position_of_Element_in_Sorted_Array.cpp
 * Billy.Ljm
 * 09 October 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/find-first-and-last-position-of-element-in-sorted-array/
 *
 * Given an array of integers nums sorted in non-decreasing order, find the
 * starting and ending position of a given target value.
 *
 * If target is not found in the array, return [-1, -1].
 *
 * You must write an algorithm with O(log n) runtime complexity.
 *
 * ===========
 * My Approach
 * ===========
 * We will use binary search to find each position. The difference in each
 * position will be how ties are handled during the binary search.
 *
 * This has a time complexity of O(log n), and space complexity of O(1), where
 * n is the size of the array
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
	vector<int> searchRange(vector<int>& nums, int target) {
		vector<int> out;
		int start = 0, end = nums.size() - 1, mid;

		// edge case
		if (end < 0) return { -1, -1 };

		// find start
		while (end - start > 1) {
			mid = (start + end) / 2;
			if (nums[mid] < target) start = mid;
			else end = mid;
		}
		if (nums[start] == target) out.push_back(start);
		else if (nums[end] == target) out.push_back(end);
		else out.push_back(-1);

		// find end
		start = 0, end = nums.size() - 1, mid;
		while (end - start > 1) {
			mid = (start + end) / 2;
			if (nums[mid] <= target) start = mid;
			else end = mid;
		}
		if (nums[end] == target) out.push_back(end);
		else if (nums[start] == target) out.push_back(start);
		else out.push_back(-1);

		return out;
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
	nums = { 5,7,7,8,8,10 };
	target = 8;
	std::cout << "searchRange(" << nums << "," << target << ") = ";
	std::cout << sol.searchRange(nums, target) << std::endl;

	// test case 2
	nums = { 5,7,7,8,8,10 };
	target = 6;
	std::cout << "searchRange(" << nums << "," << target << ") = ";
	std::cout << sol.searchRange(nums, target) << std::endl;

	// test case 3
	nums = { };
	target = 0;
	std::cout << "searchRange(" << nums << "," << target << ") = ";
	std::cout << sol.searchRange(nums, target) << std::endl;

	return 0;
}