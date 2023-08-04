/*******************************************************************************
 * 0139-Word_Break.cpp
 * Billy.Ljm
 * 04 August 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/word-break/
 *
 * Given a string s and a dictionary of strings wordDict, return true if s can
 * be segmented into a space-separated sequence of one or more dictionary words.
 *
 * Note that the same word in the dictionary may be reused multiple times in the
 * segmentation.
 *
 * ===========
 * My Approach
 * ===========
 * We have to match the whole word. Thus, we can start matching from the front,
 * and recursively match the remaining substring. We can also use memoisation
 * to avoid matching the same substring multiple times.
 *
 * This has a time complexity of O(n * m), and a space complexity of O(n),
 * where n and m are the length of the word and wordDict respectively.
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
	for (int i = 0; i < v.size(); i++) {
		os << v[i] << ",";
	}
	os << "\b]";
	return os;
}

/**
 * Solution
 */
class Solution {
	unordered_map<string, bool> memo; // memo[substr] = true/false

public:
	bool wordBreak(string s, vector<string>& wordDict) {
		// base case
		if (s == "") return true;
		// if memoised, return
		else if (memo.find(s) != memo.end()) return memo[s];

		// try to match word
		for (string word : wordDict) {
			if (s.substr(0, word.length()) == word) {
				if (wordBreak(
					s.substr(word.length(), s.length() - word.length()),
					wordDict)) {
					memo.insert({ s, true });
					return true;
				}
			}
		}

		// no word matches
		memo.insert({ s, false });
		return false;
	}
};

/**
 * Test cases
 */
int main(void) {
	Solution sol;
	string s;
	vector<string> wordDict;

	// test case 1
	s = "leetcode";
	wordDict = { "leet", "code" };
	std::cout << "wordBreak(" << s << ", " << wordDict << ") = ";
	std::cout << std::boolalpha << sol.wordBreak(s, wordDict) << std::endl;

	// test case 2
	s = "applepenapple";
	wordDict = { "apple", "pen" };
	std::cout << "wordBreak(" << s << ", " << wordDict << ") = ";
	std::cout << std::boolalpha << sol.wordBreak(s, wordDict) << std::endl;

	// test case 3
	s = "catsandog";
	wordDict = { "cats", "dog", "sand", "and", "cat" };
	std::cout << "wordBreak(" << s << ", " << wordDict << ") = ";
	std::cout << std::boolalpha << sol.wordBreak(s, wordDict) << std::endl;

	return 0;
}