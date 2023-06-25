/*******************************************************************************
 * 1575-Count_All_Possible_Routes.java
 * Billy.Ljm
 * 25 June 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/count-all-possible-routes/
 *
 * You are given an array of distinct positive integers locations where
 * locations[i] represents the position of city i. You are also given integers
 * start, finish and fuel representing the starting city, ending city, and the
 * initial amount of fuel you have, respectively.
 *
 * At each step, if you are at city i, you can pick any city j such that j != i
 * and 0 <= j < locations.length and move to city j. Moving from city i to
 * city j reduces the amount of fuel you have by |locations[i] - locations[j]|.
 * Please notice that |x| denotes the absolute value of x.
 *
 * Notice that fuel cannot become negative at any point in time, and that you
 * are allowed to visit any city more than once (including start and finish).
 *
 * Return the count of all possible routes from start to finish. Since the
 * answer may be too large, return it modulo 10^9 + 7.
 *
 * ===========
 * My Approach
 * ===========
 * We will calculate the routes recursively, since the number of routes from i
 * to j is the number from k to j minus the fuel cost of travelling from i to k.
 * To make it more efficiently, we will use memoisation to avoid repeating whole
 * recursive call chains.
 *
 * This would have a time complexity of O(n * fuel) and space complexity of
 * O(n * fuel), where n is the number of locations and fuel is the fuel available.
 ******************************************************************************/

import java.util.Arrays;

class Solution {
	int modval = 1000000007; // value to mod
	int[][] memo; // memoisation[city][fuel]

	// pass by reference
	int finish; // finish location
	int[] locations; // locations

	/**
	 * Recrusively explores all routes
	 * @param start location to start at
	 * @param fuel amount of fuel available
	 */
	private int recurse(int start, int fuel) {
		// no fuel
		if (fuel < 0) return 0;

		// memoised
		else if (memo[start][fuel] != -1) {
			return memo[start][fuel];
		}

		// calculate number of routes
		else {
			int nroutes = 0;
			if (start == finish) nroutes++; // route w/o travelling
			for (int i = 0; i < locations.length; i++) { // recurse
				if (start == i) continue; // skip
				nroutes = (nroutes + recurse(i, fuel -
						Math.abs(locations[start] - locations[i]))) % modval;
			}
			memo[start][fuel] = nroutes; // memoise
			return nroutes;
		}
	}

	/**
	 * Counts the number of routes from start to finish with the given fuel.
	 * @param locations locations[i] - locations[j] = fuel cost of travelling
	 *                     from location i to j
	 * @param start location to start at
	 * @param finish location to end at
	 * @param fuel amount of fuel available
	 * @return number of routes from start to finish with the given fuel
	 */
	public int countRoutes(int[] locations, int start, int finish, int fuel) {
		// pass by reference
		this.locations = locations;
		this.finish = finish;

		// memoisation
		memo = new int[locations.length][fuel + 1]; // memoisation[city][fuel]
		for (int[] row : memo) Arrays.fill(row, -1); // fill with -1

		// recurse
		return recurse(start, fuel);
	}
}

class Test {
	/**
	 * Test cases
	 */
	public static void main(String[] args) {
		Solution sol = new Solution();
		int[] locations;
		int start, finish, fuel;

		// test case 1
		locations = new int[] {2,3,6,8,4};
		start = 1;
		finish = 3;
		fuel = 5;
		System.out.println("countRoutes(" + Arrays.toString(locations) + ", "
				+ start + ", " + finish + ", " + fuel + ") = "
				+ sol.countRoutes(locations, start, finish, fuel));

		// test case 2
		locations = new int[] {4,3,1};
		start = 1;
		finish = 0;
		fuel = 6;
		System.out.println("countRoutes(" + Arrays.toString(locations) + ", "
				+ start + ", " + finish + ", " + fuel + ") = "
				+ sol.countRoutes(locations, start, finish, fuel));

		// test case 3
		locations = new int[] {5,2,1};
		start = 0;
		finish = 2;
		fuel = 3;
		System.out.println("countRoutes(" + Arrays.toString(locations) + ", "
				+ start + ", " + finish + ", " + fuel + ") = "
				+ sol.countRoutes(locations, start, finish, fuel));
	}
}