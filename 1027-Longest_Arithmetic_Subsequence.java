/*******************************************************************************
 * 1027-Longest_Arithmetic_Subsequence.java
 * Billy.Ljm
 * 23 June 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/longest-arithmetic-subsequence/
 *
 * Given an array nums of integers, return the length of the longest arithmetic
 * subsequence in nums.
 *
 * Note that:
 * - A subsequence is an array that can be derived from another array by deleting
 *   some or no elements without changing the order of the remaining elements.
 * - A sequence seq is arithmetic if seq[i + 1] - seq[i] are all the same value
 *   (for 0 <= i < seq.length - 1).
 *
 * ===========
 * My Approach
 * ===========
 * We can try pairing each element with one before it. If there is already an
 * arithmetic subsequence with the same difference, we can extend it by one.
 * Otherwise, we will create a new subsequence. To remember the subsequences
 * ending at each element and distance, we will use an array of hashmaps.
 *
 * This would have a time complexity of O(n^2) and space complexity of O(n^2),
 * where n is the number of integers.
 ******************************************************************************/

import java.util.Arrays;
import java.util.HashMap;

class Solution {
	/**
	 * Find the length of the longest arithmetic subsequence in nums.
	 * @param nums array of integers to find arithmetic subsequences in
	 * @return length of longest arithmetic subsequence
	 */
	public int longestArithSeqLength(int[] nums) {
		// initialize array of hashmaps
		HashMap<Integer, Integer>[] dp = new HashMap[nums.length];
		for (int i = 0; i < nums.length; i++) {
			dp[i] = new HashMap<Integer, Integer>();
		}

		// initialize max length
		int max = 0;

		// iterate through each element
		for (int i = 0; i < nums.length; i++) {
			// iterate through each element before it
			for (int j = 0; j < i; j++) {
				// calculate difference
				int diff = nums[i] - nums[j];

				// get length of subsequence ending at j with difference diff
				int len = dp[j].getOrDefault(diff, 1) + 1;

				// update max length
				max = Math.max(max, len);

				// update subsequence ending at i with difference diff
				dp[i].put(diff, len);
			}
		}

		// return max length
		return max;
	}
}

class Test {
	/**
	 * Test cases
	 */
	public static void main(String[] args) {
		Solution sol = new Solution();
		int[] nums;

		// test case 1
		nums = new int[] {3,6,9,12};
		System.out.println("longestArithSeqLength(" + Arrays.toString(nums)
				+ ") = " + sol.longestArithSeqLength(nums));

		// test case 2
		nums = new int[] {9,4,7,2,10};
		System.out.println("longestArithSeqLength(" + Arrays.toString(nums)
				+ ") = " + sol.longestArithSeqLength(nums));

		// test case 3
		nums = new int[] {20,1,15,3,10,5,8};
		System.out.println("longestArithSeqLength(" + Arrays.toString(nums)
				+ ") = " + sol.longestArithSeqLength(nums));
	}
}