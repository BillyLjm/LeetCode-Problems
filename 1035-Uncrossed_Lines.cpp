/*******************************************************************************
 * 1035-Uncrossed_Lines.cpp
 * Billy.Ljm
 * 11 May 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/uncrossed-lines/
 *
 * You are given two integer arrays nums1 and nums2. We write the integers of
 * nums1 and nums2 (in the order they are given) on two separate horizontal
 * lines.
 *
 * We may draw connecting lines: a straight line connecting two numbers nums1[i]
 * and nums2[j] such that:
 * 
 * - nums1[i] == nums2[j], and
 * - the line we draw does not intersect any other connecting (non-horizontal)
 *   line.
 *
 * Note that a connecting line cannot intersect even at the endpoints (i.e.,
 * each number can only belong to one connecting line).
 *
 * Return the maximum number of connecting lines we can draw in this way.
 *
 * ===========
 * My Approach
 * ===========
 * The task can be reformulated as finding the longest common subsequence. The
 * paired elements will be in the common subsequence, and there are no crossing
 * of lines since the subsequences will preserve the initial ordering.
 *
 * The known optimal algorithm for this problem is dynamic programming.
 * https://en.wikipedia.org/wiki/Longest_common_subsequence
 *
 * This has a time complexity of O(n * m) and space complexity of O(n * m),
 * where n and m are the lengths of the two arrays.
 ******************************************************************************/

#include <iostream>
#include <vector>

 /**
  * Solution
  */
class Solution {
public:
	/**
	 * Finds the maximum number of uncrossed lines which can be drawn between
	 * elements of similar values in two arrays
	 *
	 * @param nums1 array to be paired with nums2
	 * @param nums2 array to be paired with nums1
	 *
	 * @return max number of uncrossed lines b/w similar value in nums1, nums2
	 */
	int maxUncrossedLines(std::vector<int>& nums1, std::vector<int>& nums2) {
		// dynamic programming table
		std::vector<std::vector<int>> dp(nums1.size() + 1,
			std::vector<int>(nums2.size() + 1, 0));

		// fill up table
		for (int i = 1; i <= nums1.size(); i++) {
			for (int j = 1; j <= nums2.size(); j++) {
				if (nums1[i - 1] == nums2[j - 1]) {
					dp[i][j] = dp[i - 1][j - 1] + 1;
				}
				else {
					dp[i][j] = std::max(dp[i - 1][j], dp[i][j - 1]);
				}
			}
		}

		return dp.back().back();
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

	// test case 1
	nums1 = { 1, 4, 2 };
	nums2 = { 1, 2, 4 };
	std::cout << "maxUncrossedLines(" << nums1 << "," << nums2 << ") = "
		<< sol.maxUncrossedLines(nums1, nums2) << std::endl;

	// test case 2
	nums1 = { 2, 5, 1, 2, 5 };
	nums2 = { 10, 5, 2, 1, 5, 2 };
	std::cout << "maxUncrossedLines(" << nums1 << "," << nums2 << ") = "
		<< sol.maxUncrossedLines(nums1, nums2) << std::endl;

	// test case 3
	nums1 = { 1, 3, 7, 1, 7, 5 };
	nums2 = { 1, 9, 2, 5, 1 };
	std::cout << "maxUncrossedLines(" << nums1 << "," << nums2 << ") = "
		<< sol.maxUncrossedLines(nums1, nums2) << std::endl;

	return 0;
}