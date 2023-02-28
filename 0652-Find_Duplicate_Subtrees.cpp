/*******************************************************************************
 * 652-Find_Duplicate_Subtress.cpp
 * Billy.Ljm
 * 28 Feb 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/find-duplicate-subtrees/description/
 * Given the root of a binary tree, return all duplicate subtrees. For each kind
 * of duplicate subtrees, you only need to return the root node of any one of
 * them.Two trees are duplicate if they have the same structure with the same
 * node values.
 *
 * ===========
 * My Approach
 * ===========
 * My approach is hash the subtree (i.e. structure and node values) to be able
 * to quickly compare across different locations in the parent tree. This is
 * most efficiently done while recursively traversing the tree by hashing the
 * leaves and then building up larger subtrees by hashing its combined left
 * branch, right branch, and node.
 *
 * The time complexity of this will be O(n), where n is the number of nodes in
 * the tree, assuming an O(1) hash like std::hash or std::unordered_map is used.
 * The space complexity will also be identically O(n), since n hashes have to be
 * constructed and stored.
 ******************************************************************************/

#include <iostream>
#include <vector>
#include <functional>
#include <unordered_map>
#include <string>

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

class Solution {
public:
	/**
	 * Find all duplicate subtrees in a binary tree
	 *
	 * @param root root of binary tree to be checked
	 *
	 * @return vector of the roots of all duplicate subtrees
	 */
	std::vector<TreeNode*> findDuplicateSubtrees(TreeNode* root) {
		std::unordered_map<size_t, int> map; // hash-number of occurence
		std::vector<TreeNode*> dupl; // duplicate subtrees
		recurse(root, map, dupl); // recursively traverse tree
		return dupl;
	}

private:
	/**
	 * Recursively traverse binary tree while hashing each subtree and counting
	 * each subtree's occurrence
	 *
	 * @param root root of subtree
	 * @param map hash table tracking number of occurrence of each subtree
	 * @param dupl vector of duplicate subtrees (one root node per duplicate)
	 *
	 * @return hash value of the subtree (at given root)
	 */
	size_t recurse(TreeNode* root, std::unordered_map<size_t, int>& map,
		std::vector<TreeNode*>& dupl) {

		// ignore ends of leaves
		if (root == nullptr) {
			return size_t(1);
		}

		// for branches, hash and check occurrence
		else {
			// hash; must distinguish left from right
			size_t lefthash = recurse(root->left, map, dupl);
			size_t righthash = recurse(root->right, map, dupl);
			size_t hash = std::hash<std::string>{}(std::to_string(lefthash) +
				std::to_string(righthash) + std::to_string(root->val));

			// keep track of occurrences
			if (map.count(hash) == 0) {
				map[hash] = 1;
			}
			else {
				map[hash]++;
			};

			// if second instance of duplicate, append to output
			if (map[hash] == 2) {
				dupl.push_back(root);
			}

			// return hash
			return hash;
		}
	}
};

/**
 * Print operator for trees (pre-order traversal)
 */
std::ostream& operator<<(std::ostream& os, const TreeNode* root) {
	if (root == nullptr) {
		os << "NULL";
	}
	else {
		os << "[" << root->val << ",";
		os << root->left << ",";
		os << root->right << ",";
		os << "\b]";
	}
	return os;
};

/**
 * Print operator for the 1D vector class
 */
std::ostream& operator<<(std::ostream& os, const std::vector<int> vector) {
	os << "[";
	for (size_t i = 0; i < vector.size(); i++) {
		os << vector[i] << ",";
	}
	os << "\b]";
	return os;
};
std::ostream& operator<<(std::ostream& os, const std::vector<TreeNode*> vector) {
	for (size_t i = 0; i < vector.size(); i++) {
		os << vector[i] << ",";
	}
	return os;
};

/**
 * Test Cases
 */
int main(void) {
	Solution sol;

	// test case 1
	TreeNode* root1 = new TreeNode(1,
		new TreeNode(2, new TreeNode(4), nullptr),
		new TreeNode(3,
			new TreeNode(2, new TreeNode(4), nullptr),
			nullptr
		)
	);
	std::vector<TreeNode*> dupl1 = sol.findDuplicateSubtrees(root1);
	std::cout << "tree: " << root1 << "\ndupl: " << dupl1;

	return 0;
}