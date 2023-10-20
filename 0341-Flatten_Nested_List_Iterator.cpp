/*******************************************************************************
 * 0341-Flatten_Nested_List_Iterator.cpp
 * Billy.Ljm
 * 20 October 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/flatten-nested-list-iterator/
 *
 * You are given a nested list of integers nestedList. Each element is either an
 * integer or a list whose elements may also be integers or other lists.
 * Implement an iterator to flatten it.
 *
 * Implement the NestedIterator class:
 * - NestedIterator(List<NestedInteger> nestedList) Initializes the iterator
 *   with the nested list nestedList.
 * - int next() Returns the next integer in the nested list.
 * - boolean hasNext() Returns true if there are still some integers in the
 *   nested list and false otherwise.
 *
 * Your code will be tested with the following pseudocode:
 * ```
 * initialize iterator with nestedList
 * res = []
 * while iterator.hasNext()
 *     append iterator.next() to the end of res
 * return res
 * ```
 * If res matches the expected flattened list, then your code will be judged as
 * correct.
 *
 * ===========
 * My Approach
 * ===========
 * We will use a stack to remember each element of the list, and then flatten
 * each element as needed.
 *
 * This has a time complexity of O(n) for each method, and space complexity of
 * O(n), where n is number of integers in the nested lists.
 ******************************************************************************/

#include <iostream>
#include <vector>
#include <stack>

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
 * Interface for creating nested lists.
 */
class NestedInteger {
private:
	vector<NestedInteger> list;
	int val;
	bool isInt;

public:
	/**
	 * Create nested list of list
	 */
	NestedInteger(vector<NestedInteger> lists) {
		this->list = lists;
		this->isInt = false;
	}

	/**
	 * Create nested list of integer
	 */
	NestedInteger(int val) {
		this->val = val;
		this->isInt = true;
	}

	/**
	 * Return true if this NestedInteger holds a single integer, rather than a
	 * nested list.
	 */
	const bool isInteger() {
		return this->isInt;
	}

	/**
	 * Return the single integer that this NestedInteger holds, if it holds a
	 * single integer. The result is undefined if this NestedInteger holds a
	 * nested list.
	 */
	const int getInteger() {
		if (this->isInteger()) return this->val;
	}

	/**
	 * Return the nested list that this NestedInteger holds, if it holds a
	 * nested list. The result is undefined if this NestedInteger holds a single
	 * integer.
	 */
	const vector<NestedInteger>& getList() {
		if (not this->isInteger()) return this->list;
	}
};

/**
 * For iterating through vectors of NestedIntegers in flattened order
 */
class NestedIterator {
private:
	stack<NestedInteger> stk;

public:
	/**
	 * Initializes the iterator with the nested list nestedList.
	 */
	NestedIterator(vector<NestedInteger>& nestedList) {
		for (int i = nestedList.size() - 1; i >= 0; i--) {
			stk.push(nestedList[i]);
		}
	}

	/**
	 * Flatten the top of the stack
	 */
	void flattenTop() {
		vector<NestedInteger> ls;
		while (!stk.empty() && !stk.top().isInteger()) {
			ls = stk.top().getList();
			stk.pop();
			for (int i = ls.size() - 1; i >= 0; i--) {
				stk.push(ls[i]);
			}
		}
	}

	/**
	 * Returns next integer in nested list
	 */
	int next() {
		flattenTop();
		NestedInteger top = stk.top();
		stk.pop();
		return top.getInteger();
	}

	/**
	 * Returns true if there are still some integers in the nested list and
	 * false otherwise.
	 */
	bool hasNext() {
		flattenTop();
		return !stk.empty();
	}
};

/**
 * Test cases
 */
int main(void) {
	vector<NestedInteger> nestedList;
	//NestedIterator i({ NestedInteger(1) });

	// test case 1
	nestedList = { NestedInteger({ NestedInteger(1), NestedInteger(1) }) };
	nestedList.push_back(NestedInteger(2));
	nestedList.push_back(NestedInteger({ NestedInteger(1), NestedInteger(1) }));
	NestedIterator i(nestedList);
	std::cout << "[";
	while (i.hasNext()) std::cout << i.next() << ',';
	std::cout << "\b]" << std::endl;

	// test case 2
	nestedList = { NestedInteger(6) };
	nestedList = { NestedInteger(4), nestedList };
	nestedList = { NestedInteger(1), nestedList };
	i = NestedIterator(nestedList);
	std::cout << "[";
	while (i.hasNext()) std::cout << i.next() << ',';
	std::cout << "\b]" << std::endl;

	nestedList = { {} };
	i = NestedIterator(nestedList);
	std::cout << "[";
	while (i.hasNext()) std::cout << i.next() << ',';
	std::cout << "\b]" << std::endl;

	return 0;
}