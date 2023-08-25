/*******************************************************************************
 * 0097-Interleaving_String.cpp
 * Billy.Ljm
 * 25 August 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/interleaving-string/
 *
 * Given strings s1, s2, and s3, find whether s3 is formed by an interleaving of
 * s1 and s2.
 *
 * An interleaving of two strings s and t is a configuration where s and t are
 * divided into n and m substrings respectively, such that:
 * - s = s1 + s2 + ... + sn
 * - t = t1 + t2 + ... + tm
 * - |n - m| <= 1
 * - The interleaving is s1 + t1 + s2 + t2 + s3 + t3 + ... or
 *   t1 + s1 + t2 + s2 + t3 + s3 + ...
 *
 * ===========
 * My Approach
 * ===========
 * This can be done recursively  since f(s1, s2, s3) = f(s1[1:], s2, s3[1:]) &&
 * f(s1, s2[1:], s3[1:]). We may need the same recursion multiple times since
 * choosing the char from s1 then s2, will be identical to choosing from s2 then
 * s1. Thus, we will use memoisation to make it more efficient
 *
 * This has a time complexity of O(n*m*k), and a space complexity of O(n*m*k), 
 * where n, m, and k is the length of s1, s2, and s3 respectively.
 ******************************************************************************/

#include <iostream>
#include <vector>
#include <map>
#include <tuple>

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
	map<tuple<int, int, int>, bool> memo; // for memoisation
	string s1, s2, s3; // pass by reference

public:
	bool isInterleave(string s1, string s2, string s3) {
		memo.clear();
		this->s1 = s1;
		this->s2 = s2;
		this->s3 = s3;
		return recurse(0, 0, 0);
	}

private:
	bool recurse(int i1, int i2, int i3) {
		tuple<int, int, int> memoidx = make_tuple(i1, i2, i3);
		// base case
		if (i1 == s1.size() and i2 == s2.size() and i3 == s3.size()) {
			return true;
		}
		else if ((i1 >= s1.size() and i2 >= s2.size()) or i3 >= s3.size()) {
			return false;
		}
		// if memoised, return
		else if (memo.find(memoidx) != memo.end()) {
			return memo[memoidx];
		}
		// else recurse
		else {
			memo[memoidx] = false;
			if (s1[i1] == s3[i3]) {
				memo[memoidx] = memo[memoidx] or recurse(i1 + 1, i2, i3 + 1);
			}
			if (s2[i2] == s3[i3]) {
				memo[memoidx] = memo[memoidx] or recurse(i1, i2 + 1, i3 + 1);
			}
			return memo[memoidx];
		}
	}
};

/**
 * Test cases
 */
int main(void) {
	Solution sol;
	string s1, s2, s3;

	// test case 1
	s1 = "aabcc";
	s2 = "dbbca";
	s3 = "aadbbcbcac";
	std::cout << "isInterleave(" << s1 << ", " << s2 << ", " << s3 << ") = ";
	std::cout << std::boolalpha << sol.isInterleave(s1, s2, s3) << std::endl;

	// test case 2
	s1 = "aabcc";
	s2 = "dbbca";
	s3 = "aadbbbaccc";
	std::cout << "isInterleave(" << s1 << ", " << s2 << ", " << s3 << ") = ";
	std::cout << std::boolalpha << sol.isInterleave(s1, s2, s3) << std::endl;

	// test case 3
	s1 = "";
	s2 = "";
	s3 = "";
	std::cout << "isInterleave(" << s1 << ", " << s2 << ", " << s3 << ") = ";
	std::cout << std::boolalpha << sol.isInterleave(s1, s2, s3) << std::endl;

	return 0;
}