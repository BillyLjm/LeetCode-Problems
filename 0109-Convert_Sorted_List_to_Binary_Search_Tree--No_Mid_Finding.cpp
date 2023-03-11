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
 * But thats kind of trivial, and I want to try something different. I want to
 * create a binary search tree from only traversing the linked list from front
 * to back, no accessing the middle. And this is what I came up with.
 *
 * We can loop through the linked list once solely to find its length. Knowing
 * this length, we can determine the structure of the resulting binary search
 * tree. Then, we just have to loop through the linked list a second time and
 * fill out the kown binary search tree from left to right.
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
		// count length of linked list
		int length = 0;
		ListNode* curr = head;
		while (curr) {
			length++;
			curr = curr->next;
		}

		// determine structure of binary search tree
		if (length == 0) {
			return nullptr;
		}
		int nlevels = int(std::log(length) / std::log(2));
		int nlast = length - (int(std::pow(2, nlevels)) - 1);

		// build binary search tree
		return buildSubTree(&head, nlevels, &nlast);
	}

private:
	/**
	 * Recursively build subtree of height from linked list at head. Modifies
	 * linked list, so keep another pointer and don't let memory overflow!
	 *
	 * @param head pointer to pointer to head of linked list
	 * @param height number of fully-filled layers of subtree
	 * @param nlast pointer to number of leaves in last partially-filled layer
	 *
	 * @return root of converted binary tree
	 **/
	TreeNode* buildSubTree(ListNode** head, int height, int* nlast) {
		// base case: add last layer of tree
		if (height == 0) {
			// terminate branch into leave if no last leaves
			if (*nlast == 0) {
				return nullptr;
			}
			// else add last leaves
			else {
				TreeNode* root = new TreeNode((*head)->val);
				*head = (*head)->next;
				*nlast -= 1;
				return root;
			}
		}

		// else, build subtrees recursively and combine
		else {
			// first left, using front nodes of linked list
			TreeNode* left = buildSubTree(head, height - 1, nlast);
			// then root
			TreeNode* root = new TreeNode((*head)->val);
			*head = (*head)->next;
			// finally right, using back nodes of linked list
			TreeNode* right = buildSubTree(head, height - 1, nlast);
			// combine
			root->left = left;
			root->right = right;
			return root;
		}
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