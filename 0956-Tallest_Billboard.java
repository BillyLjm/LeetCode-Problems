/*******************************************************************************
 * 0956-Tallest_Billboard.java
 * Billy.Ljm
 * 24 June 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/tallest-billboard/
 *
 * You are installing a billboard and want it to have the largest height. The
 * billboard will have two steel supports, one on each side. Each steel support
 * must be an equal height.
 *
 * You are given a collection of rods that can be welded together. For example,
 * if you have rods of lengths 1, 2, and 3, you can weld them together to make a
 * support of length 6.
 *
 * Return the largest possible height of your billboard installation. If you
 * cannot support the billboard, return 0.
 *
 * ===========
 * My Approach
 * ===========
 * We will add each rod one by one, considering all possibilities for adding the
 * new rod on the left, right, or neither. Since we are only interested in the
 * highest billboard, we just have to remember the tallest support for each
 * height difference in the two supports, and add additional rods to it.
 *
 * This would have a time complexity of O(n * m) and space complexity of O(m),
 * where n is the number of rods and m is the total length of all rods.
 ******************************************************************************/

import java.util.Arrays;
import java.util.HashMap;

class Solution {
	/**
	 * Finds the tallest billboard that can be supported on both ends by supports
	 * assembled from a given set of rods
	 * @param rods length of the available rods
	 * @return the tallest billboard that can be supported
	 */
	public int tallestBillboard(int[] rods) {
		// max height of billboard, if all rods used
		int maxLen = 0;
		for (int i : rods) maxLen += i;
		maxLen = maxLen / 2;

		// dp[i] = tallest billboard with difference i
		HashMap<Integer, Integer> dp = new HashMap<Integer, Integer>();
		dp.put(0, 0);

		// add each rod one by one
		for (int rod : rods) {
			HashMap<Integer, Integer> copy = new HashMap<Integer, Integer>(dp);
			for (HashMap.Entry<Integer, Integer> hash : copy.entrySet()) {
				int diff = hash.getKey();
				int height = hash.getValue();

				// add rod to higher support
				if (height + rod <= maxLen) {
					dp.put(diff + rod, Math.max(dp.getOrDefault(diff + rod, 0),
							height + rod));
				}
				// add rod to lower support, which remains lower
				if (rod <= diff) {
					dp.put(diff - rod, Math.max(dp.getOrDefault(diff - rod, 0),
							height));
				}
				// add rod to lower support, which become higher
				else if (height - diff + rod <= maxLen) {
					dp.put(rod - diff, Math.max(dp.getOrDefault(rod - diff, 0),
							height - diff + rod));
				}
			}
		}

		return dp.get(0);
	}
}

class Test {
	/**
	 * Test cases
	 */
	public static void main(String[] args) {
		Solution sol = new Solution();
		int[] rods;

		// test case 1
		rods = new int[] {1,2,3,6};
		System.out.println("tallestBillboard(" + Arrays.toString(rods) + ") = "
				+ sol.tallestBillboard(rods));

		// test case 2
		rods = new int[] {1,2,3,4,5,6};
		System.out.println("tallestBillboard(" + Arrays.toString(rods) + ") = "
				+ sol.tallestBillboard(rods));

		// test case 3
		rods = new int[] {1,2};
		System.out.println("tallestBillboard(" + Arrays.toString(rods) + ") = "
				+ sol.tallestBillboard(rods));
	}
}