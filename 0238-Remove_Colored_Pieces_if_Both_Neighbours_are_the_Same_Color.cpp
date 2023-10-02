/*******************************************************************************
 * 0238-Remove_Colored_Pieces_if_Both_Neighbours_are_the_Same_Color.cpp
 * Billy.Ljm
 * 02 October 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/remove-colored-pieces-if-both-neighbors-are-the-same-color/
 *
 * There are n pieces arranged in a line, and each piece is colored either by
 * 'A' or by 'B'. You are given a string colors of length n where colors[i] is
 * the color of the ith piece.
 *
 * Alice and Bob are playing a game where they take alternating turns removing
 * pieces from the line. In this game, Alice moves first.
 * - Alice is only allowed to remove a piece colored 'A' if both its neighbors
 *   are also colored 'A'. She is not allowed to remove pieces that are colored
 *   'B'.
 * - Bob is only allowed to remove a piece colored 'B' if both its neighbors are
 *   also colored 'B'. He is not allowed to remove pieces that are colored 'A'.
 * - Alice and Bob cannot remove pieces from the edge of the line.
 * - If a player cannot make a move on their turn, that player loses and the
 *   other player wins.
 *
 * Assuming Alice and Bob play optimally, return true if Alice wins, or return
 * false if Bob wins.
 *
 * ===========
 * My Approach
 * ===========
 * This is not a competitive game, in that the player's choices can't influence
 * the outcome of the game. This is because Alice can only whittle a 'BAA...AAB'
 * to 'BAB', and can never create new subsequences of A's or B's which either
 * player can now remove elements from. Thus, there is no optimal strategy to
 * find here, just one strategy and one outcome.
 *
 * This one strategy is to remove any element in any subsequences of A's and B's,
 * until no such elements exist anymore. Thus, we just have to count the number
 * of removable elements for Alice and Bob, and the larger count will win.
 *
 * This has a time complexity of O(n), and a space complexity of O(1), where n
 * is the number of pieces.
 ******************************************************************************/

#include <iostream>
#include <vector>

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
	bool winnerOfGame(string colors) {
		// count number of removable elements
		int numa = 0, numb = 0;
		for (int i = 1; i < colors.size() - 1; i++) {
			if (colors[i] == colors[i - 1] and colors[i] == colors[i + 1]) {
				if (colors[i] == 'A') numa++;
				else numb++;
			}
		}

		// return winner
		return numa > numb;
	}
};

/**
 * Test cases
 */
int main(void) {
	Solution sol;
	string colors;

	// test case 1
	colors = "AAABABB";
	std::cout << "winnerOfGame(" << colors << ") = ";
	std::cout << std::boolalpha << sol.winnerOfGame(colors) << std::endl;

	// test case 2
	colors = "AA";
	std::cout << "winnerOfGame(" << colors << ") = ";
	std::cout << std::boolalpha << sol.winnerOfGame(colors) << std::endl;

	// test case 3
	colors = "ABBBBBBBAAA";
	std::cout << "winnerOfGame(" << colors << ") = ";
	std::cout << std::boolalpha << sol.winnerOfGame(colors) << std::endl;

	return 0;
}