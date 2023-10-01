/*******************************************************************************
 * 0557-Reverse_Words_in_a_String_III.cpp
 * Billy.Ljm
 * 01 October 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/reverse-words-in-a-string-iii/
 *
 * Given a string s, reverse the order of characters in each word within a
 * sentence while still preserving whitespace and initial word order.
 *
 * ===========
 * My Approach
 * ===========
 * We can iterate through each character to find the start and end of each word.
 * Then, we just have to swap the ordering within each word.
 *
 * This has a time complexity of O(n), and a space complexity of O(1), where n
 * is the size of the string.
 ******************************************************************************/

#include <iostream>
#include <vector>
#include <algorithm>

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
	string reverseWords(string s) {
		int start = 0, end = 0;

		while (end < s.size()) {
			// find end of word
			if (s[end] != ' ') {
				end++;
			}
			else {
				// swap odering
				for (int i = 0; start + i < end - 1 - i; i++) {
					swap(s[start + i], s[end - 1 - i]);
				}
				// prep for next word
				end++;
				start = end;
			}
		}

		// swap last word
		for (int i = 0; start + i < end - 1 - i; i++) {
			swap(s[start + i], s[end - 1 - i]);
		}

		return s;
	}
};

/**
 * Test cases
 */
int main(void) {
	Solution sol;
	string s;

	// test case 1
	s = "Let's take LeetCode contest";
	std::cout << "reverseWords(" << s << ") = ";
	std::cout << sol.reverseWords(s) << std::endl;

	// test case 2
	s = "God Ding";
	std::cout << "reverseWords(" << s << ") = ";
	std::cout << sol.reverseWords(s) << std::endl;

	return 0;
}