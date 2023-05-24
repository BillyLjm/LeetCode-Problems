/*******************************************************************************
 * 2542-Maximum_Subsequence_Score.cpp
 * Billy.Ljm
 * 24 May 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/maximum-subsequence-score/
 *
 * You are given two 0-indexed integer arrays nums1 and nums2 of equal length n
 * and a positive integer k. You must choose a subsequence of indices from nums1
 * of length k.
 *
 * For chosen indices i0, i1, ..., ik - 1, your score is defined as:
 *
 * - The sum of the selected elements from nums1 multiplied with the minimum of
 *   the selected elements from nums2.
 * - It can defined simply as: (nums1[i0] + nums1[i1] +...+ nums1[ik - 1]) *
 *   min(nums2[i0] , nums2[i1], ... ,nums2[ik - 1]).
 *
 * Return the maximum possible score.
 *
 * ===========
 * My Approach
 * ===========
 * If we choose a specific nums2[i], the maximum score which includes that
 * number will be of the indices with larger nums2, and maximum num1. Thus, we 
 * just have to calculate this maximum score for each specific nums2, and return 
 * the overall maximum score. To do this efficiently, we can start with the 
 * largest nums2, then consider the second-largest nums2 and so on.
 *
 * This has a time complexity of O(n log n) and space complexity of O(n), where
 * n is the size of each array.
 ******************************************************************************/

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

/**
 * Solution
 */
class Solution {
public:
	/**
	 * Finds the maximum score of subsequences of nums1 and nums2 of length k.
	 * The score is the sum of the elements in the subsequence of nums1
	 * multiplied by the minimum of the elements in the subsequence of nums2.
	 *
	 * @param nums1 array to take sum of elements from
	 * @param nums2 array to take minimum of elements from
	 * @param k length of subsequences to consider
	 *
	 * @return maximum score of k-long subsequences of nums1 & nums2
	 */
	long long maxScore(std::vector<int>& nums1, std::vector<int>& nums2, int k) {
		// sort paired nums1 & nums2
		std::vector<std::pair<int, int>> nums;
		for (int i = 0; i < nums1.size(); i++) {
			nums.push_back({ nums1[i], nums2[i] });
		}
		std::sort(nums.begin(), nums.end(),
			[](std::pair<int, int> a, std::pair<int, int> b) {
				return a.second > b.second;
			}
		);

		// find maximum score for each nums2
		long long maxscore;
		long long summ = 0; // sum of k-largest nums1
		std::priority_queue<int, std::vector<int>, std::greater<int>> pq;
		// create first k-subsequence
		for (int i = 0; i < k; i++) {
			summ = summ + nums[i].first * 1LL;
			pq.push(nums[i].first);
		}
		maxscore = summ * nums[k - 1].second;
		// consider other k-subsequences
		for (int i = k; i < nums.size(); i++) {
			if (nums[i].first > pq.top()) {
				// add nums1 to summ
				summ = summ + nums[i].first * 1LL;
				pq.push(nums[i].first);
				summ = summ - pq.top();
				pq.pop();
				// calculate max score for current nums2
				maxscore = std::max(maxscore, summ * nums[i].second);
			}
		}

		return maxscore;
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
	std::vector<int> nums1, nums2;
	int k;

	// test case 1
	nums1 = { 1, 3, 3, 2 };
	nums2 = { 2, 1, 3, 4 };
	k = 3;
	std::cout << "maxScore(" << nums1 << "," << nums2 << "," << k << ") = "
		<< sol.maxScore(nums1, nums2, k) << std::endl;

	// test case 2
	nums1 = { 4, 2, 3, 1, 1 };
	nums2 = { 7, 5, 10, 9, 6 };
	k = 1;
	std::cout << "maxScore(" << nums1 << "," << nums2 << "," << k << ") = "
		<< sol.maxScore(nums1, nums2, k) << std::endl;

	return 0;
}