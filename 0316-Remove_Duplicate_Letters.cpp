/*******************************************************************************
 * 0316-Remove_Duplicate_Letters.cpp
 * Billy.Ljm
 * 26 September 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/remove-duplicate-letters/
 *
 * Given a string s, remove duplicate letters so that every letter appears once
 * and only once. You must make sure your result is the smallest in
 * lexicographical order among all possible results.
 *
 * ===========
 * My Approach
 * ===========
 * If a letter is the last occurrence of the character, then we have to include
 * it. Otherwise, if it is not the last occurrence, then we add it temporarily.
 * However, we might have to pop this characters out and append the later
 * occurrences if a lexicographically smaller character comes along.
 *
 * This has a time complexity of O(n^2), and a space complexity of O(n), where n
 * is the length of the string.
 ******************************************************************************/

#include <iostream>
#include <vector>
#include <map>
#include <set>

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
	string removeDuplicateLetters(string s) {
		// count letters
		map<char, int> count;
		for (char c : s) {
			if (count.find(c) != count.end()) count[c]++;
			else count[c] = 1;
		}

		// form output
		string out;
		set<char> visited;
		for (char c : s) {
			// append any new chars
			if (visited.find(c) == visited.end()) {
				// remove any lexographically larger chars with later occurences
				while (out.size() > 0 and out.back() > c and count[out.back()] != 0) {
					visited.erase(out.back());
					out.pop_back();
				}
				out += c;
				visited.insert(c);
			}
			// update remaining count
			count[c]--;
		}
		return out;
	}
};

/**
 * Test cases
 */
int main(void) {
	Solution sol;
	string s;

	// test case 1
	s = "bcabc";
	std::cout << "removeDuplicateLetters(" << s << ") = ";
	std::cout << sol.removeDuplicateLetters(s) << std::endl;

	// test case 2
	s = "cbacdcbc";
	std::cout << "removeDuplicateLetters(" << s << ") = ";
	std::cout << sol.removeDuplicateLetters(s) << std::endl;

	return 0;
}