/*******************************************************************************
 * 0033-Search_in_Rotated_Sorted_Array.cpp
 * Billy.Ljm
 * 08 August 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/search-in-rotated-sorted-array/
 *
 * There is an integer array nums sorted in ascending order (with distinct values).
 *
 * Prior to being passed to your function, nums is possibly rotated at an
 * unknown pivot index k (1 <= k < nums.length) such that the resulting array is
 * [nums[k], nums[k+1], ..., nums[n-1], nums[0], nums[1], ..., nums[k-1]].
 * For example, [0,1,2,4,5,6,7] might be rotated at pivot index 3 and become
 *  [4,5,6,7,0,1,2].
 *
 * Given the array nums after the possible rotation and an integer target,
 * return the index of target if it is in nums, or -1 if it is not in nums.
 *
 * You must write an algorithm with O(log n) runtime complexity.
 *
 * ===========
 * My Approach
 * ===========
 * We'll us a modified binary search algorithm. We break the array into two
 * halves, one of which will be sorted and the other not sorted due to the
 * rotation. We'll check if the target is in the sorted half, otherwise its
 * in the other half. This continues until only 1 or 2 elements are left.
 *
 * This has a time complexity of O(log n), and a space complexity of  O(1),
 * where n is the length of the array.
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
	int search(vector<int>& nums, int target) {
		int start = 0, end = nums.size() - 1, mid;

		// binary search
		while (end - start > 1) {
			mid = start + (end - start) / 2;
			if (nums[mid] > nums[start]) { // first half is sorted
				if (target >= nums[start] and target <= nums[mid]) end = mid;
				else start = mid;
			}
			else { // second half is sorted
				if (target >= nums[mid] and target <= nums[end]) start = mid;
				else end = mid;
			}
		}

		// check last few elements
		if (target == nums[start]) return start;
		else if (target == nums[end]) return end;
		else return -1;
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
	nums = { 4,5,6,7,0,1,2 };
	target = 0;
	std::cout << "search(" << nums << "," << target << ") = ";
	std::cout << sol.search(nums, target) << std::endl;

	// test case 2
	nums = { 4,5,6,7,0,1,2 };
	target = 3;
	std::cout << "search(" << nums << "," << target << ") = ";
	std::cout << sol.search(nums, target) << std::endl;

	// test case 3
	nums = { 1 };
	target = 0;
	std::cout << "search(" << nums << "," << target << ") = ";
	std::cout << sol.search(nums, target) << std::endl;

	return 0;
}