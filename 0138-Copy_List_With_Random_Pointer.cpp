/*******************************************************************************
 * 0138-Copy_List_With_Random_Pointer.cpp
 * Billy.Ljm
 * 05 September 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/copy-list-with-random-pointer/
 *
 * A linked list of length n is given such that each node contains an additional
 * random pointer, which could point to any node in the list, or null.
 *
 * Construct a deep copy of the list. The deep copy should consist of exactly n
 * brand new nodes, where each new node has its value set to the value of its
 * corresponding original node. Both the next and random pointer of the new
 * nodes should point to new nodes in the copied list such that the pointers in
 * the original list and copied list represent the same list state. None of the
 * pointers in the new list should point to nodes in the original list.
 *
 * ===========
 * My Approach
 * ===========
 * We'll copy the normal linked list first, then loop again to add the random
 * pointers. To make it more time efficient, we can save the linked list nodes
 * in a map for faster lookup of its indices when adding the random pointers.
 *
 * This has a time complexity of O(n), and a space complexity of O(n), where n
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
 * Definition for a Node.
 */
class Node {
public:
	int val;
	Node* next;
	Node* random;

	Node(int _val) {
		val = _val;
		next = NULL;
		random = NULL;
	}
};

/**
 * Creates linked list from a vector of consecutive nodes, where the nodes
 * are specified as {value, index of node of random pointer}
 */
Node* createList(vector<vector<int>> nodes) {
	// edge case
	if (nodes.size() == 0) return nullptr;

	// create nodes
	vector<Node*> linkedlist;
	for (int i = 0; i < nodes.size(); i++) {
		linkedlist.push_back(new Node(nodes[i][0]));
	}

	// add links
	for (int i = 0; i < nodes.size(); i++) {
		// normal link
		if (i + 1 < nodes.size()) {
			linkedlist[i]->next = linkedlist[i + 1];
		}
		else {
			linkedlist[i]->next = nullptr;
		}
		// random pointer
		if (nodes[i][1] >= 0) {
			linkedlist[i]->random = linkedlist[nodes[i][1]];
		}
		else {
			linkedlist[i]->random = nullptr;
		}
	}

	return linkedlist[0];
}

/**
 * Translates the linked list into a 2D vector for printing. The vector will be
 * consecutive links represented as {value, index of node of random pointer}
 */
vector<vector<int>> printList(Node* head) {
	vector<vector<int>> out;
	Node* crawler;
	unordered_map<Node*, int> idx; // map of node to index

	// edge case
	if (head == nullptr) return vector<vector<int>>();

	// fill in map
	crawler = head;
	while (crawler != nullptr) {
		idx[crawler] = idx.size();
		crawler = crawler->next;
	}

	// fill in output vector
	crawler = head;
	while (crawler != nullptr) {
		if (crawler->random != nullptr) {
			out.push_back({ crawler->val, idx[crawler->random] });
		}
		else {
			out.push_back({ crawler->val, -1 });
		}
		crawler = crawler->next;
	}

	return out;
}

/**
 * Deallocate linked list
 */
void deleteList(Node* head) {
	// edge case
	if (head == nullptr) return;

	Node* tmp;
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
	Node* copyRandomList(Node* head) {
		Node* crawler;
		unordered_map<Node*, int> idx; // map of node to index
		vector<Node*> copied; // copied nodes

		// edge case;
		if (head == nullptr) return nullptr;

		// first traversal
		crawler = head;
		while (crawler != nullptr) {
			idx[crawler] = idx.size(); // fill in map
			copied.push_back(new Node(crawler->val)); // copy nodes
			crawler = crawler->next;
		}

		// second traversal
		crawler = head;
		while (crawler != nullptr) {
			// copy regular links
			if (crawler->next != nullptr) {
				copied[idx[crawler]]->next = copied[idx[crawler->next]];
			}
			else {
				copied[idx[crawler]]->next = nullptr;
			}
			// copy random links
			if (crawler->random != nullptr) {
				copied[idx[crawler]]->random = copied[idx[crawler->random]];
			}
			else {
				copied[idx[crawler]]->random = nullptr;
			}
			crawler = crawler->next;
		}

		return copied[0];
	}
};

/**
 * Test cases
 */
int main(void) {
	Solution sol;
	Node *head, *copied;
	vector<vector<int>> nodes;

	// test case 1
	nodes = { {7,-1},{13,0},{11,4},{10,2},{1,0} };
	head = createList(nodes);
	copied = sol.copyRandomList(head);
	std::cout << "copyRandomList(" << printList(head) << ") = ";
	std::cout << printList(copied) << std::endl;
	deleteList(head);
	deleteList(copied);

	// test case 2
	nodes = { {1,1},{2,1} };
	head = createList(nodes);
	copied = sol.copyRandomList(head);
	std::cout << "copyRandomList(" << printList(head) << ") = ";
	std::cout << printList(copied) << std::endl;
	deleteList(head);
	deleteList(copied);

	// test case 3
	nodes = { {3,-1},{3,0},{3,-1} };
	head = createList(nodes);
	copied = sol.copyRandomList(head);
	std::cout << "copyRandomList(" << printList(head) << ") = ";
	std::cout << printList(copied) << std::endl;
	deleteList(head);
	deleteList(copied);

	return 0;
}