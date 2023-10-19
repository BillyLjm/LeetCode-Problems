/*******************************************************************************
 * 0844-Backspace_String_Compare.cpp
 * Billy.Ljm
 * 19 October 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/backspace-string-compare/
 *
 * Given two strings s and t, return true if they are equal when both are typed
 * into empty text editors. '#' means a backspace character.
 *
 * Note that after backspacing an empty text, the text will continue empty.
 *
 * ===========
 * My Approach
 * ===========
 * We will just maintain two pointers for the two characters which has to be
 * compared. Additionally, we can iterate through the string in reverse so that
 * the backspace becomes a skip, only affecting characters that are yet to be
 * iterated through.
 *
 * This has a time complexity of O(n), and space complexity of O(1), where n is
 * the length of the string.
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
 * Solution
 */
class Solution {
public:
	bool backspaceCompare(string s, string t) {
		int ids = s.length() - 1, idt = t.length() - 1; // index of s and t
		int tmp;

		while (true) {
			// parse backspaces in s
			tmp = 0;
			while (ids >= 0 && (s[ids] == '#' || tmp > 0)) {
				if (s[ids] == '#') tmp++;
				else tmp--;
				ids--;
			}

			// prase backspaces in t
			tmp = 0;
			while (idt >= 0 && (t[idt] == '#' || tmp > 0)) {
				if (t[idt] == '#') tmp++;
				else tmp--;
				idt--;
			}

			// compare characters
			cout << ids << idt << endl;
			if (ids < 0 && idt < 0) return true;
			else if (ids < 0 || idt < 0) return false;
			else if (s[ids] != t[idt]) return false;
			else { // current char passes
				ids--;
				idt--;
			}
		}
	}
};

/**
 * Test cases
 */
int main(void) {
	Solution sol;
	string s, t;

	// test case 1
	s = "ab#c";
	t = "ad#c";
	std::cout << "backspaceCompare(" << s << "," << t << ") = ";
	std::cout << std::boolalpha << sol.backspaceCompare(s, t) << std::endl;

	// test case 2
	s = "ab##";
	t = "c#d#";
	std::cout << "backspaceCompare(" << s << "," << t << ") = ";
	std::cout << std::boolalpha << sol.backspaceCompare(s, t) << std::endl;

	// test case 3
	s = "a#c";
	t = "b";
	std::cout << "backspaceCompare(" << s << "," << t << ") = ";
	std::cout << std::boolalpha << sol.backspaceCompare(s, t) << std::endl;

	return 0;
}