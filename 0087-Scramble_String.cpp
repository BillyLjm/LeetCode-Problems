/*******************************************************************************
 * 0087-Scramble_String.cpp
 * Billy.Ljm
 * 30 Mar 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/scramble-string/
 * We can scramble a string s to get a string t using the following algorithm:
 * - If the length of the string is 1, stop.
 * - If the length of the string is > 1, do the following:
 *   > Split the string into two non-empty substrings at a random index,
 *   i.e., if the string is s, divide it to x and y where s = x + y.
 *   > Randomly decide to swap the two substrings or to keep them in the same
 *   order. i.e., after this step, s may become s = x + y or s = y + x.
 *   > Apply step 1 recursively on each of the two substrings x and y.
 * Given two strings s1 and s2 of the same length, return true if s2 is a
 * scrambled string of s1, otherwise, return false.
 *
 * ===========
 * My Approach
 * ===========
 * We have to check all possibilities of the scrambling. However, splitting the
 * string at 8 then 2 and splitting at 4 then 2 will overlap since both compare
 * string[:2]. Thus, we can avoid recalculating it by using dynamic programming
 * where dp[i][j][k] is true if s1[i:i+k] is a scrambled string of s2[j:j+k].
 *
 * This has time complexity of O(n^4) and space complexity of O(n^3), where n is
 * the length of the strings.
 ******************************************************************************/

#include <iostream>
#include <string>
#include <vector>

class Solution {
public:
	/**
	 * Checks if two strings are scrambled versions of each other, where the
	 * scrambling corresponds to bisecting and swapping the order of substrings.
	 *
	 * @param s1 string to compare against s2
	 * @param s2 string to compare against s1
	 *
	 * @return true if s1 and s2 are scrambled versions of each other
	 */
	bool isScramble(std::string s1, std::string s2) {
		size_t n = s1.length();

		// dp[i][j][k] = is s1[i:i+k] is a scrambled string of s2[j:j+k].
		std::vector<std::vector<std::vector<bool>>> dp(n,
			std::vector< std::vector<bool>>(n, std::vector<bool>(n, false)));

		// base case
		for (size_t i = 0; i < n; i++) {
			for (size_t j = 0; j < n; j++) {
				dp[i][j][0] = s1[i] == s2[j];
			}
		}

		// dynamic programming
		for (size_t k = 1; k < n; k++) { // length of substring
			for (size_t i = 0; i < n - k; i++) { // starting index of s1
				for (size_t j = 0; j < n - k; j++) { // starting index of s2
					for (size_t l = 0; l < k; l++) { // index to split at
						// no swap
						dp[i][j][k] = dp[i][j][k] ||
							(dp[i][j][l] && dp[i + l + 1][j + l + 1][k - l - 1]);
						// swap
						dp[i][j][k] = dp[i][j][k] ||
							(dp[i][j + k - l][l] && dp[i + l + 1][j][k - l - 1]);
						// stop splitting if found
						if (dp[i][j][k]) {
							break;
						}
					}
				}
			}
		}

		return dp[0][0][n - 1];
	}
};

/**
 * Test cases
 */
int main(void) {
	Solution sol;
	std::string s1, s2;

	// test case 1
	s1 = "great";
	s2 = "rgeat";
	std::cout << std::boolalpha << "isScramble(" << s1 << ", " << s2 << ") = "
		<< sol.isScramble(s1, s2) << std::endl;

	// test case 2
	s1 = "abcde";
	s2 = "caebd";
	std::cout << std::boolalpha << "isScramble(" << s1 << ", " << s2 << ") = "
		<< sol.isScramble(s1, s2) << std::endl;

	// test case 3
	s1 = "a";
	s2 = "a";
	std::cout << std::boolalpha << "isScramble(" << s1 << ", " << s2 << ") = "
		<< sol.isScramble(s1, s2) << std::endl;

	return 0;
}