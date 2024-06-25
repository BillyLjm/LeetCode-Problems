/*******************************************************************************
 * 1038-Binary_Search_Tree_to_Greater_Sum_Tree.cpp
 * Billy.Ljm
 * 25 June 2024
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/binary-search-tree-to-greater-sum-tree/
 *
 * Given the root of a Binary Search Tree (BST), convert it to a Greater Tree
 * such that every key of the original BST is changed to the original key plus
 * the sum of all keys greater than the original key in BST.
 *
 * As a reminder, a binary search tree is a tree that satisfies these constraints:
 * - The left subtree of a node contains only nodes with keys less than the
 *   node's key.
 * - The right subtree of a node contains only nodes with keys greater than the
 *   node's key.
 * - Both the left and right subtrees must also be binary search trees.
 *
 * ===========
 * My Approach
 * ===========
 * We can traverse through the tree in (reverse) inorder, summing the values
 * seen so far and editing each node's value appropriately.
 *
 * This has a time complexity of O(n) and space complexity of O(1), where n is
 * the number of nodes in the binary tree.
 ******************************************************************************/

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

/**
 * << operator for vectors
 */
template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& v) {
	os << "[";
	for (const auto elem : v) {
		os << elem << ",";
	}
	if (v.size() > 0) os << "\b";
	os << "]";
	return os;
}

/**
 * Definition for a binary tree node
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
 * Create binary tree from elements specified in level-order
 */
TreeNode* BinaryTree(vector<int>& elements) {
	queue<TreeNode*> queue;
	TreeNode* root = new TreeNode(elements[0]);
	queue.push(root);

	size_t i = 1;
	while (i < elements.size()) {
		TreeNode* current = queue.front();
		queue.pop();
		if (i < elements.size() && elements[i] != -1) {
			current->left = new TreeNode(elements[i]);
			queue.push(current->left);
		}
		i++;
		if (i < elements.size() && elements[i] != -1) {
			current->right = new TreeNode(elements[i]);
			queue.push(current->right);
		}
		i++;
	}

	return root;
}

/**
 * Print binary tree as elements specified in level-order
 */
void printTree(TreeNode* root) {
	queue<TreeNode*> queue;
	queue.push(root);
	cout << "[";
	while (!queue.empty()) {
		TreeNode* current = queue.front();
		queue.pop();
		if (current) {
			cout << current->val << ",";
			queue.push(current->left);
			queue.push(current->right);
		}
		else {
			cout << -1 << ",";
		}
	}
	cout << "\b]" << endl;
}

/**
 * Delete binary tree
 */
void deleteTree(TreeNode* root) {
	if (root == nullptr) return;
	deleteTree(root->left);
	deleteTree(root->right);
	delete root;
}

/**
 * Solution
 */
class Solution {
private:
	void recurse(TreeNode* root, int& summ) {
		if (root == nullptr) return;
		recurse(root->right, summ);
		summ += root->val;
		root->val = summ;
		recurse(root->left, summ);
	}

public:
	TreeNode* bstToGst(TreeNode* root) {
		int summ = 0;
		recurse(root, summ);
		return root;
	}
};

/**
 * Test cases
 */
int main(void) {
	Solution sol;
	TreeNode* root;
	vector<int> elements;

	// test case 1
	elements = { 4,1,6,0,2,5,7,-1,-1,-1,3,-1,-1,-1,8 };
	root = BinaryTree(elements);
	std::cout << "bstToGst(" << elements << ") = ";
	printTree(sol.bstToGst(root));
	std::cout << std::endl;
	deleteTree(root);

	// test case 2
	elements = { 0,-1,1 };
	root = BinaryTree(elements);
	std::cout << "bstToGst(" << elements << ") = ";
	printTree(sol.bstToGst(root));
	std::cout << std::endl;
	deleteTree(root);

	return 0;
}