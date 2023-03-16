/*******************************************************************************
 * 0106-Construct_Binary_Tree_from_Inorder_and_Postorder_Traversal.cpp
 * Billy.Ljm
 * 16 Mar 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/construct-binary-tree-from-inorder-and-postorder-traversal/
 * Given two integer arrays inorder and postorder where inorder is the inorder
 * traversal of a binary tree and postorder is the postorder traversal of the
 * same tree, construct and return the binary tree.
 *
 * ===========
 * My Approach
 * ===========
 * The last node in postorder traversal is the root of the tree. We can then
 * lookup this root in inorder traversal to find the elements to the left and
 * right of the root. This can be repeated recursively to find the ordering of
 * the binary tree from the root to the leaves.
 *
 * At each recursion, the relevant portions of the inorder traversal will be
 * [left, root, right], and the postorder traversal will be [left, right, root].
 * We will have to calculate the indices of each portion appropriately.
 *
 * Note that the ordering can be indeterminate if there are multiple nodes with
 * identical values, since there are multiple possible roots. However, we will
 * not account for this scenario here. Assuming no duplicate nodes, we can then
 * use a hashtable for O(1) lookup of the root in the inorder traversal.
 *
 * This has a time complexity of O(n) to recurse through all nodes, and a space
 * complexity of O(n) to store the map and to recurse through an unbalanced tree.
 ******************************************************************************/

#include <iostream>
#include <vector>
#include <unordered_map>

/**
 * Definition for a binary tree node.
 */
struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode() : val(0), left(nullptr), right(nullptr) {}
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
	TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left),
		right(right) {}
};

class Solution {
public:
	/**
	 * Builds binary tree from inorder and postorder traversal
	 *
	 * @param inorder nodes of the binary tree in inorder traversal
	 * @param postorder nodes of the binary tree in postorder traversal
	 *
	 * @return root of the corresponding binary tree
	 */
	TreeNode* buildTree(std::vector<int>& inorder, std::vector<int>& postorder) {
		// build hashmap for inorder as value->index
		std::unordered_map<int, int> inordermap (inorder.size());
		for (int i = 0; i < inorder.size(); i++) {
			inordermap[inorder[i]] = i;
		}

		return recurse(inordermap, postorder, 0, inorder.size() - 1, 0,
			postorder.size() - 1);
	}

private:
	/**
	 * Recursively builds binary tree from inorder and postorder traversal
	 *
	 * @param inorder nodes of the binary tree in inorder traversal
	 * @param postorder nodes of the binary tree in postorder traversal
	 * @param mini index of the first node in the inorder traversal
	 * @param maxi index of the last node in the inorder traversal
	 * @param minp index of the first node in the postorder traversal
	 * @param maxp index of the last node in the postorder traversal
	 *
	 * @return root of the corresponding binary tree
	 */
	TreeNode* recurse(std::unordered_map<int, int>& inorder,
		std::vector<int>& postorder, int mini, int maxi, int minp,
		int maxp) {

		// trisect the ranges
		int rootval = postorder[maxp];
		int midi = inorder[rootval];
		maxp--;
		int midp = maxp - (maxi - midi);

		// construct binary tree
		if (maxi - mini <= 0) { // if at leaf
			return new TreeNode(rootval);
		}
		else if (maxi - midi <= 0) { // if no right subtree
			return new TreeNode(rootval,
				recurse(inorder, postorder, mini, midi - 1, minp, midp), nullptr
			);
		}
		else if (midi - mini <= 0) { // if no left subtree
			return new TreeNode(rootval, nullptr,
				recurse(inorder, postorder, midi + 1, maxi, midp + 1, maxp)
			);
		}
		else { // else recurse both subtrees
			return new TreeNode(rootval,
				recurse(inorder, postorder, mini, midi - 1, minp, midp),
				recurse(inorder, postorder, midi + 1, maxi, midp + 1, maxp)
			);
		}
	}
};

/**
 * Deletes a binary tree
 *
 * @param root root of binary tree to be deleted
 */
void deleteTree(TreeNode* root) {
	if (root == nullptr) return;
	deleteTree(root->left);
	deleteTree(root->right);
	delete root;
}

/**
 * Prints a binary tree in preorder traversal
 */
void printPreorder(TreeNode* root) {
	if (root == nullptr) return;
	std::cout << root->val << " ";
	printPreorder(root->left);
	printPreorder(root->right);
}

/**
 * Prints a vector
 */
template <typename T>
std::ostream& operator<<(std::ostream& os, std::vector<T> vec) {
	for (auto i = vec.begin(); i != vec.end(); i++) {
		os << *i << " ";
	}
	return os;
}

/**
 * Test cases
 */
int main(void) {
	Solution sol;
	std::vector<int> inorder, postorder;
	TreeNode* root;

	// test case 1
	inorder = {9,3,15,20,7};
	postorder = {9,15,7,20,3};
	root = sol.buildTree(inorder, postorder);
	std::cout << "Inorder: " << inorder << std::endl;
	std::cout << "Postorder: " << postorder << std::endl;
	std::cout << "Preorder: ";
	printPreorder(root);
	std::cout << std::endl;
	deleteTree(root);

	// test case 2
	inorder = { 2,1 };
	postorder = { 2,1 };
	root = sol.buildTree(inorder, postorder);
	std::cout << "Inorder: " << inorder << std::endl;
	std::cout << "Postorder: " << postorder << std::endl;
	std::cout << "Preorder: ";
	printPreorder(root);
	deleteTree(root);
}