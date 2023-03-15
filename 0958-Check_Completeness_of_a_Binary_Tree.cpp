/*******************************************************************************
 * 0958-Check_Completeness_of_a_Binary_Tree.cpp
 * Billy.Ljm
 * 15 Mar 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/check-completeness-of-a-binary-tree/
 * Given the root of a binary tree, determine if it is a complete binary tree.
 * In a complete binary tree, every level, except possibly the last, is
 * completely filled, and all nodes in the last level are as far left as
 * possible. It can have between 1 and 2h nodes inclusive at the last level h.
 *
 * ===========
 * My Approach
 * ===========
 * Recursively visit all the leaves from left to right, in a depth-first-search
 * manner. We then compare the height of each leaf with the leftmost leaf, and
 * with any preceding (leftwards) leaf that is 1 shorter than the leftmost one.
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
	 * Checks if binary tree is complete
	 *
	 * @param root root of tree to check
	 *
	 * @return true if binary tree is complete, false otherwise
	 */
	bool isCompleteTree(TreeNode* root) {
		int leftHeight = -1;
		bool minused = false;
		return (recurse(root, &leftHeight, &minused, 0));
	}

private:
	/**
	 * Recursively check that each node is complete
	 *
	 * @param root root of (sub)tree to check from
	 * @param leftHeight height of leftmost branch; -1 if uninitialised
	 * @param minused true if any branches to the left is already 1 shorter
	 *    than the leftmost branch
	 * @param currHeight height of current node being traversed
	 *
	 * @return true if all branches to the left are balanced, false otherwise
	 */
	bool recurse(TreeNode* root, int* leftHeight, bool* minused, int currHeight) {
		// check at leaves
		if (root == nullptr) {
			// if left height is unitialised, init
			if (*leftHeight < 0) {
				*leftHeight = currHeight;
				return true;
			}
			// if current height is one less than leftmost, flag
			else if (*leftHeight == currHeight + 1) {
				*minused = true;
				return true;
			}
			// if at max height, check if preceeding nodes were one less
			else if (*leftHeight == currHeight) {
				return (*minused == false);
			}
			// else, its not balanced
			else {
				return false;
			}
		}
		// else recurse left branch, then right branch
		else {
			return (recurse(root->left, leftHeight, minused, currHeight + 1) and
				recurse(root->right, leftHeight, minused, currHeight + 1));
		}
	}
};

/**
 * Test cases
 */
int main(void) {
	Solution sol;
	TreeNode* root;

	// Test Case 1
	root = new TreeNode(1, new TreeNode(2, new TreeNode(4), new TreeNode(5)),
		new TreeNode(3, new TreeNode(6), nullptr));
	std::cout << std::boolalpha << sol.isCompleteTree(root) << std::endl;
	delete root->left->left, root->left->right, root->right->left, root->left,
		root->right, root;

	// Test Case 2
	root = new TreeNode(1, new TreeNode(2, new TreeNode(4), new TreeNode(5)),
		new TreeNode(3, nullptr, new TreeNode(7)));
	std::cout << std::boolalpha << sol.isCompleteTree(root) << std::endl;
}