/*******************************************************************************
 * 0837-New_21_Game.cpp
 * Billy.Ljm
 * 25 May 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/new-21-game/
 *
 * Alice plays the following game, loosely based on the card game "21".
 *
 * Alice starts with 0 points and draws numbers while she has less than k points.
 * During each draw, she gains an integer number of points randomly from the
 * range [1, maxPts], where maxPts is an integer. Each draw is independent and
 * the outcomes have equal probabilities.
 *
 * Alice stops drawing numbers when she gets k or more points.
 *
 * Return the probability that Alice has n or fewer points.
 *
 * ===========
 * My Approach
 * ===========
 * We can just simulate the game, filling up a dynamic programming table where
 * prob[i] represents the probability of getting a score i. The prob[i] will be
 * the average of prob[i-maxPts:i-1], since we'll rolling a fair die. We also
 * have to ignore ranges larger than maxPts, since the "probabilities" will sum 
 * to more than 1 and not be actual probabilities.
 *
 * This has a time complexity of O(n) and space complexity of O(n), where n is
 * the maximum points for winning.
 ******************************************************************************/

#include <iostream>
#include <vector>

/**
 * Solution
 */
class Solution {
public:
	/**
	 * Returns the probability of getting [k+1,n] points by rolling a maxPts-sided
	 * die and accumulating the result.
	 *
	 * @param n maximum points to win
	 * @param k minimum points to win
	 * @param maxPts maximum points added per roll
	 *
	 * @return probability of accumulating [k,n] points across multiple rolls
	 */
	double new21Game(int n, int k, int maxPts) {
		std::vector<double> probs (n + 1, 0); // probs[i] = probability of score i
		probs[0] = 1; // no dice rolls
		double summ = 0; // to sum prob[i-maxPts:i-1]

		// if [n,k] is larger than maxpts, we'll always win
		if (n - k >= maxPts - 1) {
			return 1.0;
		}

		// simulate game
		for (int i = 1; i <= n; i++) {
			if (i <= k) { // can only roll when points < k
				summ = summ + probs[i - 1];
			}
			if (i - maxPts > 0) { // can only reach i from i - maxpts
				summ = summ - probs[i - maxPts - 1];
			}
			probs[i] = summ / maxPts;
		}

		// sum probability of range
		double totprob = 0;
		for (int i = k; i <= n; i++) {
			totprob = totprob + probs[i];
		}
		return totprob;
	}
};

/**
 * Test cases
 */
int main(void) {
	Solution sol;
	int n, k, maxPts;

	// test case 1
	n = 10;
	k = 1;
	maxPts = 10;
	std::cout << "new21Game(" << n << "," << k << "," << maxPts << ") = "
		<< sol.new21Game(n, k, maxPts) << std::endl;

	// test case 2
	n = 6;
	k = 1;
	maxPts = 10;
	std::cout << "new21Game(" << n << "," << k << "," << maxPts << ") = "
		<< sol.new21Game(n, k, maxPts) << std::endl;

	// test case 3
	n = 21;
	k = 17;
	maxPts = 10;
	std::cout << "new21Game(" << n << "," << k << "," << maxPts << ") = "
		<< sol.new21Game(n, k, maxPts) << std::endl;

	return 0;
}