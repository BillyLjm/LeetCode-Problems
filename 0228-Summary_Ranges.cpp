/*******************************************************************************
 * 0228-Summary_Ranges.cpp
 * Billy.Ljm
 * 12 June 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/summary-ranges/
 *
 * You are given a sorted unique integer array nums.
 *
 * A range [a,b] is the set of all integers from a to b (inclusive).
 * 
 * Return the smallest sorted list of ranges that cover all the numbers in the
 * array exactly. That is, each element of nums is covered by exactly one of the
 * ranges, and there is no integer x such that x is in one of the ranges but not
 * in nums.
 *
 * Each range [a,b] in the list should be output as:
 * - "a->b" if a != b
 * - "a" if a == b
 *
 * ===========
 * My Approach
 * ===========
 * Since the input array is already sorted, we just have to iterate through the
 * array and compress any series of consecutive numbers into a range.
 *
 * This has a time complexity of O(n) and space complexity of O(n), where n is
 * the size of the array
 ******************************************************************************/

#include <iostream>
#include <vector>
#include <string>

/**
 * Solution
 */
class Solution {
public:
	/**
	 * Converts a sorted array of integers into an array of ranges
	 *
	 * @param nums sorted array of integers to convert
	 *
	 * @return array of ranges in the form ["a->b", "c", ...]
	 */
	std::vector<std::string> summaryRanges(std::vector<int>& nums) {
		// variables
		std::vector<std::string> out; // output value
		int front = -1; // front index of current range

		// edge case
		if (nums.size() == 0) return out;

		// find ranges
		for (int i = 0; i < nums.size() - 1; i++) {
			// if start of range
			if (front == -1) front = i;
			// if end of range
			if (nums[i] != nums[i + 1] - 1) {
				if (nums[front] == nums[i]) out.push_back(std::to_string(nums[i]));
				else out.push_back(std::to_string(nums[front]) + "->" +
					std::to_string(nums[i]));
				front = -1; // mark for new range
			}
		}

		// add last range
		if (front == -1) out.push_back(std::to_string(nums.back()));
		else out.push_back(std::to_string(nums[front]) + "->" +
			std::to_string(nums.back()));

		// return output
		return out;
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

	// test case 1
	nums = { 0, 1, 2, 4, 5, 7 };
	std::cout << "summaryRanges(" << nums << ") = ";
	std::cout << sol.summaryRanges(nums) << std::endl;

	// test case 2
	nums = { 0, 2, 3, 4, 6, 8, 9 };
	std::cout << "summaryRanges(" << nums << ") = ";
	std::cout << sol.summaryRanges(nums) << std::endl;

	return 0;
}