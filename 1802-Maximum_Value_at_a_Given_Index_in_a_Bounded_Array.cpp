/*******************************************************************************
 * 1802-Maximum_Value_at_a_Given_Index_in_a_Bounded_Array.cpp
 * Billy.Ljm
 * 10 June 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/maximum-value-at-a-given-index-in-a-bounded-array/
 *
 * You are given three positive integers: n, index, and maxSum. You want to
 * construct an array nums (0-indexed) that satisfies the following conditions:
 *
 * - nums.length == n
 * - nums[i] is a positive integer where 0 <= i < n.
 * - abs(nums[i] - nums[i+1]) <= 1 where 0 <= i < n-1.
 * - The sum of all the elements of nums does not exceed maxSum.
 * - nums[index] is maximized.
 *
 * Return nums[index] of the constructed array.
 *
 * ===========
 * My Approach
 * ===========
 * The desired array if to have nums[index] maximised, and elements decreasing
 * by 1 for each increasing distance from index, up to 1 or the limits of the
 * array. Thus, we can calculate the maxSum based on n and index. We will then
 * binary search for the largest value that yields a sum less than maxSum.
 *
 * This has a time complexity of O(n) and space complexity of O(n), where n
 * is size of the output array
 ******************************************************************************/

#include <iostream>
#include <vector>

/**
 * Solution
 */
class Solution {
private:
	/**
	 * Gets the sum of the n-element array which has the format of
	 * [1, 1, ..., maxVal-2, maxVal-1, maxVal, maxVal-1, ..., 1, 1]
	 * where array[index] = maxVal
	 *
	 * @param n number of elements in the array
	 * @param index index of the maximum value
	 * @param maxVal maximum value
	 *
	 * @return sum of all elements in the array
	 */
	long long getSum(int n, int index, int maxVal) {
		long long tmp;
		long long summ = n; // all 1;s
		summ += maxVal - 1; // maximum value
		tmp = std::min(index, maxVal - 1); // num in left slope
		summ += tmp * (2 * (maxVal - 1) - tmp + 1) / 2; // sum of left slope
		summ -= tmp; // 1's in left slope
		tmp = std::min(n - index - 1, maxVal - 1); // num in right slope
		summ += tmp * (2 * (maxVal - 1) - tmp + 1) / 2; // sum of right slope
		summ -= tmp; // 1's in right slope
		return summ;
	}

public:
	/**
	 * Determines the maximum element of the array which satisfies the
	 * conditions specified in the problem statement.
	 *
	 * @param n number of elements in the array
	 * @param index index of the maximum value
	 * @param maxSum maximum value for the sum of all elements
	 *
	 * @return maximum element in the array
	 */
	int maxValue(int n, int index, int maxSum) {
		int mid;
		int minn = 1;
		int maxx = maxSum;

		// binary search
		while (maxx - minn > 1) {
			mid = (maxx + minn) / 2;
			if (getSum(n, index, mid) > maxSum) maxx = mid;
			else minn = mid;
		}

		// check last two values
		if (getSum(n, index, maxx) <= maxSum) return maxx;
		else return minn;
	}
};

/**
 * Test cases
 */
int main(void) {
	Solution sol;
	int n, index, maxSum;

	// test case 1
	n = 4;
	index = 2;
	maxSum = 6;
	std::cout << "maxValue(" << n << "," << index << "," << maxSum << ") = ";
	std::cout << sol.maxValue(n, index, maxSum) << std::endl;

	// test case 2
	n = 6;
	index = 1;
	maxSum = 10;
	std::cout << "maxValue(" << n << "," << index << "," << maxSum << ") = ";
	std::cout << sol.maxValue(n, index, maxSum) << std::endl;

	return 0;
}