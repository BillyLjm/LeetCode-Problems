/*******************************************************************************
 * 0225-Implement_Stack_Using_Queues.cpp
 * Billy.Ljm
 * 28 August 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/implement-stack-using-queues/
 *
 * Implement a last-in-first-out (LIFO) stack using only two queues. The
 * implemented stack should support all the functions of a normal stack
 * (push, top, pop, and empty).
 *
 * Implement the MyStack class:
 * - void push(int x) Pushes element x to the top of the stack.
 * - int pop() Removes the element on the top of the stack and returns it.
 * - int top() Returns the element on the top of the stack.
 * - boolean empty() Returns true if the stack is empty, false otherwise.
 *
 * ===========
 * My Approach
 * ===========
 * A stack is a LIFO data structure, so we'll use a double-ended queue to
 * implement it.
 *
 * This has a time complexity of O(1) for all methods, and a space complexity of
 * O(n), where n is the size of the stack.
 ******************************************************************************/

#include <iostream>
#include <vector>
#include <queue>

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
 * Solution
 */
class MyStack {
	deque<int> dq;

public:
	MyStack() {
		dq = deque<int>();
	}

	void push(int x) {
		dq.push_front(x);
	}

	int pop() {
		int out = dq.front();
		dq.pop_front();
		return out;
	}

	int top() {
		return dq.front();
	}

	bool empty() {
		return dq.empty();
	}
};

/**
 * Test cases
 */
int main(void) {
	// test case 1
	MyStack* obj = new MyStack();
	obj->push(1);
	obj->push(2);
	std::cout << obj->top() << ", ";
	std::cout << obj->pop() << ", ";
	std::cout << std::boolalpha << obj->empty() << std::endl;

	return 0;
}