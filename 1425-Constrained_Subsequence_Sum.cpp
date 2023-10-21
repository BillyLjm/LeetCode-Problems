/*******************************************************************************
 * 1425-Constrained_Subsequence_Sum.cpp
 * Billy.Ljm
 * 21 October 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/constrained-subsequence-sum/
 *
 * Given an integer array nums and an integer k, return the maximum sum of a
 * non-empty subsequence of that array such that for every two consecutive
 * integers in the subsequence, nums[i] and nums[j], where i < j, the condition
 * j - i <= k is satisfied.
 *
 * A subsequence of an array is obtained by deleting some number of elements
 * (can be zero) from the array, leaving the remaining elements in their
 * original order.
 *
 * ===========
 * My Approach
 * ===========
 * We can essentially remove k adjacent elements from the array to maximise the
 * sum. Thus, dynamic programming can be used to consider all removals and find
 * the optimal subsequence. To speed things up, we can use a priority queue to
 * consider the removals, adding and removing one element into the queue on each
 * iteration instead of comparing k elements on every iteration.
 *
 * This has a time complexity of O(n * log(k)), and space complexity of O(n),
 * where n is the size of the array and k is the integer given as an argument.
 ******************************************************************************/

#include <iostream>
#include <vector>
#include <queue>

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
	int constrainedSubsetSum(vector<int>& nums, int k) {
		// dp[i] = max sum when including nums[i]
		vector<int> dp(nums.size(), 0);
		// last k elements of dp as {dp[i], i}
		priority_queue<pair<int, int>> pq;
		pq.push({ 0, -1 });

		// fill up dp table
		for (int i = 0; i < nums.size(); i++) {
			while (pq.top().second < i - k) pq.pop();
			dp[i] = max(0, pq.top().first) + nums[i];
			pq.push({ dp[i], i });
		}

		// find answer
		return *max_element(dp.begin(), dp.end());
	}
};

/**
 * Test cases
 */
int main(void) {
	Solution sol;
	vector<int> nums;
	int k;

	// test case 1
	nums = { 10,2,-10,5,20 };
	k = 2;
	std::cout << "constrainedSubsetSum(" << nums << "," << k << ") = ";
	std::cout << sol.constrainedSubsetSum(nums, k) << std::endl;

	// test case 2
	nums = { -1,-2,-3 };
	k = 1;
	std::cout << "constrainedSubsetSum(" << nums << "," << k << ") = ";
	std::cout << sol.constrainedSubsetSum(nums, k) << std::endl;

	// test case 3
	nums = { 10,-2,-10,-5,20 };
	k = 2;
	std::cout << "constrainedSubsetSum(" << nums << "," << k << ") = ";
	std::cout << sol.constrainedSubsetSum(nums, k) << std::endl;

	return 0;
}