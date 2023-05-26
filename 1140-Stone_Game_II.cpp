/*******************************************************************************
 * 1140-Stone_Game_II.cpp
 * Billy.Ljm
 * 26 May 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/stone-game-ii/
 *
 * Alice and Bob continue their games with piles of stones.  There are a number
 * of piles arranged in a row, and each pile has a positive integer number of
 * stones piles[i].  The objective of the game is to end with the most stones. 
 *
 * Alice and Bob take turns, with Alice starting first.  Initially, M = 1.
 *
 * On each player's turn, that player can take all the stones in the first X
 * remaining piles, where 1 <= X <= 2M.  Then, we set M = max(M, X).
 *
 * The game continues until all the stones have been taken.
 *
 * Assuming Alice and Bob play optimally, return the maximum number of stones
 * Alice can get.
 *
 * ===========
 * My Approach
 * ===========
 * We have to consider all strategies to find the one with the maximum score.
 * Fortunately, many of these strategies lead to the same intermediate state, 
 * for example choosing 1, 2, 1 piles will yield the same as 2, 1, 1, since both
 * end up at the same player, M, and piles left. Thus, we can memoise them to
 * avoid repeating the same calculation.
 *
 * Furthermore, we can use a negative sign to encapsulate the adversarial nature
 * of the game. meme[0] = alice[0] - memo[1] = alice[0] - bob[1] + memo[2]. Then,
 * alice[0] = bob[0] and vice versa, and we don't need to calculate each player
 * separately.
 *
 * This has a time complexity of O(n) and space complexity of O(n), where n is
 * the number of piles.
 ******************************************************************************/

#include <iostream>
#include <vector>

/**
 * Solution
 */
class Solution {
private:
	/**
	 * Returns the maximum differential score attainable with a specific M and
	 * number of piles left
	 *
	 * @param ipiles starting integer of piles left
	 * @param m number of piles taken in previous round
	 * @param piles number of stones in each pile
	 * @param memo to memoise the output of this function, as memo[ipiles][m]
	 *
	 * @return maximum differential score of current player - next player
	 */
	int diffScore(int ipiles, int m, std::vector<int>& piles,
		std::vector<std::vector<int>>& memo) {
		// if no piles left, return 0
		if (ipiles >= piles.size()) {
			return 0;
		}
		// if all piles can be taken, take all
		else if (ipiles + 2 * m >= piles.size()) {
			int maxscore = 0;
			for (int i = ipiles; i < piles.size(); i++) {
				maxscore = maxscore + piles[i];
			}
			return maxscore;
		}
		// if memoised, return cached
		else if (memo[ipiles][m] != INT_MIN) {
			return memo[ipiles][m];
		}
		// else recursively consider all scenarios
		else {
			int maxscore = INT_MIN; // max differential score
			int stones = 0; // number of stones taken in current step
			for (int x = 1; x <= 2 * m; x++) { // number of piles to take
				stones = stones + piles[ipiles + x - 1];
				maxscore = std::max(maxscore, stones -
					diffScore(ipiles + x, std::max(m, x), piles, memo));
			}
			memo[ipiles][m] = maxscore;
			return memo[ipiles][m];
		}
	}

public:
	/**
	 * Returns the maximum score/rocks attainable by the first player, where two
	 * players takes turns accumulating rocks from specified piles. In each step,
	 * the player can take up to twice the number of piles as was taken before.
	 *
	 * @param piles number of rocks in each pile
	 * 
	 * @return maximum number of rocks accumulated by first player
	 */
	int stoneGameII(std::vector<int>& piles) {
		// memo[ipiles][m] = max differential score of situation, for Alice & Bob
		std::vector<std::vector<int>> memo;
		for (int i = 0; i < piles.size(); i++) { // m only up to piles_left/2
			memo.push_back(std::vector<int>((piles.size() - i) / 2 + 1, INT_MIN));
		}

		// count total number of stones
		int totstones = 0;
		for (int i = 0; i < piles.size(); i++) {
			totstones = totstones + piles[i];
		}

		// convert differential score to personal score
		return (totstones + diffScore(0, 1, piles, memo)) / 2;
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
	std::vector<int> piles;

	// test case 1
	piles = { 2, 7, 9, 4, 4 };
	std::cout << "stoneGameII(" << piles << ") = " << sol.stoneGameII(piles)
		<< std::endl;

	// test case 2
	piles = { 1, 2, 3, 4, 5, 100 };
	std::cout << "stoneGameII(" << piles << ") = " << sol.stoneGameII(piles)
		<< std::endl;

	return 0;
}