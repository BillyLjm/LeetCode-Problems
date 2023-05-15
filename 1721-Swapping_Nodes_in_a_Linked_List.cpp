/*******************************************************************************
 * 1721-Swapping_Nodes_in_a_Linked_List.cpp
 * Billy.Ljm
 * 15 May 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/swapping-nodes-in-a-linked-list/
 *
 * You are given the head of a linked list, and an integer k.
 *
 * Return the head of the linked list after swapping the values of the kth node
 * from the beginning and the kth node from the end (the list is 1-indexed).
 *
 * ===========
 * My Approach
 * ===========
 * We will crawl through the linked list, remembering the (k-1)th node and
 * the (-k-1)-th node. To do this, we will use two crawlers spaced a appropriate
 * number of nodes apart. Then, when one of them reaches the head or tail, the
 * other crawler will be at the desired node. We then just have to swap them.
 *
 * This has a time complexity of O(n) and space complexity of O(1), where n is
 * the length of the linked list.
 ******************************************************************************/

#include <iostream>
#include <vector>

/**
 * Definition for singly - linked list
 */
struct ListNode {
	int val;
	ListNode* next;
	ListNode() : val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode* next) : val(x), next(next) {}
};

/**
 * Solution
 */
class Solution {
public:
	/**
	 * Swaps the (k)-th and (-k)-th nodes of a linked list
	 *
	 * @param head head of the linked list to swap
	 * @param k index of the nodes to swap
	 *
	 * @return head of the swapped linked list
	 */
	ListNode* swapNodes(ListNode* head, int k) {
		ListNode* front;
		ListNode* back;
		ListNode* ptr;

		// find k-th element
		ptr = head;
		for (int i = 1; i < k; i++) {
			ptr = ptr->next;
		}

		// find (-k)-th element
		back = head;
		front = ptr;
		while (front->next != nullptr) {
			back = back->next;
			front = front->next;
		}

		// swap their values
		int tmp = ptr->val;
		ptr->val = back->val;
		back->val = tmp;

		return head;
	}
};

/**
 * Convert from vector to linked list
 *
 * @param nodes value of linked list nodes in order
 *
 * @return head of linked list
 */
ListNode* linkedlist(std::vector<int> nodes) {
	ListNode* head = nullptr;
	for (int i = nodes.size() - 1; i >= 0; i--) {
		head = new ListNode(nodes[i], head);
	}
	return head;
}

/**
 * Delete linked list
 * 
 * @param head head of linked list to be deleted
 */
void dellinkedlist(ListNode* head) {
	if (head->next == nullptr) {
		delete head;
	}
	else {
		dellinkedlist(head->next);
		delete head;
	}
}

/**
 * << operator for ListNodes's linked lisst
 */
std::ostream& operator<<(std::ostream& os, const ListNode* head) {
	if (head->next == nullptr) {
		return os << head->val;
	}
	else {
		return os << head->val << "," << head->next;
	}
}

/**
 * Test cases
 */
int main(void) {
	Solution sol;
	int k;
	ListNode* head;
	std::vector<int> nodes;

	// test case 1
	nodes = { 1, 2, 3, 4, 5 };
	head = linkedlist(nodes);
	k = 2;
	std::cout << "swapNodes([" << head << "]," << k << ") = ";
	std::cout << "[" << sol.swapNodes(head, k) << "]" << std::endl;
	dellinkedlist(head);

	// test case 2
	nodes = { 7, 9, 6, 6, 7, 8, 3, 0, 9, 5 };
	head = linkedlist(nodes);
	k = 5;
	std::cout << "swapNodes([" << head << "]," << k << ") = ";
	std::cout << "[" << sol.swapNodes(head, k) << "]" << std::endl;
	dellinkedlist(head);

	return 0;
}