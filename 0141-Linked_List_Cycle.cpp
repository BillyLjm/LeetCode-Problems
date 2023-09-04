/*******************************************************************************
 * 0141-Linked_List_Cycle.cpp
 * Billy.Ljm
 * 04 September 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/linked-list-cycle/
 *
 * Given head, the head of a linked list, determine if the linked list has a
 * cycle in it.
 *
 * There is a cycle in a linked list if there is some node in the list that can
 * be reached again by continuously following the next pointer. Internally, pos
 * is used to denote the index of the node that tail's next pointer is connected
 * to. Note that pos is not passed as a parameter.
 *
 * Return true if there is a cycle in the linked list. Otherwise, return false.
 *
 * ===========
 * My Approach
 * ===========
 * We'll use Floyd's cycle finding algorithm, where we have one fast pointer
 * advancing two links at a time, and one slow pointer advancing one link at
 * a time. If there is a cycle, the two pointer will go around the cycle at
 * different speeds until they eventually meet.
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
 * Definition for singly - linked list
 */
struct ListNode {
	int val;
	ListNode* next;
	ListNode(int x) : val(x), next(NULL) {}
};

/**
 * Creates a linked list, with the last link cycling back to a specified position
 */
ListNode* createList(vector<int> values, int cycle_pos) {
	ListNode* head = new ListNode(values[0]);

	// create linked list
	ListNode* crawler = head;
	for (int i = 1; i < values.size(); i++) {
		crawler->next = new ListNode(values[i]);
		crawler = crawler->next;
	}

	// add cycle
	ListNode* end = crawler;
	if (cycle_pos >= 0) {
		crawler = head;
		for (int i = 0; i < cycle_pos; i++) {
			crawler = crawler->next;
		}
		end->next = crawler;
	}

	return head;
}

/**
 * Deallocate a linked list of specified length
 */
void deleteList(ListNode* head, int length) {
	ListNode* crawler = head->next;
	for (int i = 0; i < length; i++) {
		delete head;
		head = crawler;
		crawler = head->next;
	}
}

/**
 * Solution
 */
class Solution {
public:
	bool hasCycle(ListNode* head) {
		ListNode *fast = head, *slow = head;

		while (fast != nullptr) {
			// advance pointers
			slow = slow->next;
			fast = fast->next;
			if (fast != nullptr) fast = fast->next;
			// check if cycle found
			if (fast == slow and fast != nullptr) return true;
		}

		// linked list ends, with no cycle
		return false;
	}
};

/**
 * Test cases
 */
int main(void) {
	Solution sol;
	vector<int> values;
	int pos;
	ListNode* head;

	// test case 1
	values = { 3,2,0,-4 };
	pos = 1;
	head = createList(values, pos);
	std::cout << "hasCycle(" << values << "," << pos << ") = ";
	std::cout << std::boolalpha << sol.hasCycle(head) << std::endl;
	deleteList(head, values.size());

	// test case 2
	values = { 1,2 };
	pos = 0;
	head = createList(values, pos);
	std::cout << "hasCycle(" << values << "," << pos << ") = ";
	std::cout << std::boolalpha << sol.hasCycle(head) << std::endl;
	deleteList(head, values.size());

	// test case 3
	values = { 1 };
	pos = -1;
	head = createList(values, pos);
	std::cout << "hasCycle(" << values << "," << pos << ") = ";
	std::cout << std::boolalpha << sol.hasCycle(head) << std::endl;
	deleteList(head, values.size());

	return 0;
}