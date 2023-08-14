/*******************************************************************************
 * 0215-Kth_Largest_Element_in_an_Array.cpp
 * Billy.Ljm
 * 14 August 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/kth-largest-element-in-an-array/
 *
 * Given an integer array nums and an integer k, return the kth largest element
 * in the array.
 *
 * Note that it is the kth largest element in the sorted order, not the kth
 * distinct element.
 *
 * Can you solve it without sorting?
 * 
 * ===========
 * My Approach
 * ===========
 * We'll use the quickselect algorithm, which is the default algorithm for find
 * the k-th largest (or smallest element)
 *
 * This has a time complexity of O(n^2), and a space complexity of  O(n), where
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
	int findKthLargest(vector<int>& nums, int k) {
		// base case
		if (nums.size() == 1) return nums[0];

		// recursion
		else {
			// partition vector
			int pivot = nums[0];
			vector<int> less, equal, more;
			for (int num : nums) {
				if (num < pivot) less.push_back(num);
				else if (num == pivot) equal.push_back(num);
				else more.push_back(num);
			}

			// recurse in appropriate partition
			if (k <= more.size()) return findKthLargest(more, k);
			else if (k <= more.size() + equal.size()) return pivot;
			else return findKthLargest(less, k - more.size() - equal.size());
		}
	}
};

/**
 * Test cases
 */
int main(void) {
	Solution sol;
	vector<int> nums;
	int k;

	// test case 1
	nums = { 3,2,1,5,6,4 };
	k = 2;
	std::cout << "findKthLargest(" << nums << "," << k << ") = ";
	std::cout << sol.findKthLargest(nums, k) << std::endl;

	// test case 2
	nums = { 3,2,3,1,2,4,5,5,6 };
	k = 4;
	std::cout << "findKthLargest(" << nums << "," << k << ") = ";
	std::cout << sol.findKthLargest(nums, k) << std::endl;

	return 0;
}