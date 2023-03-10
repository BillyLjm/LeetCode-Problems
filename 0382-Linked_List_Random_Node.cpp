/*******************************************************************************
 * 0382-Linked_List_Random_Node.cpp
 * Billy.Ljm
 * 10 Mar 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/linked-list-random-node/
 * Given a singly linked list, return a random node's value from the linked list.
 * Each node must have the same probability of being chosen. Implement the
 * Solution class: Solution(ListNode head) Initializes the object with the head
 * of the singly-linked list head. int getRandom() Chooses a node randomly from
 * the list and returns its value. All the nodes of the list should be equally
 * likely to be chosen.
 *
 * ===========
 * My Approach
 * ===========
 * The intuitive approach is to just convert the linked list to an array, and
 * select from it with a randomly-generated index. However, this has a space
 * complexity of O(n), and a time complexity of O(n), where n is the length of
 * the linked list.
 *
 * A more space-efficient method is reservoir sampling. The most basic version
 * involves reading from a stream, including each in the element in the random
 * array with a probability 1/i, and keeping it in the list for every element
 * thereafter with a probability i/i+1 = 1 - 1/i+1, where i is the number of
 * elements read so far. This way, after the stream is exhausted, each element
 * has a chance 1/i * i/i+1 * ... * n-1/n = 1/n of being in the randomised array,
 * where n is the length of the stream.
 ******************************************************************************/

#include <iostream>
#include <vector>

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

class Solution {
public:
	ListNode* head;

	/**
	 * Defines the linked list to get a random node from
	 *
	 * @param head head of the linked list to get a random node from
	 */
	Solution(ListNode* head) {
		this->head = head;
	}

	/**
	 * Gets a random node of the linked list, via reservoir sampling
	 */
	int getRandom() {
		// Basic reservoir sampling
		int randnode;
		int count = 1; // sufficient for 2^16 > 10^4 long linked lists
		ListNode* crawler = this->head;
		while (crawler != nullptr) {
			if (rand() % count == 0) {
				randnode = crawler->val;
			}
			crawler = crawler->next;
			count++;
		}
		return randnode;
	}
};

/**
 * Test cases
 */
int main(void) {
	// test case 1
	ListNode* head = new ListNode(1, new ListNode(2, new ListNode(3)));
	Solution* obj = new Solution(head);
	for (int i = 0; i < 10; i++) {
		std::cout << obj->getRandom() << std::endl;
	}
}