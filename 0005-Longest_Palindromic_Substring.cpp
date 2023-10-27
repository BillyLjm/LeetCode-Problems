/*******************************************************************************
 * 0005-Longest_Palindromic_Substring.cpp
 * Billy.Ljm
 * 27 October 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/longest-palindromic-substring/
 * 
 * Given a string s, return the longest palindromic substring in s.
 * 
 * ===========
 * My Approach
 * ===========
 * We will use Manacher's algorithm, where we essentially iterate through each
 * index and find the longest palindrome centred at each index. Additionally,
 * we remember the longest identified palindrome which stretches to the furthest
 * index. If the next iteration's centre index is within this long palindrome,
 * then this centre was already seen before as '*a*...|...*a*', and its minimal
 * lps within the bounds of the long palindrome is already known.
 *
 * This has a time complexity of O(n), and space complexity of O(n), where n is
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
	string longestPalindrome(string s) {
		string out = s.substr(0,1); // longest palindrome output
		vector<int> lps; // longest prefix suffix
		int center, radius; // centre and radius of rightmost palindrome

		// consider odd-length palindromes
		lps = vector<int>(s.length(), 0);
		center = 0;
		radius = 0;
		for (int i = 0; i < s.length(); i++) {
			// get minimum lps based on rightmost palindrome
			if (i < center + radius) {
				lps[i] = min(center + radius - i, lps[2 * center - i]);
			}
			else lps[i] = 0;
			// get maximum lps by including furhter letters
			while (i - lps[i] - 1 >= 0 && i + lps[i] + 1 < s.length() &&
				s[i - lps[i] - 1] == s[i + lps[i] + 1]) {
				lps[i]++;
			}
			// update output longest palindrome
			if (lps[i] > out.size() / 2) {
				out = s.substr(i - lps[i], lps[i] * 2 + 1);
			}
			// update rightmost palindrome
			if (i + lps[i] > center + radius) {
				center = i;
				radius = lps[i];
			}
		}

		// consider even-length palindromes
		lps = vector<int>(s.length() - 1, 0);
		center = 0;
		radius = 0;
		for (int i = 0; i < s.length() - 1; i++) {
			// get minimum lps based on rightmost palindrome
			if (i < center + radius) {
				lps[i] = min(center + radius - i, lps[2 * center - i]);
			}
			else lps[i] = 0;
			// get maximum lps by including further letters
			while (i - lps[i] >= 0 && i + lps[i] + 1 < s.length() &&
				s[i + lps[i] + 1] == s[i - lps[i]]) {
				lps[i]++;
			}
			// update output longest palindrome
			if (lps[i] > out.size() / 2) {
				out = s.substr(i - lps[i] + 1, lps[i] * 2);
			}
			// update rightmost palindrome
			if (i + lps[i] > center + radius) {
				center = i;
				radius = lps[i];
			}
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
	s = "babad";
	std::cout << "longestPalindrome(" << s << ") = ";
	std::cout << sol.longestPalindrome(s) << std::endl;

	// test case 2
	s = "cbbd";
	std::cout << "longestPalindrome(" << s << ") = ";
	std::cout << sol.longestPalindrome(s) << std::endl;

	return 0;
}