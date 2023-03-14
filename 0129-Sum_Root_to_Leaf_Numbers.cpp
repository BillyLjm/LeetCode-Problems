/*******************************************************************************
 * 0129-Sum_Root_to_Leaf_Numbers.cpp
 * Billy.Ljm
 * 14 Mar 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/sum-root-to-leaf-numbers/
 * You are given the root of a binary tree containing digits from 0 to 9 only.
 * Each root-to-leaf path in the tree represents a number. For example, the
 * root-to-leaf path 1 -> 2 -> 3 represents the number 123. Return the total sum
 * of all root-to-leaf numbers. Test cases are generated so that the answer will
 * fit in a 32-bit integer.
 *
 * ===========
 * My Approach
 * ===========
 * Recursively visit all the leaves in a depth-first-search manner, and sum up
 * all root-to-leaf paths.
 ******************************************************************************/

#include <iostream>

/**
 * Definition for a binary tree node.
 */
struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode() : val(0), left(nullptr), right(nullptr) {}
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
	TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:
	/**
	 * Sums up all the the root-to-leaf numbers
	 *
	 * @param root root of tree to sum numbers from
	 *
	 * @return sum of all the root-to-leaf numbers
	 */
	int sumNumbers(TreeNode* root) {
		if (root == nullptr) {
			return 0;
		}
		else {
			return recurse(root, 0);
		}
	}

private:
	/**
	 * Recurses until leaf node, and sums both left and right numbers
	 *
	 * @param root root of tree to recursively traverse
	 * @param sum sum of parent nodes
	 *
	 * @returns sum of all root-to-leaf numbers passing through root
	 */
	int recurse(TreeNode* root, int sum) {
		// sum up to current node
		sum = sum * 10 + root->val;
		// recursively sum up other nodes
		if (root->left != nullptr and root->right != nullptr) {
			return recurse(root->left, sum) + recurse(root->right, sum);
		}
		else if (root->left != nullptr) {
			return recurse(root->left, sum);
		}
		else if (root->right != nullptr) {
			return recurse(root->right, sum);
		}
		else {
			return sum;
		}
	}
};

/**
 * Test cases
 */
int main (void) {
	Solution sol;
	TreeNode* root;

	// Test Case 1
	root = new TreeNode(1, new TreeNode(2), new TreeNode(3));
	std::cout << sol.sumNumbers(root) << std::endl;
	delete root->left, root->right, root;

	// Test Case 2
	root = new TreeNode(4, new TreeNode(0),
		new TreeNode(9, new TreeNode(5), new TreeNode(1)));
	std::cout << sol.sumNumbers(root) << std::endl;
}