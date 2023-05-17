/*******************************************************************************
 * 2130-Maximum_Twin_Sum_of_Linked_List.cpp
 * Billy.Ljm
 * 17 May 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/maximum-twin-sum-of-a-linked-list/
 *
 * In a linked list of size n, where n is even, the ith node (0-indexed) of the
 * linked list is known as the twin of the (n-1-i)th node, if 0 <= i <=
 * (n / 2) - 1.
 *
 * For example, if n = 4, then node 0 is the twin of node 3, and node 1 is the
 * twin of node 2. These are the only nodes with twins for n = 4.
 *
 * The twin sum is defined as the sum of a node and its twin.
 *
 * Given the head of a linked list with even length, return the maximum twin sum
 * of the linked list.
 *
 * ===========
 * My Approach
 * ===========
 * I'll continue working in the linked list data structure, and reverse the
 * second half of the linked list. To find the halfway mark of the linked list,
 * we can just use two crawlers with one at twice the speed of the other. Once
 * the halfway mark is identified, we reverse the second half and break the
 * linked list into two. Then, we just iterate through both lists, sum them and
 * remember the maximum.
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
	 * Returns the maximum sum of the (i)-th and (-i)-th element of a linked list
	 *
	 * @param head head of the linked list
	 *
	 * @return maximum sum of the (i)-th and (-i)-th element
	 */
	int pairSum(ListNode* head) {
		// 1 element list
		if (head->next == nullptr) { 
			return head->val;
		}
		// 2 element list
		else if (head->next->next == nullptr) { 
			return head->val + head->next->val;
		}
		// n element list
		else { 
			ListNode* prev, * curr, * next, * head2; // to reverse linked list
			int maxsum; // maximum pair sum

			// find halfway point of linked list
			prev = head;
			curr = head;
			while (curr->next != nullptr and curr->next->next != nullptr) {
				prev = prev->next;
				curr = curr->next->next;
			}

			// reverse second half of linked list
			curr = prev->next; // first node
			next = curr->next; 
			prev->next = nullptr;
			prev = nullptr;
			while (next != nullptr) {
				curr->next = prev; // reverse link
				prev = curr; // move to next node
				curr = next;
				next = next->next;
			}
			curr->next = prev; // last node
			head2 = curr;

			// find max pair sum
			maxsum = 0;
			prev = head; // crawlers, just reusing var names
			curr = head2;
			while (prev != nullptr and curr != nullptr) {
				maxsum = std::max(prev->val + curr->val, maxsum);
				prev = prev->next;
				curr = curr->next;
			}

			return maxsum;
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
 * << operator for ListNodes's linked list
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
	nodes = { 5, 4, 2, 1 };
	head = linkedlist(nodes);
	std::cout << "pairSum([" << head << "]) = ";
	std::cout << sol.pairSum(head) << std::endl;
	dellinkedlist(head);

	// test case 2
	nodes = { 4, 2, 2, 3 };
	head = linkedlist(nodes);
	std::cout << "pairSum([" << head << "]) = ";
	std::cout << sol.pairSum(head) << std::endl;
	dellinkedlist(head);

	// test case 3
	nodes = { 1, 100000 };
	head = linkedlist(nodes);
	std::cout << "pairSum([" << head << "]) = ";
	std::cout << sol.pairSum(head) << std::endl;
	dellinkedlist(head);

	return 0;
}