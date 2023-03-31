/*******************************************************************************
 * 1444-Number_of_Ways_of_Cutting_a_Pizza.cpp
 * Billy.Ljm
 * 31 Mar 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/number-of-ways-of-cutting-a-pizza/
 * Given a rectangular pizza represented as a rows x cols matrix containing the
 * following characters: 'A' (an apple) and '.' (empty cell) and given the
 * integer k. You have to cut the pizza into k pieces using k-1 cuts.
 *
 * For each cut you choose the direction: vertical or horizontal, then you
 * choose a cut position at the cell boundary and cut the pizza into two pieces.
 * If you cut the pizza vertically, give the left part of the pizza to a person.
 * If you cut the pizza horizontally, give the upper part of the pizza to a
 * person. Give the last piece of pizza to the last person.
 *
 * Return the number of ways of cutting the pizza such that each piece contains
 * at least one apple. Since the answer can be a huge number, return this modulo
 * 10^9 + 7.
 *
 * ===========
 * My Approach
 * ===========
 * Cutting the pizza at rows 2 then 4, and at rows 1 then 4 results in the same
 * remaining portion of the pizza. Thus, to avoid calculating the same remaining
 * portion twice, we can use dynamic programming.
 *
 * We will calculate the number of ways to make 1 cut in each possible remaining
 * portion. This will inform how to make 2 cuts in the remaining portion, and so
 * on. This continues until we have made k-1 cuts, or we reach the whole pizza.
 *
 * This has time complexity of O(k*n*m*(n+m)) and space complexity of O(n*m),
 * where n is the number of rows of the pizza, m is the number of columns and k
 * is the number of slices to be made.
 ******************************************************************************/

#include <iostream>
#include <string>
#include <vector>

class Solution {
public:
	/**
	 * Finds number of ways to cut a pizza such that each slice has at least one
	 * apple, modulo 10^9 + 7
	 *
	 * @param pizza each element corresponds to a row of the pizza, where 'A'
	 * represents an apple and '.' represents an empty cell
	 * @param k number of slices to cut the pizza into
	 *
	 * @return number of ways to cut a pizza into k slices with at least one
	 * apple each, modulo 10^9 + 7
	 */
	long ways(std::vector<std::string>& pizza, int k) {
		int n = pizza.size();
		int m = pizza[0].size();

		// number of apples in the remaining slice pizza[i:-1][j:-1]
		std::vector<std::vector<int>> napples(n, std::vector<int>(m, 0));
		// bottom right column
		napples[n - 1][m - 1] = (pizza[n - 1][m - 1] == 'A');
		// bottom row
		for (int i = n - 2; i >= 0; i--) {
			napples[i][m - 1] = (pizza[i][m - 1] == 'A') + napples[i + 1][m - 1];
		}
		// rightmost column
		for (int j = m - 2; j >= 0; j--) {
			napples[n - 1][j] = (pizza[n - 1][j] == 'A') + napples[n - 1][j + 1];
		}
		// rest of elements
		for (int i = n - 2; i >= 0; i--) {
			for (int j = m - 2; j >= 0; j--) {
				napples[i][j] = (pizza[i][j] == 'A') + napples[i + 1][j] +
					napples[i][j + 1] - napples[i + 1][j + 1];
			}
		}

		// dp[i][j] is the number of ways to cut the remaining pizza[i:-1][j:-1]
		std::vector<std::vector<long>> dp(n, std::vector<long>(m, 0L));

		// find number for zero cut (i.e. if remaining has apple or not)
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				if (napples[i][j] > 0) {
					dp[i][j] = 1;
				}
			}
		}

		// find number for kk cuts
		for (int kk = 1; kk < k; kk++) {
			// consider pizza[i:-1][j:-1] remaining
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < m; j++) {
					// clear cell (to change for kk-1 cuts to kk cuts)
					dp[i][j] = 0;
					// consider slice by rows
					for (int ii = i + 1; ii < n; ii++) {
						if (napples[i][j] > napples[ii][j]) { // check top slice
							dp[i][j] += dp[ii][j]; // check bottom slice
							dp[i][j] %= 1000000007;
						}
					}
					// consider slice by columns
					for (int jj = j + 1; jj < m; jj++) {
						if (napples[i][j] > napples[i][jj]) { // check left slice
							dp[i][j] += dp[i][jj]; // check right slice
							dp[i][j] %= 1000000007;
						}
					}
					// short circuit for last cut, we only need dp[0][0];
					if (kk == k - 1) {
						return dp[0][0];
					}
				}
			}
		}

		return dp[0][0]; // if not compiler will complain
	}
};

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
 * Test cases
 */
int main(void) {
	Solution sol;
	std::vector<std::string> pizza;
	int k;

	// test case 1
	pizza = { "A..", "AAA", "..." };
	k = 3;
	std::cout << "ways(" << pizza << ", " << k << ") = "
		<< sol.ways(pizza, k) << std::endl;

	// test case 2
	pizza = { "A..","AA.","..." };
	k = 3;
	std::cout << "ways(" << pizza << ", " << k << ") = "
		<< sol.ways(pizza, k) << std::endl;

	// test case 3
	pizza = { "A..","A..","..." };
	k = 3;
	std::cout << "ways(" << pizza << ", " << k << ") = "
		<< sol.ways(pizza, k) << std::endl;

	return 0;
}