/*******************************************************************************
 * 0649-Dota2_Senate.cpp
 * Billy.Ljm
 * 04 May 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/dota2-senate/
 *
 * In the world of Dota2, there are two parties: the Radiant and the Dire.
 *
 * The Dota2 senate consists of senators coming from two parties. Now the Senate
 * wants to decide on a change in the Dota2 game. The voting for this change is
 * a round-based procedure. In each round, each senator can exercise one of the
 * two rights:
 * 
 * - Ban one senator's right: A senator can make another senator lose all his
 *   rights in this and all the following rounds.
 * - Announce the victory: If this senator found the senators who still have
 *   rights to vote are all from the same party, he can announce the victory and
 *   decide on the change in the game.
 *
 * Given a string senate representing each senator's party belonging. The
 * character 'R' and 'D' represent the Radiant party and the Dire party. Then if
 * there are n senators, the size of the given string will be n.
 *
 * The round-based procedure starts from the first senator to the last senator
 * in the given order. This procedure will last until the end of voting. All the
 * senators who have lost their rights will be skipped during the procedure.
 *
 * Suppose every senator is smart enough and will play the best strategy for his
 * own party. Predict which party will finally announce the victory and change
 * the Dota2 game. The output should be "Radiant" or "Dire".
 *
 * ===========
 * My Approach
 * ===========
 * The optimal strategy is to greedily ban the next senator to exercise his/her
 * right from the opposing faction. Thus, we can just queue up all the senators
 * and simulate the optimal strategy until either faction wins.
 *
 * To optimise the finding of the next opposing senator, we can remember the
 * outstanding amount of senators to be banned and ban them as we iterate through
 * the string of senators. To optimise the deleting of banned senators, we can
 * use a queue, which has O(1) popping.
 *
 * This has a time complexity of O(n) and space complexity of O(n), where n is
 * the number of senators.
 ******************************************************************************/

#include <iostream>
#include <vector>
#include <string>
#include <queue>

/**
 * Solution
 */
class Solution {
public:
	/**
	 * Predicts the winner of the senate voting
	 *
	 * @param senate string of senators, with 'R' and 'D' being opposing faction
	 *
	 * @return the winning faction, as 'radiant' or 'dire'
	 */
	std::string predictPartyVictory(std::string senate) {
		std::queue<bool> qq; // true for 'R', false for 'D'
		int rban = 0; // number of senators to be banned, from each faction
		int dban = 0;

		// first round, while filling queue
		for (int i = 0; i < senate.size(); i++) {
			if (senate[i] == 'R') {
				if (rban > 0) {
					rban--;
				}
				else {
					dban++;
					qq.push(true);
				}
			}
			else { // senate[i] == 'D'
				if (dban > 0) {
					dban--;
				}
				else {
					rban++;
					qq.push(false);
				}
			}
		}

		// subsequent rounds
		bool senator;
		while (rban < qq.size() and dban < qq.size()) { 
			// pop queue
			senator = qq.front();
			qq.pop();
			// simulate round
			if (senator == true) {
				if (rban > 0) {
					rban--;
				}
				else {
					dban++;
					qq.push(senator);
				}
			}
			else { // senator == false
				if (dban > 0) {
					dban--;
				}
				else {
					rban++;
					qq.push(senator);
				}
			}
		}

		return dban > 0 ? "Radiant" : "Dire";
	}
};

/**
 * Test cases
 */
int main(void) {
	Solution sol;
	std::string senate;

	// test case 1
	senate = "RD";
	std::cout << "predictPartyVictory(" << senate << ") = " <<
		sol.predictPartyVictory(senate) << std::endl;

	// test case 2
	senate = "RDD";
	std::cout << "predictPartyVictory(" << senate << ") = " <<
		sol.predictPartyVictory(senate) << std::endl;

	return 0;
}