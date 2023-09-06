/*******************************************************************************
 * 0725-Split_Linked_List_in_Parts.cpp
 * Billy.Ljm
 * 06 September 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/split-linked-list-in-parts/
 *
 * Given the head of a singly linked list and an integer k, split the linked
 * list into k consecutive linked list parts.
 *
 * The length of each part should be as equal as possible: no two parts should
 * have a size differing by more than one. This may lead to some parts being null.
 *
 * The parts should be in the order of occurrence in the input list, and parts
 * occurring earlier should always have a size greater than or equal to parts
 * occurring later.
 *
 * Return an array of the k parts.
 *
 * ===========
 * My Approach
 * ===========
 * To find the head of each split list, we'll use k pointers advancing at
 * different speeds. The first will advance one link at a time, the second
 * advances two links, as so on. Then, when the k-th pointer arrives at the
 * end of the original linked list, all the other pointers will be at the end
 * (or the head) of each split linked list. If the linked list is not divisible
 * by k, then the k-th pointer will reach the end before it can advance k links,
 * and we have to advance the corresponding pointers accordingly.
 *
 * This has a time complexity of O(n), and a space complexity of O(1), where n
 * is the length of the linked list.
 ******************************************************************************/

#include <iostream>
#include <vector>
#include <unordered_map>

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
	vector<ListNode*> splitListToParts(ListNode* head, int k) {
		// pointers that will advance at different speeds
		vector<ListNode*> ptrs(k);
		ptrs[0] = head;
		for (int i = 1; i < ptrs.size(); i++) {
			if (ptrs[i - 1] != nullptr) ptrs[i] = ptrs[i - 1]->next;
			else ptrs[i] = nullptr;
		}

		// edge case: linked list shorter than number of parts
		if (ptrs.back() == nullptr) {
			for (int i = 0; i < ptrs.size(); i++) {
				if (ptrs[i] != nullptr) ptrs[i]->next = nullptr;
			}
			return ptrs;
		}
		
		// advance pointers at different speeds
		int seglen; // length of segment traversed by k-th pointer
		while (ptrs.back()->next != nullptr) {
			// advance the k pointer one by one, counting length it'll advance
			seglen = 0;
			while (ptrs.back()->next != nullptr and seglen < k) {
				ptrs.back() = ptrs.back()->next;
				seglen++;
			}
			// advance all the other pointers appropriately
			for (int i = 0; i < seglen; i++) {
				for (int j = i; j < ptrs.size() - 1; j++) {
					ptrs[j] = ptrs[j]->next;
				}
			}
		}

		// close split linked list and create output
		vector<ListNode*> out = { head };
		for (int i = 0; i < ptrs.size() - 1; i++) {
			out.push_back(ptrs[i]->next);
			ptrs[i]->next = nullptr;
		}

		return out;
	}
};

/**
 * Test cases
 */
int main(void) {
	Solution sol;
	vector<int> values;
	int k;
	ListNode* head;
	vector<ListNode*> split;

	// test case 1
	values = { 1,2,3 };
	k = 5;
	head = createList(values);
	std::cout << "splitListToParts(" << head << "," << k << ") = ";
	split = sol.splitListToParts(head, k);
	std::cout << split << endl;
	for (ListNode* i : split) deleteList(i);

	// test case 2
	values = { 1,2,3,4,5,6,7,8,9,10 };
	k = 3;
	head = createList(values);
	std::cout << "splitListToParts(" << head << "," << k << ") = ";
	split = sol.splitListToParts(head, k);
	std::cout << split << endl;
	for (ListNode* i : split) deleteList(i);

	return 0;
}