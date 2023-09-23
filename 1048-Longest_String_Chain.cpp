/*******************************************************************************
 * 1048-Longest_String_Chain.cpp
 * Billy.Ljm
 * 23 September 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/longest-string-chain/
 *
 * You are given an array of words where each word consists of lowercase English
 * letters.
 *
 * wordA is a predecessor of wordB if and only if we can insert exactly one
 * letter anywhere in wordA without changing the order of the other characters
 * to make it equal to wordB.
 *
 * For example, "abc" is a predecessor of "abac", while "cba" is not a
 * predecessor of "bcad".
 *
 * A word chain is a sequence of words [word1, word2, ..., wordk] with k >= 1,
 * where word1 is a predecessor of word2, word2 is a predecessor of word3, and
 * so on. A single word is trivially a word chain with k == 1.
 *
 * Return the length of the longest possible word chain with words chosen from
 * the given list of words.
 *
 * ===========
 * My Approach
 * ===========
 * Every predecessor will be one character shorter than its successor. Thus, we
 * can iterate through the strings of ascending lengths, calculating the longest
 * word chain ending with each string. If the new string has predecessors, then
 * its maximum chain length will be the max of its predecessors plus one.
 * Otherwise the new string will form a single-element chain.
 * 
 * This has a time complexity of O(n^2), and a space complexity of O(n), where
 * n is the number of words
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
private:
	/**
	 * Check is pred is a predcessor of succ
	 */
	bool checkPred(string pred, string succ) {
		int offset = 0;
		for (int i = 0; i < pred.length(); i++) {
			while (pred[i] != succ[i + offset]) {
				offset++;
				if (offset > 1) return false;
			}
		}
		return true;
	}

public:
	int longestStrChain(vector<string>& words) {
		// sort in asceding string length
		sort(words.begin(), words.end(),
			[](const string lhs, const string rhs) {
				return lhs.length() < rhs.length();
			});

		// count max chain ending with each char
		vector<int> maxchain(words.size(), 1);
		for (int i = 1; i < words.size(); i++) {
			int maxpred = 0; // max chain length of predcessors
			// find all possible predecessors
			for (int j = i - 1; j >= 0; j--) {
				if (words[j].length() < words[i].length() - 1) break;
				else if (words[j].length() == words[i].length()) continue;
				if (checkPred(words[j], words[i])) {
					maxchain[i] = max(maxchain[i], maxchain[j] + 1);
				}
			}
		}

		// find max chain ending with any char
		return *max_element(maxchain.begin(), maxchain.end());
	}
};

/**
 * Test cases
 */
int main(void) {
	Solution sol;
	vector<string> words;

	// test case 1
	words = { "a","b","ba","bca","bda","bdca" };
	std::cout << "longestStrChain(" << words << ") = ";
	std::cout << sol.longestStrChain(words) << std::endl;

	// test case 2
	words = { "xbc","pcxbcf","xb","cxbc","pcxbc" };
	std::cout << "longestStrChain(" << words << ") = ";
	std::cout << sol.longestStrChain(words) << std::endl;

	// test case 3
	words = { "abcd","dbqca" };
	std::cout << "longestStrChain(" << words << ") = ";
	std::cout << sol.longestStrChain(words) << std::endl;

	return 0;
}