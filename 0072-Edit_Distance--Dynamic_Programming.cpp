/*******************************************************************************
 * 72-Edit_Distance--Dynamic_Programming.cpp
 * Billy.Ljm
 * 26 Feb 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/edit-distance/description/
 * Given two strings word1 and word2, return the minimum number of operations
 * (insert, delete, replace) required to convert word1 to word2.
 *
 * ===========
 * My Approach
 * ===========
 * The brute force solution is to try every possbile operation for each letter
 * of one of the words: do nothing, replace, delete, and insert (aka delete
 * from the other letter). This is most intuitively implemented using
 * recursion, and has a time complexity of O(4^n) and space complexity
 * O(n), where n is the length of the shorter word.
 *
 * However, the recursion layers have significant overlap, with multiple paths
 * that converge back into the same path. For example, inserting then deleting,
 * deleting then inserting, and replacing are identical. This would suggest an
 * optimisation strategy using memoisation or something similar.
 *
 * But if we probe more, we can further realise that is optimal substructure to
 * the problem. This allows the solution to be phrased as filling up a matrix as
 * detailed in https://leetcode.com/problems/edit-distance/editorial/.
 *
 * Thus, a dynamic programming approach will be optimal. We find the minimum
 * moves between small segments of both words, and use those results to do the
 * same of increasingly longer segments of words. These longer and shorter
 * segments will be related by the given operations: do nothing, replace,
 * and delete, insert (multiples).
 *
 * The time complexity will be O(m*n), and the space complexity will be O(m),
 * where n and m are the lengths of the longer and shorter words respectively.
 *
 * ====
 * Misc
 * ====
 * This has the same time complexity scaling as memoisation at O(m*n). But
 * practically on LeetCode, dynamic programming seems to be faster (10ms)
 * than memoisation (60ms). I presume this is because it avoids the overhead
 * from recursively calling functions.
 *
 * This has better space complexity at O(m) as compared to memoisation at O(m*n)
 * because it exploits the substructure of the problem to only remember one
 * iteration, instead of all possible subproblems. On LeetCode, memoisation uses
 * 80 MB as compared to dynamic programming's 7 MB.
 ******************************************************************************/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

class Solution {
public:
	/**
	 * Given two strings word1 and word2, return the minimum number of
	 * operations (insert, delete, replace) required to convert word1 to word2.
	 *
	 * @param word1 word to convert into word2
	 * @param word2 word to convert into word1
	 *
	 * @return minimum number of operations to convert word1 into word2
	 */
	int minDistance(std::string word1, std::string word2) {
		// make word2 the shorter word
		size_t n = word1.length();
		size_t m = word2.length();
		if (n < m) {
			word1.swap(word2);
			std::swap(n, m);
		}

		// trivial case
		if (n == 0 or m == 0) {
			return n + m;
		}

		// bulk cases
		else {
			// to store subproblem answers
			std::vector<unsigned int> dp_prev(m + 1); // word1[:i-1] to word2[:j]
			std::vector<unsigned int> dp_curr(m + 1); // word1[:i] to word2[:j]

			// manually do 1st iteration, word1[:1] to word2[:j]
			// note: this is to skip the initilisation loop for word1[:0]
			dp_curr[0] = 1;
			int counter = 1;
			for (int j = 1; j <= m; j++) {
				if (word1[0] == word2[j - 1]) {
					counter--;
				}
				dp_curr[j] = counter;
				counter++;
			}

			// iteratively calculate bigger subproblems
			// note: we only remember 2 iterations, to minimise space complexity
			for (int i = 2; i <= n; i++) {
				dp_curr.swap(dp_prev); // remember only previous iteration
				for (int j = 0; j <= m; j++) {
					// empty word2, just copy whole word1
					if (j == 0) {
						dp_curr[j] = i;
					}
					// last chars match, same ops as word1[:i-1] to word2[:j-1]
					else if (word1[i - 1] == word2[j - 1]) { // indexing from 0
						dp_curr[j] = dp_prev[j - 1];
					}
					else {
						dp_curr[j] = std::min({
							// delete from word2 (or insert into word1)
							dp_curr[j - 1] + 1,
							// insert into word2 (or delete from word1)
							dp_prev[j - 1] + 1,
							// replace into word2 from word1 (or vice versa)
							dp_prev[j] + 1
							});
					}
				}
			}

			return dp_curr[m];
		}
	};
};


/**
 * Test Cases
 */
int main() {
	Solution sol;
	std::cout << "\"horse\" <-> \"ros\" takes " <<
		sol.minDistance("horse", "ros") << " operations\n";
	std::cout << "\"intention\" <-> \"execution\" takes " <<
		sol.minDistance("intention", "execution") << " operations\n";
	return 0;
}