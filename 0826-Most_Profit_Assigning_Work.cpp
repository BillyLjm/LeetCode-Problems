/*******************************************************************************
 * 0826-Most_Profit_Assigning_Work.cpp
 * Billy.Ljm
 * 18 June 2024
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/most-profit-assigning-work/
 *
 * You have n jobs and m workers. You are given three arrays: difficulty,
 * profit, and worker where:
 * - difficulty[i] and profit[i] are the difficulty and the profit of the ith
 *   job, and
 * - worker[j] is the ability of jth worker (i.e., the jth worker can only
 *   complete a job with difficulty at most worker[j]).
 *
 * Every worker can be assigned at most one job, but one job can be completed
 * multiple times.
 *
 * For example, if three workers attempt the same job that pays $1, then the
 * total profit will be $3. If a worker cannot complete any job, their profit is
 * $0.
 *
 * Return the maximum profit we can achieve after assigning the workers to the
 * jobs.
 *
 * ===========
 * My Approach
 * ===========
 * We just want to find the highest-paying job for each worker's ability. So we
 * can sort the worker by ability, choose the highest paying job and assign it
 * to all unoccupied workers capable of completing it, rinse and repeat.
 *
 * This has a time complexity of O(n log n) and space complexity of O(n), where
 * n is the length of the longest vector given as an argument.
 ******************************************************************************/

#include <iostream>
#include <vector>
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
	int maxProfitAssignment(vector<int>& difficulty, vector<int>& profit,
		vector<int>& worker) {

		// sort jobs by descending profit
		// if your compiler supports zip
		ranges::sort(views::zip(profit, difficulty), [](auto a, auto b) {
			return get<0>(a) > get<0>(b);
		});
		/*// if your compiler doesn't support zip
		vector<tuple<int, int>> jobs;
		for (int i = 0; i < profit.size(); i++) {
			jobs.push_back({ profit[i], difficulty[i] });
		}
		sort(jobs.begin(), jobs.end(), [](auto a, auto b) {
			return get<0>(a) > get<0>(b);
		});
		for (int i = 0; i < profit.size(); i++) {
			profit[i] = get<0>(jobs[i]);
			difficulty[i] = get<1>(jobs[i]);
		}*/

		// assign jobs to worker with decreasing capability
		int maxprofit = 0;
		int jobidx = 0;
		sort(worker.begin(), worker.end(), greater<int>());
		for (int i : worker) {
			while (i < difficulty[jobidx]) {
				jobidx++;
				if (jobidx >= difficulty.size()) return maxprofit;
			}
			maxprofit += profit[jobidx];
		}

		return maxprofit;
	}
};

/**
 * Test cases
 */
int main(void) {
	Solution sol;
	vector<int> difficulty, profit, worker;

	// test case 1
	difficulty = { 2,4,6,8,10 };
	profit = { 10,20,30,40,50 };
	worker = { 4,5,6,7 };
	std::cout << "maxProfitAssignment(" << difficulty << ", " << profit
		<< ", " << worker << ") = ";
	std::cout << sol.maxProfitAssignment(difficulty, profit, worker) << std::endl;

	// test case 2
	difficulty = { 85,47,57 };
	profit = { 24,66,99 };
	worker = { 40,25,25 };
	std::cout << "maxProfitAssignment(" << difficulty << ", " << profit
		<< ", " << worker << ") = ";
	std::cout << sol.maxProfitAssignment(difficulty, profit, worker) << std::endl;

	return 0;
}