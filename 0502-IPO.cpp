/*******************************************************************************
 * 0502-IPO.cpp
 * Billy.Ljm
 * 15 June 2024
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/ipo/
 *
 * Suppose LeetCode will start its IPO soon. In order to sell a good price of
 * its shares to Venture Capital, LeetCode would like to work on some projects
 * to increase its capital before the IPO. Since it has limited resources, it
 * can only finish at most k distinct projects before the IPO. Help LeetCode
 * design the best way to maximize its total capital after finishing at most k
 * distinct projects.
 *
 * You are given n projects where the ith project has a pure profit profits[i]
 * and a minimum capital of capital[i] is needed to start it.
 *
 * Initially, you have w capital. When you finish a project, you will obtain its
 * pure profit and the profit will be added to your total capital.
 *
 * Pick a list of at most k distinct projects from given projects to maximize
 * your final capital, and return the final maximized capital.
 *
 * The answer is guaranteed to fit in a 32-bit signed integer.
 *
 * ===========
 * My Approach
 * ===========
 * We are constrained by the number of projects but not the time to complete
 * them. Thus, it is optimal to complete the projects one by one and use the
 * full capital after completion to pick the next project with the largest
 * profits, constituting a greedy algorithm.
 *
 * This has a time complexity of O(n log n) and space complexity of O(n), where
 * n is the size of the array.
 ******************************************************************************/

#include <iostream>
#include <vector>
#include <queue>
#include <ranges>
#include <algorithm>

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
	int findMaximizedCapital(int k, int w, std::vector<int>& profits,
		std::vector<int>& capital) {
		priority_queue<int, vector<int>> avail_profits;

		// sort projects by descending capital
		// if your compiler supports zip
		ranges::sort(views::zip(capital, profits), [](auto a, auto b) {
			return get<0>(a) > get<0>(b);
		});
		/*// if your compiler doesn't support zip
		vector<tuple<int, int>> projects;
		for (int i = 0; i < profits.size(); i++) {
			projects.push_back({ capital[i], profits[i] });
		}
		sort(projects.begin(), projects.end(), [](auto a, auto b) {
			return get<0>(a) > get<0>(b);
			});
		for (int i = 0; i < profits.size(); i++) {
			capital[i] = get<0>(projects[i]);
			profits[i] = get<1>(projects[i]);
		}*/

		// greedily choose projects
		for (int i = 0; i < k; i++) {
			// update available projects
			while (!capital.empty() and capital.back() <= w) {
				avail_profits.push(profits.back());
				profits.pop_back();
				capital.pop_back();
			}

			// if no projects left, return
			if (avail_profits.empty()) {
				break;
			}
			// else choose project with highest profit
			else {
				w += avail_profits.top();
				avail_profits.pop();
			}

		}

		return w;
	}
};

/**
 * Test cases
 */
int main(void) {
	Solution sol;
	int k, w;
	std::vector<int> profits, capital;

	// test case 1
	k = 2;
	w = 0;
	profits = { 1,2,3 };
	capital = { 0,1,1 };
	std::cout << "findMaximizedCapital(" << k << ", " << w << ", " << profits
		<< ", " << capital << ") = ";
	std::cout << sol.findMaximizedCapital(k, w, profits, capital) << std::endl;

	// test case 2
	k = 3;
	w = 0;
	profits = { 1,2,3 };
	capital = { 0,1,2 };
	std::cout << "findMaximizedCapital(" << k << ", " << w << ", " << profits
		<< ", " << capital << ") = ";
	std::cout << sol.findMaximizedCapital(k, w, profits, capital) << std::endl;

	return 0;
}