/*******************************************************************************
 * 0530-Minimum_Absolute_Difference_in_BST.java
 * Billy.Ljm
 * 14 June 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/minimum-absolute-difference-in-bst/
 *
 * Given the root of a Binary Search Tree (BST), return the minimum absolute
 * difference between the values of any two different nodes in the tree.
 *
 * ===========
 * My Approach
 * ===========
 * Since we are given a binary search tree, in-order traversal would yield the
 * nodes in ascending order. We can then simply find the difference b/w adjacent
 * nodes and remember the minimum absolute difference.
 *
 * This would have a time complexity of O(n) and space complexity of O(1), where
 * n is the number of nodes in the tree
 ******************************************************************************/

import java.util.Arrays;
import java.util.Queue;
import java.util.LinkedList;

/**
 * Definition for a binary tree node.
 */
class TreeNode {
	int val;
	TreeNode left;
    TreeNode right;
    TreeNode() {}
    TreeNode(int val) { this.val = val; }
    TreeNode(int val, TreeNode left, TreeNode right) {
        this.val = val;
		this.left = left;
		this.right = right;
	}
}

class Solution {
	private int prev = Integer.MAX_VALUE; // value of previous node
	private int minDiff = Integer.MAX_VALUE; // minimum absolute difference

	/**
	 * Recursively traverse the tree in-order and update the minimum difference
	 *
	 * @param node current node
	 */
	private void recurse(TreeNode node) {
		// traverse left first
		if (node.left != null) recurse(node.left);
		// find difference w/ previous/left node
		minDiff = Math.min(minDiff, Math.abs(prev - node.val));
		// traverse current node
		prev = node.val;
		// traverse right
		if (node.right!= null) recurse(node.right);
	}

	/**
	 * Finds the minimum absolute difference between two nodes in a binary
	 * search tree
	 *
	 * @param root root of the binary search tree
	 * @return minimum absolute difference between any two nodes
	 */
	public int getMinimumDifference(TreeNode root) {
		recurse(root);
		return minDiff;
	}
}

class Test {
	/**
	 * Create binary tree from array of integers
	 */
	private static TreeNode createTree(Integer[] array) {
		TreeNode root = new TreeNode(array[0]); // root of tree

		// queue of nodes to add children to
		Queue<TreeNode> queue = new LinkedList<>();
		queue.add(root);

		// iteratively add remaining nodes
		TreeNode node = root;
		for(int i = 1; i < array.length; i++) {
			if (array[i] == null) continue;
			else if (i % 2 == 1) {
				node = queue.poll();
				node.left = new TreeNode(array[i]);
				queue.add(node.left);
			}
			else {
				if(array[i] != null) node.right = new TreeNode(array[i]);
				queue.add(node.right);
			}
		}

		return root;
	}

	/**
	 * Test cases
	 */
	public static void main(String[] args) {
		Solution sol = new Solution();
		Integer[] nodes;
		TreeNode root;

		// test case 1
		nodes = new Integer[] {4, 2, 6, 1, 3};
		root = createTree(nodes);
		System.out.println("getMinimumDifference(" + Arrays.toString(nodes) + ") = "
			+ sol.getMinimumDifference(root));

		// test case 2
		nodes = new Integer[] {1, 0, 48, null, null, 12, 49};
		root = createTree(nodes);
		System.out.println("getMinimumDifference(" + Arrays.toString(nodes) + ") = "
				+ sol.getMinimumDifference(root));
	}
}