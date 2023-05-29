/*******************************************************************************
 * 1547-Minimum_Cost_to_Cut_Stick.cpp
 * Billy.Ljm
 * 28 May 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/minimum-cost-to-cut-a-stick/
 *
 * Given a wooden stick of length n units. The stick is labelled from 0 to n.
 *
 * Given an integer array cuts where cuts[i] denotes a position you should
 * perform a cut at.
 *
 * You should perform the cuts in order, you can change the order of the cuts as
 * you wish.
 *
 * The cost of one cut is the length of the stick to be cut, the total cost is
 * the sum of costs of all cuts. When you cut a stick, it will be split into two
 * smaller sticks (i.e. the sum of their lengths is the length of the stick
 * before the cut). Please refer to the first example for a better explanation.
 *
 * Return the minimum total cost of the cuts.
 *
 * ===========
 * My Approach
 * ===========
 * To minimise the cost, we have to iterate through all ordering of the cuts.
 * We'll use dynamic programming for efficiency, since cutting at cuts[0] then
 * cuts[1], or cuts[1] then cuts[0], would result in the same remaining stick
 * left. Thus, we can just calculate the cost of the remaining stick once.
 *
 * This has a time complexity of O(n^2) and space complexity of O(n^2), where n
 * is the number of cuts.
 ******************************************************************************/

#include <iostream>
#include <vector>
#include <algorithm>

/**
 * Solution
 */
class Solution {
private:
	/**
	 * Recursively calculates the minimum costs for making cuts[i:j], assuming
	 * that all other cuts have already been done.
	 *
	 * @param i starting index of cuts to execute
	 * @param j ending index of cuts to execute
	 * @param n length of original uncut stick
	 * @param cuts length to cut at
	 *
	 * @return minimum cost of making cuts[i:j]
	 */
	int recurse(int i, int j, int n, std::vector<int> &cuts,
		std::vector<std::vector<int>> &dp) {
		// if one remaining cut, return cost
		if (j == 0) {
			if (i == 0) return cuts[i + 1];
			else if (i == cuts.size() - 1) return n - cuts[i - 1];
			else return cuts[i + 1] - cuts[i - 1];
		}
		// if cached, return
		else if (dp[i][j - 1] > 0) {
			return dp[i][j - 1];
		}
		// else, recursively calculate
		else {
			int mincost = recurse(i + 1, j - 1, n, cuts, dp);
			mincost = std::min(mincost, recurse(i, j - 1, n, cuts, dp));
			for (int k = 1; k < j; k++) { 
				mincost = std::min(mincost, recurse(i, k - 1, n, cuts, dp) +
					recurse(i + k + 1, j - k - 1, n, cuts, dp));
			}
			// add current cut cost
			mincost += (i + j + 1 < cuts.size()) ? cuts[i + j + 1] : n; 
			mincost -= (i - 1 >= 0) ? cuts[i - 1] : 0;
			// cache result
			dp[i][j - 1] = mincost; 
			return mincost;
		}
	}

public:
	/**
	 * Find the minimum cost for cutting a stick of length n at specified cuts.
	 * The cost is the length of the stick currently being cut.
	 *
	 * @param n original length of the stick
	 * @param cuts lengths to cut at
	 *
	 * @return minimum cost of cutting the stick
	 */
	int minCost(int n, std::vector<int>& cuts) {
		if (cuts.size() == 0) { // no cuts
			return 0;
		}
		else if (cuts.size() == 1) { // one cut
			return n;
		}
		else {
			// make adjacent cuts adjacent physically
			std::sort(cuts.begin(), cuts.end());

			// dp[i][j] = minimum cost of cuts[i:i+j+1]
			std::vector<std::vector<int>> dp;
			for (int i = 0; i < cuts.size() - 1; i++) {
				dp.push_back(std::vector<int>(cuts.size() - i - 1));
			}

			// recursively calculate
			return recurse(0, cuts.size() - 1, n, cuts, dp);
		}
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
	int n;
	std::vector<int> cuts;

	// test case 1
	n = 7;
	cuts = { 1, 3, 4, 5 };
	std::cout << "minCost(" << n << "," << cuts << ") = " << sol.minCost(n, cuts)
		<< std::endl;

	// test case 2
	n = 9;
	cuts = { 5, 6, 1, 4, 2 };
	std::cout << "minCost(" << n << "," << cuts << ") = " << sol.minCost(n, cuts)
		<< std::endl;

	return 0;
}