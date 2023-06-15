/*******************************************************************************
 * 1161-Maximum_Level_Sum_of_a_Binary_Tree.java
 * Billy.Ljm
 * 15 June 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/maximum-level-sum-of-a-binary-tree/
 *
 * Given the root of a binary tree, the level of its root is 1, the level of its
 * children is 2, and so on.
 *
 * Return the smallest level x such that the sum of all the values of nodes at
 * level x is maximal.
 *
 * ===========
 * My Approach
 * ===========
 * We'll use breadth-first search to explore the binary tree level by level,
 * stopping at each to calculate the sum of all values and remembering the
 * maximum sum.
 *
 * This would have a time complexity of O(n) and space complexity of O(b), where
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
	public int maxLevelSum(TreeNode root) {
		int maxLayer = 0; // layer with maximum sum
		long maxSum = Long.MIN_VALUE; // maximum level sum
		int currLayer = 0; // current layer
		long currSum; // current level sum
		int layerSize; // size of current layer

		// breadth-first search
		Queue<TreeNode> queue = new LinkedList<>();
		queue.add(root);
		while(!queue.isEmpty()) {
			// sum current layer
			currLayer++;
			currSum = 0L;
			layerSize = queue.size();
			for (int i = 0; i < layerSize; i++) {
				TreeNode node = queue.poll();
				currSum += node.val;
				// queue next layer
				if (node.left != null) queue.add(node.left);
				if (node.right != null) queue.add(node.right);
			}
			// remember layer with maximum sum;
			if (currSum > maxSum) {
				maxLayer = currLayer;
				maxSum = currSum;
			}
		}

		return maxLayer;
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
		nodes = new Integer[] {1, 7, 0, 7, -8, null, null};
		root = createTree(nodes);
		System.out.println("maxLevelSum(" + Arrays.toString(nodes) + ") = "
			+ sol.maxLevelSum(root));

		// test case 2
		nodes = new Integer[] {989,null,10250,98693,-89388,null,null,null,-32127};
		root = createTree(nodes);
		System.out.println("maxLevelSum(" + Arrays.toString(nodes) + ") = "
			+ sol.maxLevelSum(root));
	}
}