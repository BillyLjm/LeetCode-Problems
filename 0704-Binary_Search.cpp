/*******************************************************************************
 * 0704-Binary_Search.cpp
 * Billy.Ljm
 * 01 Apr 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/binary-search/
 * Given an array of integers nums which is sorted in ascending order, and an
 * integer target, write a function to search target in nums. If target exists,
 * then return its index. Otherwise, return -1. You must write an algorithm with
 * O(log n) runtime complexity.
 *
 * ===========
 * My Approach
 * ===========
 * Yup, its textbook binary search.
 *
 * It has a time complexity of O(log n) and a space complexity of O(1), where n
 * is the length of the array being searched
 ******************************************************************************/

#include <iostream>
#include <vector>

class Solution {
public:
	/**
	 * Binary search algorithm
	 *
	 * @param nums array of integers to search in, sorted in ascending order
	 * @param target integer to search for
	 *
	 * @return index of target in nums, or -1 if target is not in nums
	 */
	int search(std::vector<int>& nums, int target) {
		// search range indices
		size_t min = 0;
		size_t max = nums.size() - 1;
		size_t mid;

		// binary search
		while (max - min > 1) {
			mid = (min + max) / 2;
			if (nums[mid] > target) {
				max = mid;
			}
			else if (nums[mid] < target) {
				min = mid;
			}
			else { // nums[mid] == target
				return int(mid);
			}
		}

		// check last indices
		if (nums[min] == target) {
			return int(min);
		}
		else if (nums[max] == target) {
			return int(max);
		}
		else {
			return -1;
		}
	}
};

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
 * Test cases
 */
int main(void) {
	Solution sol;
	std::vector<int> nums;
	int target;

	// test case 1
	nums = { -1,0,3,5,9,12 };
	target = 9;
	std::cout << "search(" << nums << ", " << target << ") = "
		<< sol.search(nums, target) << std::endl;

	// test case 2
	nums = { -1,0,3,5,9,12 };
	target = 2;
	std::cout << "search(" << nums << ", " << target << ") = "
		<< sol.search(nums, target) << std::endl;

	return 0;
}