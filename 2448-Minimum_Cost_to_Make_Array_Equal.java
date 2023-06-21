/*******************************************************************************
 * 2448-Minimum_Cost_to_Make_Array_Equal.java
 * Billy.Ljm
 * 21 June 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/minimum-cost-to-make-array-equal/
 *
 * You are given two 0-indexed arrays nums and cost consisting each of n
 * positive integers.
 *
 * You can do the following operation any number of times:
 * - Increase or decrease any element of the array nums by 1.
 *
 * The cost of doing one operation on the ith element is cost[i].
 *
 * Return the minimum total cost such that all the elements of the array nums
 * become equal.
 *
 * ===========
 * My Approach
 * ===========
 * We need to minimise the absolute difference between the elements and the
 * unknown equal value, multiplied by the cost coefficient. This is a convex
 * function, so we can simply find the global minimum by walking down the slope.
 * Since it is a simple convex function, binary search would be the most
 * efficient (as compared to gradient descent, etc).
 *
 * This would have a time complexity of O(n log d) and space complexity of O(1),
 * where n is the size of the array and d is the difference b/w the max and min
 * elements.
 ******************************************************************************/

import java.util.Arrays;

class Solution {
	int[] nums, cost; // input to minCost()

	/**
	 * Finds the cost to make all elements in the array equal to the given value.
	 * @param val given value to make all elements equal to
	 * @return cost to make all elements equal to val
	 */
	private long cost(int val) {
		long totalCost = 0L;
		for (int i = 0; i < nums.length; i++) {
			totalCost += 1L * Math.abs(nums[i] - val) * cost[i];
		}
		return totalCost;
	}

	/**
	 * Finds the minimum cost to make all elements in the array equal.
	 * @param nums elements of the array
	 * @param cost cost[i] = cost of changing nums[i] by 1
	 * @return minimum cost to make all elements equal
	 */
	public long minCost(int[] nums, int[] cost) {
		// pass by reference
		this.nums = nums;
		this.cost = cost;

		// find max and min element
		int min = Integer.MAX_VALUE, max = Integer.MIN_VALUE;
		for (int elem : nums) {
			if (elem < min) min = elem;
			if (elem > max) max = elem;
		}

		// binary search
		int mid;
		while (max - min > 1) {
			mid = (min + max) / 2;
			if (cost(mid) < cost(mid + 1)) max = mid; // positive slope
			else min = mid; // negative slope
		}

		// return minimum cost
		return Math.min(cost(min), cost(max));
	}
}

class Test {
	/**
	 * Test cases
	 */
	public static void main(String[] args) {
		Solution sol = new Solution();
		int[] nums, cost;

		// test case 1
		nums = new int[] {1,3,5,2};
		cost = new int[] {2,3,1,14};
		System.out.println("minCost(" + Arrays.toString(nums) + ", "
				+ Arrays.toString(cost) + ") = " + sol.minCost(nums, cost));

		// test case 2
		nums = new int[] {2,2,2,2,2};
		cost = new int[] {4,2,8,1,3};
		System.out.println("minCost(" + Arrays.toString(nums) + ", "
				+ Arrays.toString(cost) + ") = " + sol.minCost(nums, cost));
	}
}