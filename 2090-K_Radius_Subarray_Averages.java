/*******************************************************************************
 * 2090-K_Radius_Subarray_Averages.java
 * Billy.Ljm
 * 20 June 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/k-radius-subarray-averages/
 *
 * You are given a 0-indexed array nums of n integers, and an integer k.
 *
 * The k-radius average for a subarray of nums centered at some index i with the
 * radius k is the average of all elements in nums between the indices i - k and
 * i + k (inclusive). If there are less than k elements before or after the
 * index i, then the k-radius average is -1.
 *
 * Build and return an array avgs of length n where avgs[i] is the k-radius
 * average for the subarray centered at index i.
 *
 * The average of x elements is the sum of the x elements divided by x, using
 * integer division. The integer division truncates toward zero, which means
 * losing its fractional part.
 *
 * ===========
 * My Approach
 * ===========
 * We'll keep a sliding window of the sum. When we move onto the next element,
 * we'll subtract the top of the window from the sum and add the bottom of the
 * window to it.
 *
 * This would have a time complexity of O(n) and space complexity of O(n), where
 * n is the size of the array.
 ******************************************************************************/

import java.util.Arrays;

class Solution {
	/**
	 * Gets the averages of elements[i-k:i+k+1] in an array
	 * @param nums array to be averaged
	 * @param k radius of each average
	 * @return array of the k-radius averages at each index, -1 if < k elements
	 */
	public int[] getAverages(int[] nums, int k) {
		int[] avg = new int[nums.length]; // k element averages
		Arrays.fill(avg, -1);
		long currSum = 0L; // sum of current window

		// trivial case
		if (k == 0) return nums;
		if (nums.length < 2 * k + 1)  return avg;

		// first k-radius average
		for (int i = 0; i < 2 * k + 1; i++) currSum += nums[i] ;
		avg[k] = (int) (currSum / (2 * k + 1));

		// remaining k-radius averages
		for (int i = k + 1; i < nums.length - k; i++) {
			currSum -= nums[i - 1 - k];
			currSum += nums[i + k];
			avg[i] = (int) (currSum / (2 * k + 1));
		}

		return avg;
	}
}

class Test {
	/**
	 * Test cases
	 */
	public static void main(String[] args) {
		Solution sol = new Solution();
		int[] nums;
		int k;

		// test case 1
		nums = new int[] {7,4,3,9,1,8,5,2,6};
		k = 3;
		System.out.println("getAverages(" + Arrays.toString(nums) + ", " + k
				+ ") = " + Arrays.toString(sol.getAverages(nums, k)));

		// test case 2
		nums = new int[] {100000};
		k = 0;
		System.out.println("getAverages(" + Arrays.toString(nums) + ", " + k
				+ ") = " + Arrays.toString(sol.getAverages(nums, k)));

		// test case 3
		nums = new int[] {8};
		k = 100000;
		System.out.println("getAverages(" + Arrays.toString(nums) + ", " + k
				+ ") = " + Arrays.toString(sol.getAverages(nums, k)));
	}
}