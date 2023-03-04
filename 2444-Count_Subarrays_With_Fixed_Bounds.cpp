/*******************************************************************************
 * 2444-Count_Subarrays_With_Fixed_Bounds.cpp
 * Billy.Ljm
 * 04 Mar 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/count-subarrays-with-fixed-bounds/
 * You are given an integer array `nums` and two integers `minK` and `maxK`. A
 * fixed-bound subarray of `nums` is a subarray that satisfies the following
 * conditions: 1) The minimum value in the subarray is equal to `minK`. 2) The
 * maximum value in the subarray is equal to `maxK`. Return the number of
 * fixed-bound subarrays.
 *
 * ===========
 * My Approach
 * ===========
 * We need to take note of elements that are: (1) equal to the lower bound (2)
 * equal to the upper bound (3) outside either bound. Iterating through the
 * indices of nums, we can form fixed-bound subarrays from the last (1)...(2)
 * subarrays up extended up to the current index, and extended down to the last
 * (3) index.
 *
 * This would have a time complexity of O(n), where n is the length of the
 * array, since we check every element once. And a space complexity of O(1),
 * since we only keep track of the three cases above.
 ******************************************************************************/

#include <iostream>
#include <vector>

class Solution {
public:
	/**
	 * Count the number of fixed-bound subarrays, who have elements that are
	 * bounded by minK and maxK.
	 *
	 * @param nums array to search for fixed-bound subarrays in
	 * @param minK lower bound for fixed-bound subarrays
	 * @param maxK upper bound for fixed-bound subarrays
	 *
	 * @return number of fixed-bound subarrays found
	 */
	long long countSubarrays(std::vector<int>& nums, int minK, int maxK) {
		long long ntot = 0; // total number of fixed-bound subarrays
		size_t imax = 0; // last maxK index + 1
		size_t imin = 0; // last minK index + 1
		size_t iout = 0; // last out-of-bound index

		// validate input, apparently the test cases want this behaviour
		if (minK > maxK) {
			return 0;
		}

		for (int i = 0; i < nums.size(); i++) {
			// remember last indices
			if (nums[i] == maxK) {
				imax = i + 1;
			}
			else if (nums[i] == minK) {
				imin = i + 1;
			}
			else if (nums[i] < minK || nums[i] > maxK) {
				iout = i + 1;
			}
			if (minK == maxK) { // edge case
				imin = imax;
			}

			// add number of fixed-bound subarrays up to current index
			if (imin < iout or imax < iout) {
				ntot += 0;
			}
			else if (imin < imax) {
				ntot += imin - iout;
			}
			else {
				ntot += imax - iout;
			}
		}

		return ntot;
	}
};

/**
 * Test cases
 */
int main(void) {
	Solution sol;
	std::vector <int> nums;

	// test case 1
	nums = { 1, 3, 5, 2, 7, 5 };
	std::cout << "sol.countSubarrays({ 1, 3, 5, 2, 7, 5 }, 1, 5): ";
	std::cout << sol.countSubarrays(nums, 1, 5) << std::endl;

	// test case 2
	nums = { 1, 1, 1, 1 };
	std::cout << "sol.countSubarrays({ 1, 1, 1, 1 }, 1, 1): ";
	std::cout << sol.countSubarrays(nums, 1, 1) << std::endl;
}