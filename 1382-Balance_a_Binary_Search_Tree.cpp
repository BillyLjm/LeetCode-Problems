/*******************************************************************************
 * 1382-Balance_a_Binary_Search_Tree.cpp
 * Billy.Ljm
 * 26 June 2024
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/balance-a-binary-search-tree/
 *
 * Given the root of a binary search tree, return a balanced binary search tree
 * with the same node values. If there is more than one answer, return any of
 * them.
 *
 * A binary search tree is balanced if the depth of the two subtrees of every
 * node never differs by more than 1.
 *
 * ===========
 * My Approach
 * ===========
 * We can traverse through the tree inorder, to extract every element into a
 * vector in ascending order. Subsequently, we just have to create a balanced
 * binary search tree from that sorted vector.
 *
 * This has a time complexity of O(n) and space complexity of O(n), where n is
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
	/* in-order traversal of binary tree, and saving elements to given vector */
	void inOrder(TreeNode* root, vector<int>& elements) {
		if (root == nullptr) return;
		inOrder(root->left, elements);
		elements.push_back(root->val);
		inOrder(root->right, elements);
	}

	/* creates a balanced binary tree from given elements*/
	TreeNode* balancedTree(int idmin, int idmax, vector<int>& elements) {
		if (idmin > idmax) return nullptr;
		int idmid = (idmin + idmax) / 2;
		return new TreeNode(elements[idmid],
			balancedTree(idmin, idmid - 1, elements),
			balancedTree(idmid + 1, idmax, elements));
	}

public:
	TreeNode* balanceBST(TreeNode* root) {
		vector<int> elements;
		inOrder(root, elements);
		return balancedTree(0, elements.size() - 1, elements);
	}
};

/**
 * Test cases
 */
int main(void) {
	Solution sol;
	TreeNode *in, *out;
	vector<int> elements;

	// test case 1
	elements = { 1,-1,2,-1,3,-1,4,-1,-1 };
	in = BinaryTree(elements);
	out = sol.balanceBST(in);
	std::cout << "balanceBST(" << elements << ") = ";
	printTree(out);
	std::cout << std::endl;
	deleteTree(in);
	deleteTree(out);

	// test case 2
	elements = { 2,1,3 };
	in = BinaryTree(elements);
	out = sol.balanceBST(in);
	std::cout << "balanceBST(" << elements << ") = ";
	printTree(out);
	std::cout << std::endl;
	deleteTree(in);
	deleteTree(out);

	return 0;
}