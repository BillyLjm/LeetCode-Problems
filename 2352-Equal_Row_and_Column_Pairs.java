/*******************************************************************************
 * 2352-Equal_Row_and_Column_Pairs.java
 * Billy.Ljm
 * 13 June 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/equal-row-and-column-pairs/
 *
 * Given a 0-indexed n x n integer matrix grid, return the number of pairs
 * (ri, cj) such that row ri and column cj are equal.
 *
 * A row and column pair is considered equal if they contain the same elements
 * in the same order (i.e., an equal array).
 *
 * ===========
 * My Approach
 * ===========
 * We will create a hashmap to remember the rows, by concatenating the elements
 * (separated by commas) together. Then, we just have to check if the columns is
 * identical to rows in the hashmap.
 *
 * This would have a time complexity of O(n) and space complexity of O(n), where
 * n is the number of rows/columns of the matrix.
 ******************************************************************************/

import java.util.Arrays;
import java.lang.String;
import java.util.HashMap;

class Solution {
	/**
	 * Counts the number of row/column pairs that have identical elements
	 *
	 * @param grid matrix to check row/column pairs for
	 * @return number of row/column pairs that have identical elements
	 */
	public static int equalPairs(int[][] grid) {
		int count = 0;

		// hashmap of rows
		HashMap<String, Integer> rowHash = new HashMap<>();
		for (int[] row : grid) {
			rowHash.merge(Arrays.toString(row), 1, Integer::sum);
		}

		// check columns equal to rows
		int[] col = new int[grid.length];
		for (int i = 0; i < grid.length; i++) {
			for (int j = 0; j < grid.length; j++) {
				col[j] = grid[j][i];
			}
			if (rowHash.containsKey(Arrays.toString(col))) {
				count += rowHash.get(Arrays.toString(col));
			}
		}

		return count;
	}
}

class Test {
	/**
	 * Test cases
	 */
	public static void main(String[] args) {
		int[][] grid;

		// test case 1
		grid = new int[][] {{3, 2, 1}, {1, 7, 6}, {2, 7, 7}};
		System.out.println("equalPairs(" + Arrays.deepToString(grid) + ") = "
			+ Solution.equalPairs(grid));

		// test case 2
		grid = new int[][] {{3, 1, 2, 2}, {1, 4, 4, 5}, {2, 4, 2, 2}, {2, 4, 2, 2}};
		System.out.println("equalPairs(" + Arrays.deepToString(grid) + ") = "
			+ Solution.equalPairs(grid));
	}
}