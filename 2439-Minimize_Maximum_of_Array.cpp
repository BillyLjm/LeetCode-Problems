/*******************************************************************************
 * 2439-Minimize_Maximum_of_Array.cpp
 * Billy.Ljm
 * 05 Apr 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/minimize-maximum-of-array/
 * You are given a 0-indexed array nums comprising of n non-negative integers.
 * 
 * In one operation, you must:
 * - Choose an integer i such that 1 <= i < n and nums[i] > 0.
 * - Decrease nums[i] by 1.
 * - Increase nums[i - 1] by 1.
 * 
 * Return the minimum possible value of the maximum integer of nums after
 * performing any number of operations.
 *
 * ===========
 * My Approach
 * ===========
 * In each operation, we are essentially moving 1 down an index of the array.
 * Thus, the optimal way would be to increase nums[i] until it matches/exceeds
 * the maximum of the modified nums[i+1:]. Doing this recursively would have a
 * time complexity of O(n^2) and space complexity of O(1).
 *
 * An alternative perspective is for each nums[i], we must increase nums[0:i]
 * until their maximum matches/exceeds the corresponding nums[i]. Thus, the 1's
 * will flow leftwards until it reaches the average nums[0:i+1]/(i+1) or it
 * reaches a higher preceding maximum. Similar to letting water level out,
 * freezing it, then adding a new segment of water again.
 *
 * This has a time complexity of O(n) and a space complexity of O(1), where n is
 * the length of integer array.
 ******************************************************************************/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

class Solution {
public:
	/**
	 * Finds the smallest upper bound of an integer array, given that we can
	 * subtract from nums[i] to add to nums[i-1]
	 *
	 * @param nums The integer array
	 *
	 * @return smaller upper bound of modified array
	 */
	int minimizeArrayValue(std::vector<int>& nums) {
		long long cumsum = 0LL; // cumulative sum
		int curmax = 0; // current maximum value

		for (int i = 0; i < nums.size(); i++) {
			cumsum += nums[i];
			curmax = std::max(curmax, int(std::ceil(cumsum / (i + 1.0))));
		}

		return curmax;
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
	nums = { 3,7,1,6 };
	std::cout << "minimizeArrayValue(" << nums << ") = " <<
		sol.minimizeArrayValue(nums) << std::endl;

	// test case 2
	nums = { 10,1 };
	std::cout << "minimizeArrayValue(" << nums << ") = " <<
		sol.minimizeArrayValue(nums) << std::endl;

	return 0;
}