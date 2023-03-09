/*******************************************************************************
 * 0142-Linked_List_Cycle_II.cpp
 * Billy.Ljm
 * 09 Mar 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/linked-list-cycle-ii/
 * Given the head of a linked list, return the node where the cycle begins. If
 * there is no cycle, return null. There is a cycle in a linked list if there is
 * some node in the list that can be reached again by continuously following the
 * next pointer. Internally, pos is used to denote the index of the node that
 * tail's next pointer is connected to (0-indexed). It is -1 if there is no
 * cycle. Note that pos is not passed as a parameter. Do not modify the linked
 * list.
 *
 * ===========
 * My Approach
 * ===========
 * The intuitive approach is to just traverse the linked list, while remembering
 * nodes that were visited before and checking newly-visited nodes against old
 * ones. However, this require O(n) space and O(n) time.
 *
 * https://www.geeksforgeeks.org/floyds-cycle-finding-algorithm/
 * But we can make this more space-efficient with Floyd's cycle finding
 * algorithm. There, we have two crawlers traversing the tree at different
 * speeds. This way, if there is a loop, the faster crawler will keep looping
 * until it meets the slower one. Thus, we just have to check if the two
 * crawlers meet at the same node, instead of remembering all the past nodes.
 *
 * To find the looping node, we can bisect the linked list into a non-looping
 * head of length k and a looping tail of length l. And let the crawlers meet
 * at index b. When they meet, the faster crawler has traversed k + b + nl and
 * the slower crawler k + b + Nl. Assuming the faster crawler is twice the speed
 * of the slower one, we have k + b + nl = 2(k + b + Nl), which implies
 * k = (N - n) l - b. If we then reset one of the crawlers to the head, and
 * evolve both at the same speed now, the crawlers will automatically meet again
 * after k steps at k = k + Nl, at the looping point.
 ******************************************************************************/

#include <iostream>
#include <vector>

/**
 * Definition for singly-linked list.
 */
struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
	/**
	 * Detects any cycles in a linked list
	 *
	 * @param head head of linked list to check
	 *
	 * @return head of the cycle; NULL if no cycles found
	 */
	ListNode* detectCycle(ListNode* head) {
		ListNode* fast = head;
		ListNode* slow = head;

		// trivial case, too short to loop
		for (int i = 0; i < 4; i++) {
			if (slow == NULL) {
				return NULL;
			}
			slow = slow->next;
		}
		slow = head;

		while (fast != NULL) {
			// loop until meet
			slow = slow->next;
			fast = fast->next;
			if (fast == NULL){
				return NULL;
			}
			else {
				fast = fast->next;
			}

			// reset & do last loop until met
			if (fast == slow) {
				slow = head;
				while (fast != slow) {
					fast = fast->next;
					slow = slow->next;
				}
				return slow;
			}
		}

		// fast crawler doesn't loop
		return NULL;
	}
};

/**
 * Print function for vectors
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
 * Test cases
 */
int main(void) {
	Solution sol;
	std::vector<int> array;
	ListNode head(0);
	ListNode* tail;
	ListNode* del;

	// test case 1
	array = {3, 2, 0, -4};
	head.val = array[0];
	tail = &head;
	for (int i = 1; i < array.size(); i++) {
		ListNode* node = new ListNode(array[i]);
		tail->next = node;
		tail = node;
	}
	tail->next = head.next;
	std::cout << "detectCycle " << array << ": " <<
		sol.detectCycle(&head)->val << std::endl;
	// deallocate list
	tail = head.next;
	for (int i = 1; i < array.size(); i++) {
		del = tail->next;
		delete tail;
		tail = del;
	}
	head.next = NULL;

	// test case 2
	array = { 1, 2 };
	head.val = array[0];
	tail = &head;
	for (int i = 1; i < array.size(); i++) {
		ListNode* node = new ListNode(array[i]);
		tail->next = node;
		tail = node;
	}
	tail->next = &head;
	std::cout << "detectCycle " << array << ": " <<
		sol.detectCycle(&head)->val << std::endl;
	// deallocate list
	delete head.next;
	head.next = NULL;

	// test case 3
	head.val = 0;
	std::cout << "detectCycle " << array << ": " <<
		sol.detectCycle(&head) << std::endl;
}