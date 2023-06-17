/*******************************************************************************
 * 1187-Make_Array_Strictly_Increasing.java
 * Billy.Ljm
 * 17 June 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/make-array-strictly-increasing/
 *
 * Given two integer arrays arr1 and arr2, return the minimum number of
 * operations (possibly zero) needed to make arr1 strictly increasing.
 *
 * In one operation, you can choose two indices 0 <= i < arr1.length and
 * 0 <= j < arr2.length and do the assignment arr1[i] = arr2[j].
 *
 * If there is no way to make arr1 strictly increasing, return -1.
 *
 * ===========
 * My Approach
 * ===========
 * At each element of arr1, we either (1) leave the element alone, or (2) replace
 * it with the smallest element in arr2 that is larger than the previous element
 * of arr1. We can then simulate all strategies recursively, with memoisation to
 * avoid repeated work.
 *
 * This would have a time complexity of O(n log n + n * m) and space complexity
 * of O(n*m) where n is the length of arr1 and m is the length of arr2.
 ******************************************************************************/

import java.util.Arrays;
import java.util.HashMap;
import java.lang.String;

class Solution {
	private int [] arr1, arr2; // input arrays, to pass to helper function
	private HashMap<String, Integer> memo; // memoise recurse()

	/**
	 * Recursively consider swap or don't swap each element of arr1
	 *
	 * @param i current element being operated on
	 * @param prev value of previous element
	 * @param i2 index of smallest element in arr2 that is larger than prev
	 * @return minimum number of operations needed to make arr1 strictly increasing
	 */
	private int recurse(int i, int prev, int i2) {
		// if arr1 increasing, return
		if (i >= arr1.length) return 0;
		// if memoised, return
		else if (memo.containsKey(i + "," + prev)) {
			return memo.get(i + "," + prev);
		}

		// find next element in arr2 that is larger than prev
		while(i2 < arr2.length && arr2[i2] <= prev) i2++;
		// if arr2 exhausted
		if (i2 >= arr2.length) {
			// return INT_MAX if arr1 not increasing
			while (i < arr1.length) {
				if (arr1[i] <= prev) {
					memo.put(i + "," + prev, -1);
					return -1;
				}
				prev = arr1[i];
				i++;
			}
			// return 0 of arr1 already increasing
			memo.put(i + "," + prev, 0);
			return 0;
		}
		// else recursively consider all options
		else {
			int nmoves;
			// if must swap
			if (arr1[i] <= prev) {
				nmoves = recurse(i + 1, arr2[i2], i2);
				if (nmoves != -1) nmoves++; // current swap move
			}
			// else consider both cases
			else {
				// recurse
				int noswap = recurse(i + 1, arr1[i], i2);
				int swap = recurse(i + 1, arr2[i2], i2);
				if (swap != -1) swap++; // current sawp move
				// handle -1 cases, answer will be saved in noswap
				if (noswap == -1 && swap == -1) nmoves = -1;
				else if (noswap == -1) nmoves = swap;
				else if (swap == -1) nmoves = noswap;
				else nmoves = Math.min(noswap, swap);
			}
			// memoise
			memo.put(i + "," + prev, nmoves);
			return nmoves;
		}
	}

	/**
	 * Finds the minimum number of replacements of elements in arr1 with that of
	 * arr2 to make arr1 strictly increasing
	 * @param arr1 array to make strictly increasing
	 * @param arr2 array of values that be used to replace elements in arr1
	 * @return minimum number of replacements to make arr1 strictly increasing
	 */
	public int makeArrayIncreasing(int[] arr1, int[] arr2) {
		Arrays.sort(arr2);
		this.arr1 = arr1;
		this.arr2 = arr2;
		this.memo = new HashMap<String, Integer>();

		return recurse(0, -1, 0);
	}
}

class Test {
	/**
	 * Test cases
	 */
	public static void main(String[] args) {
		Solution sol = new Solution();
		int[] arr1, arr2;

		// test case 1
		arr1 = new int[] {1,5,3,6,7};
		arr2 = new int[] {1,3,2,4};
		System.out.println("makeArrayIncreasing(" + Arrays.toString(arr1) + ","
				+ Arrays.toString(arr2) + ") = " + sol.makeArrayIncreasing(arr1, arr2));

		// test case 2
		arr1 = new int[] {1,5,3,6,7};
		arr2 = new int[] {4,3,1};
		System.out.println("makeArrayIncreasing(" + Arrays.toString(arr1) + ","
				+ Arrays.toString(arr2) + ") = " + sol.makeArrayIncreasing(arr1, arr2));

		// test case 3
		arr1 = new int[] {1,5,3,6,7};
		arr2 = new int[] {1,6,3,3};
		System.out.println("makeArrayIncreasing(" + Arrays.toString(arr1) + ","
				+ Arrays.toString(arr2) + ") = " + sol.makeArrayIncreasing(arr1, arr2));

	}
}