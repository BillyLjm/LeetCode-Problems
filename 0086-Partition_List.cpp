/*******************************************************************************
 * 0086-Partition_List.cpp
 * Billy.Ljm
 * 15 August 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/partition-list/
 *
 * Given the head of a linked list and a value x, partition it such that all
 * nodes less than x come before nodes greater than or equal to x.
 *
 * You should preserve the original relative order of the nodes in each of the
 * two partitions.
 *
 * ===========
 * My Approach
 * ===========
 * We'll literally partition it into two linked lists, and concatenate them at
 * the end.
 *
 * This has a time complexity of O(n), and a space complexity of  O(n), where
 * n is the length of the linked list.
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
 * Creates a linked list from a vector
 */
ListNode* createLL(vector<int> elements) {
	ListNode* head = new ListNode(elements[0]);
	ListNode* crawler = head;
	for (size_t i = 1; i < elements.size(); i++) {
		crawler->next = new ListNode(elements[i]);
		crawler = crawler->next;
	}
	return head;
}

/**
 * Delete linked list
 */
void deleteLL(ListNode* head) {
	ListNode* crawler;
	while (head != nullptr) {
		crawler = head;
		head = head->next;
		delete crawler;
	}
}

/**
 * Print linked list
 */
void printLL(ListNode* head) {
	if (head != nullptr) {
		std::cout << head->val << ",";
		printLL(head->next);
	}
}

/**
 * Solution
 */
class Solution {
public:
	ListNode* partition(ListNode* head, int x) {
		if (head == nullptr or head->next == nullptr) return head;

		ListNode* greater = nullptr, * lesser = nullptr;
		ListNode* crawlh = head, * crawlg = greater, * crawll = lesser;

		// partition
		while (crawlh != nullptr) {
			if (crawlh->val < x) {
				if (lesser == nullptr) {
					lesser = crawlh;
					crawll = lesser;
				}
				else {
					crawll->next = crawlh;
					crawll = crawll->next;
				}
			}
			else {
				if (greater == nullptr) {
					greater = crawlh;
					crawlg = greater;
				}
				else {
					crawlg->next = crawlh;
					crawlg = crawlg->next;
				}
			}
			crawlh = crawlh->next;
		}

		// concatenate
		if (lesser == nullptr) {
			crawlg = nullptr;
			return greater;
		}
		else if (greater == nullptr) {
			crawll = nullptr;
			return lesser;
		}
		else {
			crawll->next = greater;
			crawlg->next = nullptr;
			return lesser;
		}
	}
};

/**
 * Test cases
 */
int main(void) {
	Solution sol;
	ListNode* head;
	int x;

	// test case 1
	head = createLL({ 1,4,3,2,5,2 });
	x = 3;
	std::cout << "partition([";
	printLL(head);
	std::cout << "\b]," << x << ") = [";
	printLL(sol.partition(head, x));
	std::cout << "\b]" << std::endl;
	deleteLL(head);

	// test case 2
	head = createLL({ 2,1 });
	x = 2;
	std::cout << "partition([";
	printLL(head);
	std::cout << "\b]," << x << ") = [";
	printLL(sol.partition(head, x));
	std::cout << "\b]" << std::endl;
	deleteLL(head);

	return 0;
}