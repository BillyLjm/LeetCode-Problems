/*******************************************************************************
 * 1647-Minimum_Deletions_to_Make_Character_Frequencies_Unique.cpp
 * Billy.Ljm
 * 12 September 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/minimum-deletions-to-make-character-frequencies-unique/
 *
 * A string s is called good if there are no two different characters in s that
 * have the same frequency.
 *
 * Given a string s, return the minimum number of characters you need to delete
 * to make s good.
 *
 * ===========
 * My Approach
 * ===========
 * We just have to count the frequency of each character in the string. Then,
 * we iterate through the frequencies is descending order, deleting each char
 * and reducing its frequency by 1 if its frequency is not smaller than the
 * previous one.
 *
 * This has a time complexity of O(n), and a space complexity of O(1), where
 * n is the length of the string
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
	int minDeletions(string s) {
		// count frequencies
		vector<int> freq(26, 0);
		for (char c : s) {
			freq[c - 'a']++;
		}

		// sort frequencies
		sort(freq.begin(), freq.end(), greater<int>());

		// delete until frequencies is strictly decreasing
		int deletions = 0;
		for (int i = 1; i < freq.size(); i++) {
			while (freq[i] >= freq[i - 1] and freq[i] > 0) {
				deletions++;
				freq[i]--;
			}
		}

		return deletions;
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
	std::cout << "minDeletions(" << s << ") = ";
	std::cout << sol.minDeletions(s) << std::endl;

	// test case 2
	s = "aaabbbcc";
	std::cout << "minDeletions(" << s << ") = ";
	std::cout << sol.minDeletions(s) << std::endl;

	// test case 3
	s = "ceabaacb";
	std::cout << "minDeletions(" << s << ") = ";
	std::cout << sol.minDeletions(s) << std::endl;

	return 0;
}