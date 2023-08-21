/*******************************************************************************
 * 0459-Repeated_Substring_Pattern.cpp
 * Billy.Ljm
 * 21 August 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/repeated-substring-pattern/
 *
 * Given a string s, check if it can be constructed by taking a substring of it
 * and appending multiple copies of the substring together.
 *
 * ===========
 * My Approach
 * ===========
 * We just have to iterate through each substring length. If the substring
 * length is not a divisor of the string length, then we can skip.
 *
 * This has a time complexity of O(n^2), and a space complexity of O(n), where
 * n is the length of the string.
 ******************************************************************************/

#include <iostream>
#include <vector>
#include <set>
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
class Solution {
public:
	bool repeatedSubstringPattern(string s) {
		for (int i = 1; i <= s.size() / 2; i++) {
			if (s.size() % i != 0) continue;
			for (int j = 0; j < s.size(); j++) {
				if (s[j] != s[j % i]) goto nextiter;
			}
			return true;
			nextiter: continue;
		}
		return false;
	}
};

/**
 * Test cases
 */
int main(void) {
	Solution sol;
	string s;

	// test case 1
	s = "abab";
	std::cout << "repeatedSubstringPattern(" << s << ") = ";
	std::cout << std::boolalpha << sol.repeatedSubstringPattern(s) << std::endl;

	// test case 2
	s = "aba";
	std::cout << "repeatedSubstringPattern(" << s << ") = ";
	std::cout << std::boolalpha << sol.repeatedSubstringPattern(s) << std::endl;

	// test case 3
	s = "abcabcabcabc";
	std::cout << "repeatedSubstringPattern(" << s << ") = ";
	std::cout << std::boolalpha << sol.repeatedSubstringPattern(s) << std::endl;

	return 0;
}