/*******************************************************************************
 * 1970-Last_Day_Where_You_Can_Still_Cross.java
 * Billy.Ljm
 * 30 June 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/last-day-where-you-can-still-cross/
 *
 * There is a 1-based binary matrix where 0 represents land and 1 represents
 * water. You are given integers row and col representing the number of rows and
 * columns in the matrix, respectively.
 *
 * Initially on day 0, the entire matrix is land. However, each day a new cell
 * becomes flooded with water. You are given a 1-based 2D array cells, where
 * cells[i] = [ri, ci] represents that on the ith day, the cell on the rith row
 * and cith column (1-based coordinates) will be covered with water (i.e.,
 * changed to 1).
 *
 * You want to find the last day that it is possible to walk from the top to the
 * bottom by only walking on land cells. You can start from any cell in the top
 * row and end at any cell in the bottom row. You can only travel in the four
 * cardinal directions (left, right, up, and down).
 *
 * Return the last day where it is possible to walk from the top to the bottom
 * by only walking on land cells.
 *
 * ===========
 * My Approach
 * ===========
 * Instead of ensuring that there are no land paths throughout the map, we look
 * for just one water path from left to right. To find this one water path, I'll
 * use disjoint set union for each water cell added and check if the left and
 * right are of the same set.
 *
 * This would have a time complexity of O(e log(v)) and space complexity of
 * O(e + v), where e is the number of cells to be filled with water, and v is
 * the number of cells in the map.
 ******************************************************************************/

import java.util.Arrays;

/**
 * Union-Find / Disjoint Set Union class
 */
class UnionFind	 {
	public int[] parent;
	private int[] rank;

	/**
	 * Constructor for unionFind
	 * @param n number of vertices in graph
	 */
	public UnionFind(int n) {
		parent = new int[n];
		rank = new int[n];
		for (int i = 0; i < n; i++) {
			parent[i] = i;
			rank[i] = 1;
		}
	}

	/**
	 * Find parent of node x
	 * @param x node to find parent of
	 * @return parent of node x
	 */
	public int find(int x) {
		if (parent[x] == x) return x;
		return parent[x] = find(parent[x]);
	}

	/**
	 * Union nodes x and y
	 * @param x node to union with y
	 * @param y node to union with x
	 */
	public void union(int x, int y) {
		int xRoot = find(x);
		int yRoot = find(y);
		if (xRoot == yRoot) return;
		if (rank[xRoot] < rank[yRoot]) {
			parent[xRoot] = yRoot;
		} else if (rank[xRoot] > rank[yRoot]) {
			parent[yRoot] = xRoot;
		} else {
			parent[yRoot] = xRoot;
			rank[xRoot]++;
		}
	}
}

/**
 * Solution
 */
class Solution {
	/**
	 * Finds the latest day to cross a land that gradually fills up with water
	 * @param row number of rows of land
	 * @param col number of columns of land
	 * @param cells list of (row, col) of cells to fill up with water
	 * @return latest day to cross the land
	 */
	public int latestDayToCross(int row, int col, int[][] cells) {
		UnionFind uf = new UnionFind(row * col + 2); // disjoint set union
		boolean[][] grid = new boolean[row][col]; // map of land and water
		int[][] directions = new int[][] {{0, 1}, {0, -1}, {1, 0}, {-1, 0},
				{1, 1}, {1, -1}, {-1, 1}, {-1, -1}}; // directions to move

		// connect left boundary to left cells, and similarly for right
		for (int i = 0; i < row; i++) {
			uf.union(0, i * col + 1);
			uf.union(row * col + 1, (i + 1) * col);
		}

		// add each edge / water cell
		for (int i = 0; i < cells.length; i++) {
			// current cell
			int x = cells[i][0] - 1;
			int y = cells[i][1] - 1;
			int cell = x * col + y + 1;
			// update map
			grid[x][y] = true;
			// connect all adjacent water cells
			for (int[] dir : directions) {
				// find neighbour cell
				int nx = cells[i][0] - 1 + dir[0];
				int ny = cells[i][1] - 1 + dir[1];
				int ncell = nx * col + ny + 1;
				// check if out of bounds or not water
				if (nx < 0 || nx >= row || ny < 0 || ny >= col || !grid[nx][ny]) continue;
				// connect
				else uf.union(cell, ncell);
			}
			// water bridged from left to right, return
			if(uf.find(0) == uf.find(row * col + 1)) return i;
		}

		// no water bridged from left to right, return -1
		return -1;
	}
}

/**
 * Test cases
 */
class Test {
	public static void main(String[] args) {
		Solution sol = new Solution();
		int row, col;
		int[][] cells;

		// test case 1
		row = 2;
		col = 2;
		cells = new int[][] {{1,1},{2,1},{1,2},{2,2}};
		System.out.println("latestDayToCross(" + row + ", " + col + ", "
				+ Arrays.deepToString(cells) + ") = "
				+ sol.latestDayToCross(row, col, cells));

		// test case 2
		row = 2;
		col = 2;
		cells = new int[][] {{1,1},{1,2},{2,1},{2,2}};
		System.out.println("latestDayToCross(" + row + ", " + col + ", "
				+ Arrays.deepToString(cells) + ") = "
				+ sol.latestDayToCross(row, col, cells));

		// test case 3
		row = 3;
		col = 3;
		cells = new int[][] {{1,2},{2,1},{3,3},{2,2},{1,1},{1,3},{2,3},{3,2},{3,1}};
		System.out.println("latestDayToCross(" + row + ", " + col + ", "
				+ Arrays.deepToString(cells) + ") = "
				+ sol.latestDayToCross(row, col, cells));
	}
}