/*******************************************************************************
 * 0101-Symmetric_Tree.cpp
 * Billy.Ljm
 * 13 Mar 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/symmetric-tree/
 * Given the root of a binary tree, check whether it is a mirror of itself
 * (i.e., symmetric around its center).
 *
 * ===========
 * My Approach
 * ===========
 * We just have to traverse the tree and compare the node suitably. No tricks.
 * This should have a time complexity of O(n), and a space complexity is
 * O(log n), where n it the number of nodes in the tree.
 ******************************************************************************/

#include <iostream>
#include <vector>
#include <queue>

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
	 * Checks if binary tree is symmetric
	 *
	 * @param root root of binary tree to check
	 *
	 * @return true if binary tree is symmetric, false otherwise
	 */
	bool isSymmetric(TreeNode* root) {
		return isMirror(root->left, root->right);
	}

private:
	/**
	 * Check if two binary trees are mirror images of each other
	 *
	 * @param root1 root of binary tree to compare against root2
	 * @param root2 root of binary tree to compare against root1
	 *
	 * @return true if both trees are mirror images, false otherwise
	 */
	bool isMirror(TreeNode* root1, TreeNode* root2) {
		// both null
		if (root1 == nullptr && root2 == nullptr) {
			return true;
		}
		// one null
		if (root1 == nullptr || root2 == nullptr) {
			return false;
		}
		// both not null
		return (root1->val == root2->val) &&
			isMirror(root1->left, root2->right) &&
			isMirror(root1->right, root2->left);
	}
};

/**
 * Create binary tree from vector
 *
 * @param vec vector to create binary tree from
 *
 * @return root of created binary tree
 */
TreeNode* createTree(std::vector<int> vec) {
	if (vec.empty()) {
		return nullptr;
	}
	TreeNode* root = new TreeNode(vec[0]);
	std::queue<TreeNode*> q;
	q.push(root);
	int i = 1;
	while (!q.empty() && i < vec.size()) {
		TreeNode* node = q.front();
		q.pop();
		if (vec[i] != -1) {
			node->left = new TreeNode(vec[i]);
			q.push(node->left);
		}
		i++;
		if (i < vec.size() && vec[i] != -1) {
			node->right = new TreeNode(vec[i]);
			q.push(node->right);
		}
		i++;
	}
	return root;
}

/**
 * Deletes a binary tree
 *
 * @param root root of the binary tree
 */
void deleteTree(TreeNode* root) {
	if (root == nullptr) {
		return;
	}
	deleteTree(root->left);
	deleteTree(root->right);
	delete root;
}

/**
 * Print function for vectors
 */
template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec) {
	os << "[";
	for (int i = 0; i < vec.size(); i++) {
		os << vec[i] << ",";
	}
	os << "\b]";
	return os;
}

/**
 * Test cases
 */
int main(void) {
	Solution sol;
	std::vector<int> vec;
	TreeNode* root;

	// test case 1
	vec = { 1, 2, 2, 3, 4, 4, 3 };
	root = createTree(vec);
	std::cout << std::boolalpha << vec << ": " << sol.isSymmetric(root)
		<< std::endl;
	deleteTree(root);

	// test case 2
	vec = { 1, 2, 2, NULL, 3, NULL, 3 };
	root = createTree(vec);
	std::cout << std::boolalpha << vec << ": " << sol.isSymmetric(root)
		<< std::endl;
	deleteTree(root);
}