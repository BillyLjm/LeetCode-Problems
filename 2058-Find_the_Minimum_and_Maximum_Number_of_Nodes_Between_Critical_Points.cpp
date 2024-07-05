/*******************************************************************************
 * 2058-Find_the_Minimum_and_Maximum_Number_of_Nodes_Between_Critical_Points.cpp
 * Billy.Ljm
 * 05 July 2024
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/find-the-minimum-and-maximum-number-of-nodes-between-critical-points/
 *
 * A critical point in a linked list is defined as either a local maxima or a
 * local minima.
 *
 * A node is a local maxima if the current node has a value strictly greater
 * than the previous node and the next node.
 *
 * A node is a local minima if the current node has a value strictly smaller
 * than the previous node and the next node.
 *
 * Note that a node can only be a local maxima/minima if there exists both a
 * previous node and a next node.
 *
 * Given a linked list head, return an array of length 2 containing
 * [minDistance, maxDistance] where minDistance is the minimum distance between
 * any two distinct critical points and maxDistance is the maximum distance
 * between any two distinct critical points. If there are fewer than two
 * critical points, return [-1, -1].
 *
 * ===========
 * My Approach
 * ===========
 * We'll just crawl through the linked list, remembering the index of the
 * critical points. To calculate the min and max distance, we actually only
 * need to only remember the two most recent critical points and their distance.
 * The max will be the sum of the distances, and the min will be the min.
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
public:
	vector<int> nodesBetweenCriticalPoints(ListNode* head) {
		int maxdist = 0;
		int mindist = INT_MAX;
		int idx = 1; // index of linked list
		int prevcrit = -1; // index of previous critical point
		ListNode* crawler = head;

		while (crawler->next->next != nullptr) {
			// if critical point
			if ((crawler->next->val < crawler->val and
				 crawler->next->val < crawler->next->next->val) or
				(crawler->next->val > crawler->val and
				 crawler->next->val > crawler->next->next->val)) {
				if (prevcrit != -1) {
					mindist = min(mindist, idx - prevcrit);
					maxdist += idx - prevcrit;
				}
				prevcrit = idx;
			}
			// crawl to next node
			crawler = crawler->next;
			idx++;
		}

		if (maxdist == 0) return { -1,-1 };
		else return { mindist, maxdist };
	}
};

/**
 * Test cases
 */
int main(void) {
	Solution sol;
	ListNode* head;

	// test case 1
	head = LinkedList({ 3,1 });
	std::cout << "nodesBetweenCriticalPoints(" << head << ") = ";
	std::cout << sol.nodesBetweenCriticalPoints(head) << std::endl;
	DeleteLinkedList(head);

	// test case 2
	head = LinkedList({ 5,3,1,2,5,1,2 });
	std::cout << "nodesBetweenCriticalPoints(" << head << ") = ";
	std::cout << sol.nodesBetweenCriticalPoints(head) << std::endl;
	DeleteLinkedList(head);

	return 0;
}