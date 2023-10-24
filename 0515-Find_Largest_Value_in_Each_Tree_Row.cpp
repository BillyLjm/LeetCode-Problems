/*******************************************************************************
 * 0515-Find_Largest_Value_in_Each_Tree_Row.cpp
 * Billy.Ljm
 * 24 October 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/find-largest-value-in-each-tree-row/
 *
 * Given the root of a binary tree, return an array of the largest value in each
 * row of the tree (0-indexed).
 *
 * ===========
 * My Approach
 * ===========
 * We just have to iterate through every node and remember their depths to
 * recognise the largest value in each row. I'll use depth-first search.
 *
 * This has a time complexity of O(n), and space complexity of O(n), where n is
 * the number of nodes in the tree.
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
 * Create binary tree from vector of row-by-row node values
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
 * Solution
 */
class Solution {
private:
	void dfs(TreeNode* root, int depth, vector<int>& maxvals) {
		// remember max value
		if (depth + 1 > maxvals.size()) maxvals.push_back(root->val);
		else maxvals[depth] = max(maxvals[depth], root->val);
		// recurse dfs
		if (root->right != nullptr) dfs(root->right, depth + 1, maxvals);
		if (root->left != nullptr) dfs(root->left, depth + 1, maxvals);
	}

public:
	vector<int> largestValues(TreeNode* root) {
		vector<int> maxvals(0);
		if(root != nullptr) dfs(root, 0, maxvals);
		return maxvals;
	}
};

/**
 * Test cases
 */
int main(void) {
	Solution sol;
	vector<int> vals;
	TreeNode* root;

	// test case 1
	vals = { 1,3,2,5,3,-1,9 };
	root = createTree(vals);
	std::cout << "largestValues(" << vals << ") = ";
	std::cout << sol.largestValues(root) << std::endl;
	deleteTree(root);

	// test case 2
	vals = { 1,2,3 };
	root = createTree(vals);
	std::cout << "largestValues(" << vals << ") = ";
	std::cout << sol.largestValues(root) << std::endl;
	deleteTree(root);

	return 0;
}