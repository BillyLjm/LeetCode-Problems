/*******************************************************************************
 * 2181-Merge_Nodes_in_Between_Zeros.cpp
 * Billy.Ljm
 * 04 July 2024
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/merge-nodes-in-between-zeros/
 *
 * You are given the head of a linked list, which contains a series of integers
 * separated by 0's. The beginning and end of the linked list will have
 * Node.val == 0.
 *
 * For every two consecutive 0's, merge all the nodes lying in between them into
 * a single node whose value is the sum of all the merged nodes. The modified
 * list should not contain any 0's.
 *
 * Return the head of the modified linked list.
 *
 * ===========
 * My Approach
 * ===========
 * We'll use two pointers. One crawls to the next zero, summing the nodes it
 * passes. The other stays at the previous zero so that we can connect it to the
 * new merged node. I'll make sure to delete the nodes as I merge them.
 *
 * This has a time complexity of O(n) and space complexity of O(1), where n is
 * the length of the array.
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
 * Definition for singly-linked list
 */
struct ListNode {
	int val;
	ListNode* next;
	ListNode() : val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode* next) : val(x), next(next) {}
};

/**
 * Constructs singly-linked list from vector
 */
ListNode* LinkedList(const vector<int>& values) {
	if (values.empty()) return nullptr; // trivial case
	// construct linked list
	ListNode* head = new ListNode(values[0]);
	ListNode* crawler = head;
	for (size_t i = 1; i < values.size(); ++i) {
		crawler->next = new ListNode(values[i]);
		crawler = crawler->next;
	}
	return head;
}

/**
 * Deletes a linked list and all nodes
 */
void DeleteLinkedList(ListNode* head) {
	ListNode* next;
	while (head != nullptr) {
		next = head->next;
		delete head;
		head = next;
	}
}

/**
 * Prints a LinkedList as a vector
 */
std::ostream& operator<<(std::ostream& os, ListNode* head) {
	os << "[";
	ListNode* crawler = head;
	while (crawler != nullptr) {
		os << crawler->val << ",";
		crawler = crawler->next;
	}
	if (head != nullptr) os << "\b";
	os << "]";
	return os;
}

/**
 * Solution
 */
class Solution {
private:
	ListNode* crawl(ListNode* crawler) {
		ListNode* next = crawler->next;
		delete crawler;
		crawler = next;
		return crawler;
	}

public:
	ListNode* mergeNodes(ListNode* head) {
		int summ = 0;
		ListNode *crawler, * prev;

		// ignore any initial zeros
		while (head->val == 0) {
			head = crawl(head);
		}
		// merge first nodes to new head
		summ = 0;
		while (head->val != 0) {
			summ += head->val;
			head = crawl(head);
		}
		head->val = summ;

		// merge rest of list
		crawler = head;
		while (crawler != nullptr) {
			prev = crawler;
			crawler = crawler->next;
			summ = 0;
			while (crawler != nullptr and crawler->val != 0) {
				summ += crawler->val;
				crawler = crawl(crawler);
			}
			if (crawler != nullptr) {
				if (summ > 0) {
					crawler->val = summ;
					prev->next = crawler;
				}
			}
			else { // at end of list
				if (summ > 0) prev->next = new ListNode(summ);
				else prev->next = nullptr;
			}
		}

		return head;
	}
};

/**
 * Test cases
 */
int main(void) {
	Solution sol;
	ListNode* head;

	// test case 1
	head = LinkedList({ 0,3,1,0,4,5,2,0 });
	std::cout << "mergeNodes(" << head << ") = ";
	head = sol.mergeNodes(head);
	std::cout << head << std::endl;
	DeleteLinkedList(head);

	// test case 2
	head = LinkedList({ 0,1,0,3,0,2,2,0 });
	std::cout << "mergeNodes(" << head << ") = ";
	head = sol.mergeNodes(head);
	std::cout << head << std::endl;
	DeleteLinkedList(head);

	return 0;
}