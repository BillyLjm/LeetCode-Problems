/*******************************************************************************
 * 0024-Swap_Nodes_in_Pairs.cpp
 * Billy.Ljm
 * 16 May 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/swap-nodes-in-pairs/
 *
 * Given a linked list, swap every two adjacent nodes and return its head. You
 * must solve the problem without modifying the values in the list's nodes
 * (i.e., only nodes themselves may be changed.)
 *
 * ===========
 * My Approach
 * ===========
 * We just have to crawl through the list, remember the two nodes preceeding
 * those to be swapped, and the child of the later node to be swapped so nothing
 * is orphaned. Then we just carefully swap them.
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
	 * Swaps every pair in a linked list (by address, not value)
	 *
	 * @param head head of linked list to swap
	 *
	 * @return head of linked list with every pair swapped
	 */
	ListNode* swapPairs(ListNode* head) {
		// if 0 or 1 element, no pairs to swap
		if (head == nullptr or head->next == nullptr) {
			return head;
		}
		// else swap all pairs
		else {
			ListNode* node1 = head;
			ListNode* node2 = head->next;
			ListNode* tmp;

			// swap 0th and 1st node
			tmp = node2->next;
			node2->next = node1;
			node1->next = tmp;
			head = node2; // node2 - node1 - c - d

			// move to next pair
			for (int i = 0; i < 2; i++) { // a - node1 - node2 - d
				if (node2->next == nullptr) break;
				node2 = node2->next;
			}

			// swap every subsequent pair
			while (node2->next != nullptr) {
				// swap nodes
				tmp = node2->next->next;
				node1->next = node2->next;
				node1->next->next = node2;
				node2->next = tmp; // node1 - b - node2 - d
				// move to next pair
				for (int i = 0; i < 1; i++) { // node1 - b - c - node2
					if (node2->next == nullptr) break;
					node2 = node2->next;
				}
				for (int i = 0; i < 2; i++) { // a - b - node1 - node2
					if (node1->next == nullptr) break;
					node1 = node1->next;
				}
			}

			return head;
		}
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
	if (head == nullptr) {
		; // nothing to delete
	}
	else if (head->next == nullptr) {
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
	if (head == nullptr) {
		return os;
	}
	else if (head->next == nullptr) {
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
	ListNode* head;
	std::vector<int> nodes;

	// test case 1
	nodes = { 1, 2, 3, 4 };
	head = linkedlist(nodes);
	std::cout << "swapPairs([" << head << "]) = ";
	std::cout << "[" << sol.swapPairs(head) << "]" << std::endl;
	dellinkedlist(head);

	// test case 2
	nodes = { };
	head = linkedlist(nodes);
	std::cout << "swapPairs([" << head << "]) = ";
	std::cout << "[" << sol.swapPairs(head) << "]" << std::endl;
	dellinkedlist(head);

	// test case 3
	nodes = { 1 };
	head = linkedlist(nodes);
	std::cout << "swapPairs([" << head << "]) = ";
	std::cout << "[" << sol.swapPairs(head) << "]" << std::endl;
	dellinkedlist(head);

	return 0;
}