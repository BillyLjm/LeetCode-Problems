/*******************************************************************************
 * 2140-Solving_Questions_with_Brainpower.cpp
 * Billy.Ljm
 * 12 May 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/solving-questions-with-brainpower/
 *
 * You are given a 0-indexed 2D integer array questions where questions[i] =
 * [pointsi, brainpoweri].
 *
 * The array describes the questions of an exam, where you have to process the
 * questions in order (i.e., starting from question 0) and make a decision
 * whether to solve or skip each question. Solving question i will earn you
 * pointsi points but you will be unable to solve each of the next brainpoweri
 * questions. If you skip question i, you get to make the decision on the next
 * question.
 *
 * For example, given questions = [[3, 2], [4, 3], [4, 4], [2, 5]]:
 * - If question 0 is solved, you will earn 3 points but you will be unable to
 *   solve questions 1 and 2.
 * - If instead, question 0 is skipped and question 1 is solved, you will earn 4
 *   points but you will be unable to solve questions 2 and 3.
 *
 * Return the maximum points you can earn for the exam.
 *
 * ===========
 * My Approach
 * ===========
 * We can solve this with dynamic programming. If we solve questions[i], we add
 * question[i][0] to the maximum points for question[i + question[i][1]:-1]. If
 * we don't solve it, we just take the maximum points for question[i + 1:-1].
 * Thus the we can calculate the maximum points for the last i problems, and
 * use that to inform the last i + 1 problems.
 *
 * This has a time complexity of O(n) and space complexity of O(n), where n is
 * the number of questions
 ******************************************************************************/

#include <iostream>
#include <vector>

/**
 * Solution
 */
class Solution {
public:
	/**
	 * Finds the most points attainable in a list of questions. Where each
	 * question is [score, brainpower], and the brainpower denotes how many
	 * subsequent questions must be skipped if the current question is answered.
	 *
	 * @param questions vector of question's [score, brainpower]
	 *
	 * @return most points attainable for the given list of questions
	 */
	long long mostPoints(std::vector<std::vector<int>>& questions) {
		size_t tmp;
		size_t n = questions.size();
		std::vector<long long> dp(n); // max points for questions[i:-1]
		dp[n - 1] = questions[n - 1][0];

		for (int i = n - 2; i >= 0 ; i--) {
			tmp = i + questions[i][1] + 1; // index of next qn if problem solved
			dp[i] = tmp >= n ? 0 : dp[tmp]; // if solving problem
			dp[i] = questions[i][0] + dp[i];
			dp[i] = std::max(dp[i + 1], dp[i]); // compare w/ skipping problem
		}

		return dp[0];
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
	std::vector<std::vector<int>> questions;

	// test case 1
	questions = { {3, 2}, {4, 3}, {4, 4}, {2, 5} };
	std::cout << "mostPoints(" << questions << ") = " 
		<< sol.mostPoints(questions) << std::endl;

	// test case 2
	questions = { {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5} };
	std::cout << "mostPoints(" << questions << ") = "
		<< sol.mostPoints(questions) << std::endl;

	return 0;
}