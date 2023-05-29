/*******************************************************************************
 * 1406_Stone_Game_III.cpp
 * Billy.Ljm
 * 27 May 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/stone-game-iii/
 *
 * Alice and Bob continue their games with piles of stones. There are several
 * stones arranged in a row, and each stone has an associated value which is an
 * integer given in the array stoneValue.
 *
 * Alice and Bob take turns, with Alice starting first. On each player's turn,
 * that player can take 1, 2, or 3 stones from the first remaining stones in the
 * row.
 *
 * The score of each player is the sum of the values of the stones taken. The
 * score of each player is 0 initially.
 *
 * The objective of the game is to end with the highest score, and the winner is
 * the player with the highest score and there could be a tie. The game
 * continues until all the stones have been taken.
 *
 * Assume Alice and Bob play optimally.
 *
 * Return "Alice" if Alice will win, "Bob" if Bob will win, or "Tie" if they
 * will end the game with the same score.
 *
 * ===========
 * My Approach
 * ===========
 * We have to consider all strategies to find the one with the maximum score.
 * Fortunately, many of these strategies lead to the same intermediate state,
 * for example choosing 1, 2, 1 piles will yield the same as 2, 1, 1, since both
 * end up at the same player and stones left. Thus, we can memoise them to
 * avoid repeating the same calculation.
 *
 * We will calculate the differential score, since the subtraction encapsulates 
 * the adversarial nature of the game. memo[0] = alice[0] - memo[1] =
 * alice[0] - bob[1] + memo[2]. Then,  alice[0] = bob[0] and vice versa, and we
 * don't need to calculate each player separately. And finally depending on if
 * the differential score is positive of negative, we know the winner.
 *
 * This has a time complexity of O(n) and space complexity of O(n), where n is
 * the number of stones.
 ******************************************************************************/

#include <iostream>
#include <vector>

/**
 * Solution
 */
class Solution {
private:
	/**
	 * Returns the maximum differential score attainable
	 *
	 * @param istone starting integer of stones left
	 * @param stoneValue score of each stone
	 * @param memo to memoise the output of this function, as memo[istone]
	 *
	 * @return maximum differential score of current player - next player
	 */
	int diffScore(int istone, std::vector<int>& stoneValue, std::vector<int>& memo) {
		// if no piles left, reutrn 0
		if (istone >= stoneValue.size()) {
			return 0;
		}
		// if memoised, return cached
		else if (memo[istone] != INT_MIN) {
			return memo[istone];
		}
		// else recursively consider all scenarios
		else {
			int maxscore = INT_MIN; // max differential score
			int stones = 0; // number of stones taken in current step
			for (int x = 1; x < 4; x++) { // number of piles to take
				if (istone + x - 1 >= stoneValue.size()) break;
				stones = stones + stoneValue[istone + x - 1];
				maxscore = std::max(maxscore, stones -
					diffScore(istone + x, stoneValue, memo));
			}
			memo[istone] = maxscore;
			return memo[istone];
		}
	}

public:
	/**
	 * Returns the maximum score/rocks attainable by the first player, where two
	 * players takes turns accumulating rocks from specified piles. In each step,
	 * the player can take up to twice the number of piles as was taken before.
	 *
	 * @param stoneValue number of rocks in each pile
	 *
	 * @return "Alice" if the first player wins, "Bob" if the second player wins
	 */
	std::string stoneGameIII(std::vector<int>& stoneValue) {
		// memo[istone][m] = max differential score of situation, for Alice & Bob
		std::vector<int> memo(stoneValue.size(), INT_MIN);

		// recursively simulate game
		int diff = diffScore(0, stoneValue, memo);

		// return result
		if (diff == 0)  return "Tie";
		else if (diff > 0)  return "Alice";
		else return "Bob";
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
	std::vector<int> stoneValue;

	// test case 1
	stoneValue = { 1, 2, 3, 7 };
	std::cout << "stoneGameIII(" << stoneValue << ") = "
		<< sol.stoneGameIII(stoneValue) << std::endl;

	// test case 2
	stoneValue = { 1, 2, 3, -9 };
	std::cout << "stoneGameIII(" << stoneValue << ") = "
		<< sol.stoneGameIII(stoneValue) << std::endl;

	// test case 3
	stoneValue = { 1, 2, 3, 6 };
	std::cout << "stoneGameIII(" << stoneValue << ") = "
		<< sol.stoneGameIII(stoneValue) << std::endl;

	return 0;
}