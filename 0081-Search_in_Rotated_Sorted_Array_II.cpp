/*******************************************************************************
 * 0081-Search_in_Rotated_Sorted_Array_II.cpp
 * Billy.Ljm
 * 10 August 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/search-in-rotated-sorted-array-ii/
 *
 * There is an integer array nums sorted in non-decreasing order (not
 * necessarily with distinct values).
 *
 * Before being passed to your function, nums is rotated at an unknown pivot
 * index k (0 <= k < nums.length) such that the resulting array is
 * [nums[k], nums[k+1], ..., nums[n-1], nums[0], nums[1], ..., nums[k-1]].
 * For example, [0,1,2,4,4,4,5,6,6,7] might be rotated at pivot index 5 and
 * become [4,5,6,6,7,0,1,2,4,4].
 *
 * Given the array nums after the rotation and an integer target, return true if
 * target is in nums, or false if it is not in nums.
 *
 * You must decrease the overall operation steps as much as possible.
 *
 * ===========
 * My Approach
 * ===========
 * We'll us a modified binary search algorithm. We break the array into two
 * halves, one of which will be sorted and the other not sorted due to the
 * rotation. We'll check if the target is in the sorted half, otherwise its
 * in the other half. This continues until only 1 or 2 elements are left.
 *
 * Since we have duplicate values, we can only just decrement the binary search
 * range by one whenever our start, end or mid values are equal.
 *
 * This has a time complexity of O(n), and a space complexity of  O(1), where n
 * is the length of the array.
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
	for (int i = 0; i < v.size(); i++) {
		os << v[i] << ",";
	}
	os << "\b]";
	return os;
}

/**
 * Solution
 */
class Solution {
public:
	bool search(vector<int>& nums, int target) {
		int start = 0, end = nums.size() - 1, mid;

		// binary search
		while (end - start > 1) {
			mid = start + (end - start) / 2;
			// ignore duplicate values
			if (nums[mid] == nums[start]) start++;
			else if (nums[mid] == nums[end]) end--;
			// first half is sorted
			else if (nums[mid] > nums[start]) {
				if (target >= nums[start] and target <= nums[mid]) end = mid;
				else start = mid;
			}
			// second half is sorted
			else { 
				if (target >= nums[mid] and target <= nums[end]) start = mid;
				else end = mid;
			}
		}

		// check last few elements
		if (target == nums[start]) return true;
		else if (target == nums[end]) return true;
		else return false;
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
	nums = { 2,5,6,0,0,1,2 };
	target = 0;
	std::cout << "search(" << nums << "," << target << ") = ";
	std::cout << std::boolalpha << sol.search(nums, target) << std::endl;

	// test case 2
	nums = { 2,5,6,0,0,1,2 };
	target = 3;
	std::cout << "search(" << nums << "," << target << ") = ";
	std::cout << std::boolalpha << sol.search(nums, target) << std::endl;

	return 0;
}