/*******************************************************************************
 * 1732-Find_the_Highest_Altitude.java
 * Billy.Ljm
 * 19 June 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/find-the-highest-altitude/
 *
 * There is a biker going on a road trip. The road trip consists of n + 1 points
 * at different altitudes. The biker starts his trip on point 0 with altitude
 * equal 0.
 *
 * You are given an integer array gain of length n where gain[i] is the net gain
 * in altitude between points i and i + 1 for all (0 <= i < n). Return the
 * highest altitude of a point.
 *
 * ===========
 * My Approach
 * ===========
 * We'll just iterate through the altitude gains, summing them to get the
 * current altitude, and remember the maximum one.
 *
 * This would have a time complexity of O(n) and space complexity of O(1), where
 * n is the size of the array.
 ******************************************************************************/

import java.util.Arrays;

class Solution {
	/**
	 * Finds the maximum altitude in an array of altitude gains
	 * @param gain change in altitude between points
	 * @return maximum altitude at any point
	 */
	public int largestAltitude(int[] gain) {
		int maxAlt = 0, currAlt = 0;
		for (int diff : gain) {
			currAlt += diff;
			maxAlt = Math.max(maxAlt, currAlt);
		}
		return maxAlt;
	}
}

class Test {
	/**
	 * Test cases
	 */
	public static void main(String[] args) {
		Solution sol = new Solution();
		int[] gain;

		// test case 1
		gain = new int[] {-5,1,5,0,-7};
		System.out.println("largestAltitude(" + Arrays.toString(gain) + ") = "
				+ sol.largestAltitude(gain));

		// test case 2
		gain = new int[] {-4,-3,-2,-1,4,3,2};
		System.out.println("largestAltitude(" + Arrays.toString(gain) + ") = "
				+ sol.largestAltitude(gain));
	}
}