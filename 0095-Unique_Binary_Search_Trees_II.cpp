/*******************************************************************************
 * 0095-Unique_Binary_Search_Trees_II.cpp
 * Billy.Ljm
 * 05 August 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/unique-binary-search-trees-ii/
 *
 * Given an integer n, return all the structurally unique BST's (binary search
 * trees), which has exactly n nodes of unique values from 1 to n. Return the
 * answer in any order.
 *
 * ===========
 * My Approach
 * ===========
 * To construct the binary tree, we have to create a root node, then append
 * a left subtree with k nodes and right subtree with n-1-k nodes to it. Thus,
 * we can generate the tree with dynamic programming, generating all trees with
 * increasing number of nodes.
 *
 * This has a time complexity of O(n*G(n)), and a space complexity of 
 * O(\sum_{k=1}^n k*G(k)), where n is the number of nodes and G(n) is the
 * Catalan number.
 ******************************************************************************/

#include <iostream>
#include <vector>

using namespace std;

/**
 * Definition for a binary tree node.
 */
struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode() : val(0), left(nullptr), right(nullptr) {}
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
	TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

/**
 * Pre-Order traversal of binary tree, printing out the node values
 */
void preorderTraversal(TreeNode* node, std::ostream& os) {
	if (node == nullptr) {
		os << "null,";
	}
	else if (node->left == nullptr && node->right == nullptr) {
		os << node->val << ",";
	}
	else {
		os << node->val << ",";
		preorderTraversal(node->left, os);
		preorderTraversal(node->right, os);
	}
}

/**
 * << operator for binary tree nodes
 */
std::ostream& operator<<(std::ostream& os, TreeNode* root) {
	os << "[";
	preorderTraversal(root, os);
	os << "\b]";
	return os;
}

/**
 * << operator for vectors
 */
template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& v) {
	os << "[";
	for (int i = 0; i < v.size(); i++) {
		os << v[i] << ",";
	}
	os << "\b]";
	return os;
}

/**
 * Solution
 */
class Solution {
private:
	/**
	 * Clones a tree, numbering nodes in preorder, starting form offset
	 *
	 * @param root root of binary tree to copy
	 * @param offset number to offset node values by
	 * @return root of copied binary tree
	 */
	TreeNode* cloneTree(TreeNode* root, int offset) {
		if (root == nullptr) return nullptr;
		else return new TreeNode(root->val + offset,
			cloneTree(root->left, offset), cloneTree(root->right, offset));
	}

public:
	/**
	 * Generates all structurally-distinct trees with n nodes
	 *
	 * @param n number of nodes in trees
	 * @return vector of all structurally-distinct trees
	 */
	vector<TreeNode*> generateTrees(int n) {
		vector<vector<TreeNode*>> dp(n + 1);

		// base case
		dp[0] = { nullptr };

		// general case
		for (int i = 1; i <= n; i++) { // total number of nodes
			for (int k = 0; k < i; k++) { // number of nodes in left subtree
				for (TreeNode* leftsubtree : dp[k]) {
					for (TreeNode* rightsubtree : dp[i - 1 - k]) {
						// LeetCode apparently wants this specific node numbering
						dp[i].push_back(new TreeNode(k + 1,
							cloneTree(leftsubtree, 0),
							cloneTree(rightsubtree, k+1)));
					}
				}
			}
		}

		// return result
		return dp[n];
	}
};

/**
 * Test cases
 */
int main(void) {
	Solution sol;
	int n;

	// test case 1
	n = 3;
	std::cout << "generateTrees(" << n << ") = ";
	std::cout << sol.generateTrees(n) << std::endl;

	// test case 2
	n = 1;
	std::cout << "generateTrees(" << n << ") = ";
	std::cout << sol.generateTrees(n) << std::endl;

	return 0;
}