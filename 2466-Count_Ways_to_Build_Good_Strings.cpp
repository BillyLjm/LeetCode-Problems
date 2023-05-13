/*******************************************************************************
 * 2466-Count_Ways_to_Build_Good_Strings.cpp
 * Billy.Ljm
 * 13 May 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/count-ways-to-build-good-strings/
 *
 * Given the integers zero, one, low, and high, we can construct a string by
 * starting with an empty string, and then at each step perform either of the
 * following:
 *
 * - Append the character '0' zero times.
 * - Append the character '1' one times.
 *
 * This can be performed any number of times.
 *
 * A good string is a string constructed by the above process having a length
 * between low and high (inclusive).

 * Return the number of different good strings that can be constructed
 * satisfying these properties. Since the answer can be large, return it modulo
 * 10^9 + 7.
 *
 * ===========
 * My Approach
 * ===========
 * We will use dynamic programming to find the number of constructable strings
 * of increasing lengths. A length of 0 will have 1 string, and a length of n
 * will have dp[i - zero] + dp[i - one] strings, for concatenating  substring
 * '0', and substring '1' respectively.
 *
 * To find the number of good strings which have [low, high] length, we simply
 * have to add dp[low:high]. Noting that its modulo addition.
 *
 * This has a time complexity of O(n) and space complexity of O(n), where n is
 * the value of `high`
 ******************************************************************************/

#include <iostream>
#include <vector>

/**
 * Solution
 */
class Solution {
public:
	/**
	 * Counts the number of strings with lengths between `low` and `high`, which
	 * can be formed from concatenating substrings of length `zero` and `one`.
	 *
	 * @param low minimum length of final string
	 * @param high maximum length of final string
	 * @param zero length of first substring to concatenate
	 * @param one lenght of second substring to concatenate
	 *
	 * @return number of strings that satisfy the conditions described above
	 */
	int countGoodStrings(int low, int high, int zero, int one) {
		int mod = 1e9 + 7; // value to modulo over
		std::vector<int> dp(high + 1); // number of strings of length[i]
		dp[0] = 1;

		// find number of strings (w/ zero, one)
		for (int i = 1; i <= high; i++) {
			dp[i] = i - zero >= 0 ? (dp[i - zero] + dp[i] * 1L) % mod : dp[i];
			dp[i] = i - one >= 0 ? (dp[i - one] + dp[i] * 1L) % mod  : dp[i];
		}

		// find number of good strings (w/ low, high)
		int summ = 0;
		for (int i = low; i <= high; i++) {
			summ = (summ + dp[i] * 1L) % mod;
		}

		return summ;
	}
};

/**
 * Test cases
 */
int main(void) {
	Solution sol;
	int low, high, zero, one;

	// test case 1
	low = 3;
	high = 3;
	zero = 1;
	one = 1;
	std::cout << "countGoodStrings(" << low << "," << high << "," << zero << ","
		<< one << ") = " << sol.countGoodStrings(low, high, zero, one) << std::endl;

	// test case 2
	low = 2;
	high = 3;
	zero = 1;
	one = 2;
	std::cout << "countGoodStrings(" << low << "," << high << "," << zero << ","
		<< one << ") = " << sol.countGoodStrings(low, high, zero, one) << std::endl;

	return 0;
}