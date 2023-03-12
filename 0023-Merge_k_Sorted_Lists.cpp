/*******************************************************************************
 * 0023-Merge_k_Sorted_Lists.cpp
 * Billy.Ljm
 * 12 Mar 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/merge-k-sorted-lists/
 * You are given an array of k linked-lists lists, each linked-list is sorted in
 * ascending order. Merge all the linked-lists into one sorted linked-list and
 * return it.
 *
 * ===========
 * My Approach
 * ===========
 * Since the linked list is sorted, we can just compare across the heads of each
 * linked list, find the smallest element and append it to the final list. The
 * comparison across heads can be further optimised with a priority queue to
 * reduce the comparison cost form O(k) to O(log(k)).
 *
 * Thus, the time complexity is O(n log(k)), where n is the total number of
 * nodes and k is the number of linked lists. The space complexity is O(1),
 * since we'll implement a sort-in-place algorithm.
 ******************************************************************************/

#include <iostream>
#include <vector>
#include <queue>

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
 * Comparator for ListNode
 */
struct ListNodeComparator {
	bool operator()(const ListNode* lhs, const ListNode* rhs) const {
		return lhs->val > rhs->val;
	}
};

class Solution {
public:
	/**
	 * Merges multiple sorted linked lists into one long sorted linked list
	 *
	 * @param lists array of linked list to merge
	 *
	 * @return head of the merged linked list
	 */
	ListNode* mergeKLists(std::vector<ListNode*>& lists) {
		// fill priority queue for first time
		std::priority_queue<ListNode*, std::vector<ListNode*>,
			ListNodeComparator> pq;
		for (ListNode* list : lists) {
			if (list != nullptr) {
				pq.push(list);
			}
		}

		// short circuit
		if (pq.empty()) {
			return nullptr;
		}

		// pop the first node as the head
		ListNode* head = pq.top();
		ListNode* crawler = head;
		pq.pop();
		if (head->next != nullptr) {
			pq.push(head->next);
		}

		// pop the rest of the arrays
		while (!pq.empty()) {
			crawler->next = pq.top();
			crawler = crawler->next;
			pq.pop();
			if (crawler->next != nullptr) {
				pq.push(crawler->next);
			}
		}

		return head;
	}
};

/**
 * Print function for linked list
 */
std::ostream& operator<<(std::ostream& os, ListNode* head) {
	ListNode* crawler = head;
	while (crawler != nullptr) {
		std::cout << crawler->val << " ";
		crawler = crawler->next;
	}
	std::cout << std::endl;
	return os;
}

/**
 * Test cases
 */
int main(void) {
	Solution sol;
	std::vector<ListNode*> lists;
	ListNode* root;

	// test case 1
	lists.push_back(nullptr);
	lists.push_back(new ListNode(1));
	root = sol.mergeKLists(lists);
	std::cout << root << std::endl;
	delete lists[1];
	lists.pop_back();
	lists.pop_back();

	// test case 2
	lists.push_back(new ListNode(1, new ListNode(4, new ListNode(5))));
	lists.push_back(new ListNode(1, new ListNode(3, new ListNode(4))));
	lists.push_back(new ListNode(2, new ListNode(6)));
	root = sol.mergeKLists(lists);
	std::cout << root << std::endl;
}