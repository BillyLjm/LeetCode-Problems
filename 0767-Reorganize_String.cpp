/*******************************************************************************
 * 0767_Reorganize_String.cpp
 * Billy.Ljm
 * 23 August 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/reorganize-string/
 *
 * Given a string s, rearrange the characters of s so that any two adjacent
 * characters are not the same.
 *
 * Return any possible rearrangement of s or return "" if not possible.
 *
 * ===========
 * My Approach
 * ===========
 * We can first sort the string so that identical characters are adjacent to
 * each other. Then, we split the sorted string into two halves and braid them
 * in an alternating fashion of s[0],s[n/2],s[1],s[n/2+1],... If none of the
 * characters stretches across the two halves, then this string would have no
 * identical and adjacent elements.
 *
 * One thing to note is that if the length of the string is an odd number, then
 * it'll have one more odd indices than even indices. Thus, we would want to put
 * the most frequent char in the odd index, so it is less likely to overflow.
 *
 * This has a time complexity of O(n), and a space complexity of O(n), where n
 * is the length of the string.
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
	string reorganizeString(string s) {
		// count occurences
		vector<int> count(26, 0);
		for (char c : s) {
			count[c - 'a']++;
		}

		// find max element
		int maxidx, maxcount = 0;
		for (int i = 0; i < count.size(); i++) {
			if (count[i] > maxcount) {
				maxcount = count[i];
				maxidx = i;
			}
		}

		// check if any overflow
		if (maxcount > (s.size() + 1) / 2) return "";

		// create string
		vector<char> out(s.size());
		int idx = 0;
		// put most frequent element in odd indices (which is longer)
		while (count[maxidx] > 0) {
			out[idx] = maxidx + 'a';
			count[maxidx]--;
			idx = idx + 2;
			if (idx >= s.size()) idx = 1;
		}
		// fill up rest of string
		for (int i = 0; i < count.size(); i++) {
			while (count[i] > 0) {
				out[idx] = i + 'a';
				count[i]--;
				idx = idx + 2;
				if (idx >= s.size()) idx = 1;
			}
		}

		return string(out.begin(), out.end());
	}
};

/**
 * Test cases
 */
int main(void) {
	Solution sol;
	string s;

	// test case 1
	s = "aab";
	std::cout << "reorganizeString(" << s << ") = ";
	std::cout << sol.reorganizeString(s) << std::endl;

	// test case 2
	s = "aaab";
	std::cout << "reorganizeString(" << s << ") = ";
	std::cout << sol.reorganizeString(s) << std::endl;

	return 0;
}