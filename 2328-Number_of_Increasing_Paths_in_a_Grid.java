/*******************************************************************************
 * 2328-Number_of_Increasing_Paths_in_a_Grid.java
 * Billy.Ljm
 * 18 June 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/number-of-increasing-paths-in-a-grid/
 *
 * You are given an m x n integer matrix grid, where you can move from a cell to
 * any adjacent cell in all 4 directions.
 *
 * Return the number of strictly increasing paths in the grid such that you can
 * start from any cell and end at any cell. Since the answer may be very large,
 * return it modulo 10^9 + 7.
 *
 * Two paths are considered different if they do not have exactly the same
 * sequence of visited cells.
 *
 * ===========
 * My Approach
 * ===========
 * If there is a neighbouring cell with a larger value, then we can extend all
 * the paths from that neigbour by prepending the current cell. Thus, we can
 * start from the cell with the smallest value, consider all its neighbours and
 * extend the paths from there, and repeat from gradually larger values.
 *
 * We'll use a priority queue to iterate from the smallest cell to the largest.
 * And we'll use an array to remember the number of paths in visited cells.
 *
 * This would have a time complexity of O(n * m) and space complexity of O(n * m)
 * where n and m are the dimensions of the grid.
 ******************************************************************************/

import java.util.Arrays;
import java.util.Queue;
import java.util.PriorityQueue;

class Solution {
	private int modval = 1000000007; // value to modulo over

	/**
	 * Counts the number of strictly increasing paths in the grid
	 * @param grid the grid to traverse
	 * @return number of strictly increasing paths in the grid
	 */
	public int countPaths(int[][] grid) {
		int[][] npaths = new int[grid.length][grid[0].length];
		Queue<int[]> pq = new PriorityQueue<>((a, b) -> a[0] - b[0]);

		// fill priority queue, to iterate through smallest element first
		for (int i = 0; i < grid.length; i++) {
			for (int j = 0; j < grid[0].length;j++) {
				pq.add(new int[] {grid[i][j], i, j});
			}
		}

		// calculate number of paths
		int [] cur;
		while (!pq.isEmpty()) {
			cur = pq.poll();
			npaths[cur[1]][cur[2]] = 1; // path from current to current
			if (cur[1] + 1 < grid.length && cur[0] > grid[cur[1] + 1][cur[2]]) {
				npaths[cur[1]][cur[2]] = (npaths[cur[1]][cur[2]] +
						npaths[cur[1] + 1][cur[2]]) % modval;
			}
			if (cur[1] - 1 >= 0 && cur[0] > grid[cur[1] - 1][cur[2]]) {
				npaths[cur[1]][cur[2]] = (npaths[cur[1]][cur[2]] +
						npaths[cur[1] - 1][cur[2]]) % modval;
			}
			if (cur[2] + 1 < grid[0].length && cur[0] > grid[cur[1]][cur[2] + 1]) {
				npaths[cur[1]][cur[2]] = (npaths[cur[1]][cur[2]] +
						npaths[cur[1]][cur[2] + 1]) % modval;
			}
			if (cur[2] - 1 >= 0 && cur[0] > grid[cur[1]][cur[2] - 1]) {
				npaths[cur[1]][cur[2]] = (npaths[cur[1]][cur[2]] +
						npaths[cur[1]][cur[2] - 1]) % modval;
			}
		}

		// sum all paths
		int totpath = 0;
		for (int i = 0; i < grid.length; i++) {
			for (int j = 0; j < grid[0].length;j++) {
				totpath = (totpath + npaths[i][j]) % modval;
			}
		}

		return totpath;
	}
}

class Test {
	/**
	 * Test cases
	 */
	public static void main(String[] args) {
		Solution sol = new Solution();
		int[][] grid;

		// test case 1
		grid = new int[][] {{1,1},{3,4}};
		System.out.println("countPaths(" + Arrays.deepToString(grid) + ","
				+ ") = " + sol.countPaths(grid));

		// test case 2
		grid = new int[][] {{1},{2}};
		System.out.println("countPaths(" + Arrays.deepToString(grid) + ","
				+ ") = " + sol.countPaths(grid));

	}
}