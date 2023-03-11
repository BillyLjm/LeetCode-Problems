/*******************************************************************************
 * 0109-Convert_Sorted_List_to_Binary_Search_Tree.cpp
 * Billy.Ljm
 * 11 Mar 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/convert-sorted-list-to-binary-search-tree/
 * Given the head of a singly linked list where elements are sorted in ascending
 * order, convert it to a height-balanced binary search tree.
 *
 * ===========
 * My Approach
 * ===========
 * We could convert the linked list to a vector, where we can easily access the
 * middle value and construct a binary search tree from there. This would also
 * only require a vector of size n, which doesn't affect the space complexity
 * scaling, though it'll increase the absolute space required.
 *
 * This would have a time complexity of O(n) and a space complexity of O(n),
 * where n is the length of the linked list.
 ******************************************************************************/

#include <iostream>
#include <vector>
#include <cmath>

/**
 * Definition for singly-linked list.
 */
struct ListNode {
	int val;
	ListNode *next;
	ListNode() : val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode *next) : val(x), next(next) {}
};

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
	 * Convert sorted linked list to height-balanced binary tree
	 *
	 * @param head head of linked list to convert
	 *
	 * @return root of converted binary tree
	 */
	TreeNode* sortedListToBST(ListNode* head) {
		// convert linked list to vector
		std::vector<int> vec = { };
		ListNode* curr = head;
		while (curr) {
			vec.push_back(curr->val);
			curr = curr->next;
		}

		// build binary search tree
		return buildSubTree(&vec, 0, vec.size());
	}

private:
	/**
	 * Recursively build subtree of height from vector
	 *
	 * @param vec pointer to vector of values, includes values not in subtree
	 * @param start starting index of subtree in vector
	 * @param end ending index of subtree in vector
	 *
	 * @return root of converted binary tree
	 **/
	TreeNode* buildSubTree(std::vector<int>* vec, size_t start, size_t end) {
		if (start >= end) {
			return nullptr;
		}

		// get middle value
		size_t mid = start + (end - start) / 2;

		// build tree
		TreeNode* root = new TreeNode(vec->at(mid));
		root->left = buildSubTree(vec, start, mid);
		root->right = buildSubTree(vec, mid + 1, end);
		return root;
	}

};

/**
 * Print operator for vectors
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
 * Print operator for trees (in-order traversal)
 */
std::ostream& operator<<(std::ostream& os, const TreeNode* root) {
	if (root == nullptr) {
		os << "NULL";
	}
	else {
		os << "[" << root->left << ",";
		os << root->val << ",";
		os << root->right << ",";
		os << "\b]";
	}
	return os;
};

/**
 * Test cases
 */
int main(void) {
	Solution sol;
	std::vector<int> list;
	ListNode* head;
	TreeNode* root;

	// test case 2
	list = { };
	head = nullptr; // construct linked list
	root = sol.sortedListToBST(head); // convert
	std::cout << list << " = " << root << std::endl;

	// test case 1
	list = { -10, -3, 0, 5, 9 };
	head = nullptr; // construct linked list
	for (int i = list.size() - 1; i >= 0; i--) {
		head = new ListNode(list[i], head);
	}
	root = sol.sortedListToBST(head); // convert
	std::cout << list << " = " << root << std::endl;
}