/*******************************************************************************
 * 1569-Number_of_Ways_to_Reorder_Array_to_Get_Same_BST.java
 * Billy.Ljm
 * 16 June 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/number-of-ways-to-reorder-array-to-get-same-bst/
 *
 * Given an array nums that represents a permutation of integers from 1 to n. We
 * are going to construct a binary search tree (BST) by inserting the elements
 * of nums in order into an initially empty BST. Find the number of different
 * ways to reorder nums so that the constructed BST is identical to that formed
 * from the original array nums.
 *
 * For example, given nums = [2,1,3], we will have 2 as the root, 1 as a left
 * child, and 3 as a right child. The array [2,3,1] also yields the same BST but
 * [3,2,1] yields a different BST.
 *
 * Return the number of ways to reorder nums such that the BST formed is
 * identical to the original BST formed from nums.
 *
 * Since the answer may be very large, return it modulo 10^9 + 7.
 *
 * ===========
 * My Approach
 * ===========
 * Since it is a binary tree, every node can be bisected into a left and right
 * subtree depending on it they are smaller or larger respectively. Thus, we can
 * permute the ordering across different subtrees; only ensuring that the
 * ordering within the same subtree is preserved to yield the same binary tree.
 *
 * Thus, we can recurse through each level of the binary tree, identifying the
 * left and right subtree and calculating the number of permutations across
 * the two different subtrees.
 *
 * This would have a time complexity of O(n^2) and space complexity of O(n^2),
 * where n is the size of the array.
 ******************************************************************************/

import java.util.Arrays;
import java.util.ArrayList;

class Solution {
	private int modval = 1000000007;
	int[][] triangle; // Pascal's triangle

	/**
	 * Generates Pascal's triangle up to certain depth
	 * @param depth depth of the Pascals' triangle
	 */
	private void PascalTriangle (int depth) {
		triangle = new int[depth][depth];

		// first & second layer
		triangle[0][0] = 1;
		if (depth > 1) {
			triangle[1][0] = 1;
			triangle[1][1] = 1;
		}

		// subsequent layers
		for (int i = 2; i < depth; i++) {
			triangle[i][0] = 1;
			triangle[i][i] = 1;
			for (int j = 1; j < i; j++) {
				triangle[i][j] = (triangle[i - 1][j - 1] + triangle [i - 1][j])
						% modval;
			}
		}
	}

	/**
	 * Recursively calculates the number of permutations b/w each left and right
	 * subtrees, to still yield the same binary tree
	 * @param arr array of integers to insert into binary tree, sequentially
	 * @return number of ways to permute arr to yield the same binary tree
	 */
	private int recurse(ArrayList<Integer> arr) {
		// base case, only 1 node
		if (arr.size() <= 1) return 1;

		// sort into left/right subtree
		ArrayList<Integer> left = new ArrayList<Integer>();
		ArrayList<Integer> right = new ArrayList<Integer>();
		for (int i = 1; i < arr.size(); i++) {
			if (arr.get(i) > arr.get(0)) right.add(arr.get(i));
			else left.add(arr.get(i));
		}

		// recurse other levels
		long nways = triangle[left.size() + right.size()][left.size()];
		if (left.size() != 0) nways = (nways * recurse(left)) % modval;
		if (right.size() != 0) nways = (nways * recurse(right)) % modval;

		// calculate permutations
		return (int) nways;
	}

	/**
	 * Calculates the number of ways to permute nums while still yielding the
	 * same binary tree when elements are inserted sequentially.
	 * @param nums numbers to insert into the binary tree, sequentially
	 * @return numbers of ways to permute nums to yield the same binary tree
	 */
	public int numOfWays(int[] nums) {
		PascalTriangle(nums.length); // calculate binomial coefficient

		// cast nums to ArrayList for helper function
		ArrayList<Integer> arr = new ArrayList<Integer>(nums.length);
		for (int num : nums) arr.add(num);

		return recurse(arr) - 1;
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
		nums = new int[] {2,1,3};
		System.out.println("numOfWays(" + Arrays.toString(nums) + ") = "
				+ sol.numOfWays(nums));

		// test case 2
		nums = new int[] {3,4,5,1,2};
		System.out.println("numOfWays(" + Arrays.toString(nums) + ") = "
				+ sol.numOfWays(nums));

		// test case 3
		nums = new int[] {1,2,3};
		System.out.println("numOfWays(" + Arrays.toString(nums) + ") = "
				+ sol.numOfWays(nums));
	}
}