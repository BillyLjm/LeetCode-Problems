/*******************************************************************************
 * 2707-Extra_Characters_in_a_String.cpp
 * Billy.Ljm
 * 02 September 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/extra-characters-in-a-string/
 *
 * You are given a 0-indexed string s and a dictionary of words dictionary. You
 * have to break s into one or more non-overlapping substrings such that each
 * substring is present in dictionary. There may be some extra characters in s
 * which are not present in any of the substrings.
 *
 * Return the minimum number of extra characters left over if you break up s
 * optimally.
 *
 * ===========
 * My Approach
 * ===========
 * We can use std::string::find to find the first instance of each substring
 * in the dictionary. Then we just count the number of preceding characters
 * and recursively repeat the process for the subsequent strings. To make it
 * more efficient, we can memoise it.
 *
 * This has a time complexity of O(n*m), and a space complexity of O(n), where
 * n length of the string and m is the length of the dictionary.
 ******************************************************************************/

#include <iostream>
#include <vector>
#include <map>

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
	int minExtraChar(string s, vector<string>& dictionary) {
		map<int, int> memo;
		return recurse(0, s, dictionary, memo);
	}

	int recurse(int start, string& s, vector<string>& dictionary,
		map<int, int>& memo) {
		// base case, string searched
		if (start >= s.size()) {
			return 0;
		}
		// if memoised, return
		else if (memo.find(start) != memo.end()) {
			return memo[start];
		}
		// else recurse
		else {
			int out = s.size() - start;
			int idx; // output of string::find
			for (string substr : dictionary) {
				idx = s.find(substr, start);
				if (idx >= 0) {
					cout << start << substr << idx << endl;
					out = min(out, idx - start +
						recurse(idx + substr.size(), s, dictionary, memo));
				}
			}
			memo[start] = out;
			return memo[start];
		}
	}
};

/**
 * Test cases
 */
int main(void) {
	Solution sol;
	string s;
	vector<string> dictionary;

	// test case 1
	s = "leetscode";
	dictionary = { "leet","code","leetcode" };
	std::cout << "minExtraChar(" << s << "," << dictionary << ") = ";
	std::cout << sol.minExtraChar(s, dictionary) << std::endl;

	// test case 2
	s = "sayhelloworld";
	dictionary = { "hello","world" };
	std::cout << "minExtraChar(" << s << "," << dictionary << ") = ";
	std::cout << sol.minExtraChar(s, dictionary) << std::endl;

	return 0;
}