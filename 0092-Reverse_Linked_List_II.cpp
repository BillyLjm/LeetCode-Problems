/*******************************************************************************
 * 0092-Reverse_Linked_List_II.cpp
 * Billy.Ljm
 * 07 September 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/reverse-linked-list-ii/
 *
 * Given the head of a singly linked list and two integers left and right where
 * left <= right, reverse the nodes of the list from position left to position
 * right, and return the reversed list.
 *
 * ===========
 * My Approach
 * ===========
 * We'll reverse the specified section of the linked list with 3 pointers. Then,
 * we just have to reconnect the front, reversed, and back sections with a
 * similar method.
 *
 * This has a time complexity of O(n), and a space complexity of O(1), where n
 * is the length of the linked list.
 ******************************************************************************/

#include <iostream>
#include <vector>

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
 * Definition for singly - linked list.
 */
struct ListNode {
	int val;
	ListNode* next;
	ListNode() : val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode* next) : val(x), next(next) {}
};

/**
 * Creates linked list from a vector of consecutive nodes, where the nodes
 * are specified as {value, index of node of random pointer}
 */
ListNode* createList(vector<int> values) {
	// create head
	ListNode* head;
	if (values.size() > 0) head = new ListNode(values[0]);
	else head = nullptr;

	// create linked list
	ListNode* crawler = head;
	for (int i = 1; i < values.size(); i++) {
		crawler->next = new ListNode(values[i]);
		crawler = crawler->next;
	}

	return head;
}

/**
 * << operator for linked list
 */
std::ostream& operator<<(std::ostream& os, const ListNode* node) {
	const ListNode* current = node;

	os << "[";
	while (current != nullptr) {
		os << current->val;
		if (current->next != nullptr) {
			os << ",";
		}
		current = current->next;
	}
	os << "]";

	return os;
}

/**
 * Deallocate linked list
 */
void deleteList(ListNode* head) {
	if (head == nullptr) return;
	ListNode* tmp;
	while (head != nullptr) {
		tmp = head->next;
		delete head;
		head = tmp;
	}
}

/**
 * Solution
 */
class Solution {
public:
	ListNode* reverseBetween(ListNode* head, int left, int right) {
		// edge case
		if (right <= left) return head;

		// find unreversed section
		ListNode *before, *after;
		if (left <= 1) {
			before = nullptr;
			after = head;
		}
		else {
			before = head;
			for (int i = 0; i < left - 2; i++) {
				before = before->next;
			}
			after = before->next;
			before->next = nullptr;
		}

		// reverse section
		ListNode * prev, * curr, * next;
		prev = nullptr;
		curr = after;
		next = curr;
		for (int i = left; i <= right; i++) {
			if (curr == nullptr) break;
			next = curr->next;
			curr->next = prev;
			prev = curr;
			curr = next;
		}
		
		// concatenate sections
		if (before != nullptr) {
			before->next = prev;
		}
		else {
			head = prev;
		}
		after->next = curr;

		return head;
	}
};

/**
 * Test cases
 */
int main(void) {
	Solution sol;
	vector<int> values;
	int left, right;
	ListNode* head;

	// test case 1
	values = { 1,2,3,4,5 };
	left = 2;
	right = 6;
	head = createList(values);
	std::cout << "reverseBetween(" << head << "," << left << "," << right << ") = ";
	head = sol.reverseBetween(head, left, right);
	std::cout << head << endl;
	deleteList(head);

	// test case 2
	values = { 5 };
	left = 1;
	right = 1;
	head = createList(values);
	std::cout << "reverseBetween(" << head << "," << left << "," << right << ") = ";
	head = sol.reverseBetween(head, left, right);
	std::cout << head << endl;
	deleteList(head);

	return 0;
}