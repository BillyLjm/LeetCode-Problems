/*******************************************************************************
 * 0995-Minimum_Number_of_K_Consecutive_Bit_Flips.cpp
 * Billy.Ljm
 * 24 June 2024
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/minimum-number-of-k-consecutive-bit-flips/
 *
 * You are given a binary array nums and an integer k.
 *
 * A k-bit flip is choosing a subarray of length k from nums and simultaneously
 * changing every 0 in the subarray to 1, and every 1 in the subarray to 0.
 *
 * Return the minimum number of k-bit flips required so that there is no 0 in
 * the array. If it is not possible, return -1.
 *
 * A subarray is a contiguous part of an array.
 *
 * ===========
 * My Approach
 * ===========
 * The solution is straightforward. There is only one subarray containing the
 * left-most element and its value dictates if we have to flip that subarray.
 * This repeats as we traverse the array from left to right, trying to set the
 * next left-most element to 1. To do the bitflip efficiently, we use a queue
 * to track how many bitflips are applied on the current bit.
 *
 * This has a time complexity of O(n) and space complexity of O(n), where n is
 * the length of the binary array given.
 ******************************************************************************/

#include <iostream>
#include <vector>
#include <queue>

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
	int minKBitFlips(vector<int>& nums, int k) {
		int nflips = 0;
		queue<int> pos_flips;

		for (int i = 0; i < nums.size(); i++) {
			// count number of bit flips already enacted
			while (not pos_flips.empty() and i >= pos_flips.front() + k) {
				pos_flips.pop();
			}
			// if bitflip required
			if ((nums[i] == 0 and pos_flips.size() % 2 == 0) or
				(nums[i] == 1 and pos_flips.size() % 2 == 1)) {
				if (i <= nums.size() - k) { // not at end, bitflip
					nflips++;
					pos_flips.push(i);
				}
				else { // at end, can't bitflip
					return -1;
				}
			}
		}

		// all bits are 1's return
		return nflips;
	}
};

/**
 * Test cases
 */
int main(void) {
	Solution sol;
	int k;
	vector<int> nums;

	// test case 1
	k = 1;
	nums = { 0,1,0 };
	std::cout << "minKBitFlips(" << nums << ", " << k << ") = ";
	std::cout << sol.minKBitFlips(nums, k) << std::endl;

	// test case 2
	k = 2;
	nums = { 1,1,0 };
	std::cout << "minKBitFlips(" << nums << ", " << k << ") = ";
	std::cout << sol.minKBitFlips(nums, k) << std::endl;

	// test case 3
	k = 3;
	nums = { 0,0,0,1,0,1,1,0 };
	std::cout << "minKBitFlips(" << nums << ", " << k << ") = ";
	std::cout << sol.minKBitFlips(nums, k) << std::endl;

	return 0;
}