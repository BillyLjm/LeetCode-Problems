/*******************************************************************************
 * 0020-Valid_Parentheses.cpp
 * Billy.Ljm
 * 10 Apr 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/valid-parentheses/
 * Given a string s containing just the characters '(', ')', '{', '}', '[' and
 * ']', determine if the input string is valid.
 *
 * An input string is valid if:
 * - Open brackets must be closed by the same type of brackets.
 * - Open brackets must be closed in the correct order.
 * - Every close bracket has a corresponding open bracket of the same type.
 *
 * ===========
 * My Approach
 * ===========
 * We can use a LIFO stack to keep track of the opening brackets. Then, if we
 * encounter a closing bracket, we just check it against the top of the stack.
 *
 * This has a time complexity of O(n) and space complexity of O(n), where n is
 * the length of the string.
 ******************************************************************************/

#include <iostream>
#include <string>
#include <stack>

class Solution {
public:
	bool isValid(std::string s) {
		std::stack<char> stack;

		for (char c : s) {
			// if open bracket, push to stack
			if (c == '(' || c == '[' || c == '{') {
				stack.push(c);
			}
			// if close bracket, check w/ top of stack
			else if (c == ')') {
				if (stack.empty() || stack.top() != '(') {
					return false;
				}
				stack.pop();
			}
			else if (c == ']') {
				if (stack.empty() || stack.top() != '[') {
					return false;
				}
				stack.pop();
			}
			else if (c == '}') {
				if (stack.empty() || stack.top() != '{') {
					return false;
				}
				stack.pop();
			}
		}

		// check if any open brackets remaining
		return stack.empty();
	}
};

/**
 * Test cases
 */
int main(void) {
	Solution sol;
	std::string s;

	// test case 1
	s = "()";
	std::cout << std::boolalpha << "isValid(" << s << ") = " << sol.isValid(s)
		<< std::endl;

	// test case 2
	s = "()[]{}";
	std::cout << std::boolalpha << "isValid(" << s << ") = " << sol.isValid(s)
		<< std::endl;

	// test case 3
	s = "(]";
	std::cout << std::boolalpha << "isValid(" << s << ") = " << sol.isValid(s)
		<< std::endl;

	return 0;
}