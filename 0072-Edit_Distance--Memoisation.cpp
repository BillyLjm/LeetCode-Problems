/*******************************************************************************
 * 72-Edit_Distance--Memoisation.cpp
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
 * The brute force solution is to try every possible operation for each letter
 * of one of the words: do nothing, replace, delete, and insert (aka delete
 * from the other letter). This is most intuitively implemented using
 * recursion, and has a time complexity of O(4^n) and space complexity
 * O(n), where n is the length of the shorter word.
 *
 * To optimise it, we can use memoisation instead of plain recursion, since many
 * of the recursions layers overlap. For example, inserting then deleting,
 * deleting then inserting, and replacing are identical. This would reduce the
 * time complexity greatly to O(nm), but increase the space complexity slightly
 * to O(nm) as demonstrated below, where  n and m is the length of the
 * longer and shorter words respectively.
 *
 * ====
 * Misc
 * ====
 * This has the same time complexity scaling as dynamic programming at O(m*n).
 * But practically on LeetCode, memoisation seems to be slower (60ms) than
 * dynamic programming (10ms). I presume this is because memoisation had
 * additional overhead from the recursive function calls.
 *
 * Additionally, memoisation has worse space complexity at O(m*n) as compared to
 * dynamic programming at O(m). This is because it doesn't rely on the
 * substructure of the problem and thus has to remember all the subproblems
 * instead of a subset.
 *
 * On LeetCode, memoisation uses 80 MB as compared to dynamic programming's 7 MB.
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
		size_t n = word1.length();
		size_t m = word2.length();
		std::vector<std::vector<int>> memo(n + 1, std::vector<int>(m + 1, -1));
		return recurse(word1, word2, n, m, memo);
	};

private:
	/**
	 * recursive function to calculate the minimum number of operations to
	 * convert word1[:i] to word2[:j]
	 *
	 * @param word1 word to convert into word2
	 * @param word2 word to convert word1 into
	 * @param i index of word1 which is unconverted
	 * @param j index of word2 which is unconverted
	 * @param memo memoisation memory; memo[i][j] = word1[:i] to word2[:j]
	 *
	 * @return minimum number of operations to convert word1[:i] to word2[:j]
	 */
	int recurse(std::string word1, std::string word2, size_t i, size_t j,
		std::vector<std::vector<int>>& memo) {

		// if memoized, just return
		if (memo[i][j] >= 0) {
			// do nothing
		}

		// base case: one word empty, insert the other word as a whole
		else if (i == 0) {
			memo[i][j] = int(j);
		}
		else if (j == 0) {
			memo[i][j] = int(i);
		}

		// (end) chars match, do nothing and move on for both words
		else if (word1[i - 1] == word2[j - 1]) {
			memo[i][j] = recurse(word1, word2, i - 1, j - 1, memo);
		}

		// chars don't match, recurse all possible operations
		else {
			memo[i][j] = std::min({
				// replace word1[i] to word2[j]
				recurse(word1, word2, i - 1, j - 1, memo) + 1,
				// delete word1[i]
				recurse(word1, word2, i - 1, j, memo) + 1,
				// insert word2[j] before word1[i]
				recurse(word1, word2, i, j - 1, memo) + 1
				// no insert after, since word1[i:] == word2[j:]
				});
		}

		//std::cout << i << "," << j << " takes " << memo[i][j] << " ops\n";
		return memo[i][j];
	};

};

/**
 * Test Cases
 */
int main(void) {
	Solution sol;
	std::cout << "\"horse\" <-> \"ros\" takes " <<
		sol.minDistance("horse", "ros") << " operations\n";
	std::cout << "\"intention\" <-> \"execution\" takes " <<
		sol.minDistance("intention", "execution") << " operations\n";
	return 0;
}