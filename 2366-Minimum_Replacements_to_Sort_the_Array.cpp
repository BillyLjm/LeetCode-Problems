/*******************************************************************************
 * 2366-Minimum_Replacements_to_Sort_the_Array.cpp
 * Billy.Ljm
 * 30 August 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/minimum-replacements-to-sort-the-array/
 *
 * You are given a 0-indexed integer array nums. In one operation you can
 * replace any element of the array with any two elements that sum to it.
 *
 * - For example, consider nums = [5,6,7]. In one operation, we can replace
 *   nums[1] with 2 and 4 and convert nums to [5,2,4,7].
 *
 * Return the minimum number of operations to make an array that is sorted in
 * non-decreasing order.
 *
 * ===========
 * My Approach
 * ===========
 * We will want to keep the last element, which will be the maximum element of
 * the array. Then, we have to iterate backwards through the array, enforcing
 * the non-decreasing order. If the i-th element has to be replaced, we will
 * replace it with (element[i] / n) where n is an integer, since it has the
 * highest first element while still respecting the order.
 *
 * This has a time complexity of O(n), and a space complexity of O(1), where n
 * is the length of array.
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
	long long minimumReplacement(vector<int>& nums) {
		long long nmoves = 0; // number of replacement moves
		int curr, next = nums.back(); // i-th and (i+1)th element
		int tmp; // decompose curr into curr/tmp

		// do replacements
		for (int i = nums.size() - 2; i >= 0; i--) {
			curr = nums[i];
			tmp = (curr + next - 1) / next; // round up
			nmoves += tmp - 1;
			next = curr / tmp;
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
	nums = { 3,9,3 };
	std::cout << "minimumReplacement(" << nums << ") = ";
	std::cout << sol.minimumReplacement(nums) << std::endl;

	// test case 2
	nums = { 1,2,3,4,5 };
	std::cout << "minimumReplacement(" << nums << ") = ";
	std::cout << sol.minimumReplacement(nums) << std::endl;

	return 0;
}