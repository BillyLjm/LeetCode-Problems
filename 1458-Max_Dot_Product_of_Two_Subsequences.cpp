/*******************************************************************************
 * 1458-Max_Dot_Product_of_Two_Subsequences.cpp
 * Billy.Ljm
 * 08 October 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/max-dot-product-of-two-subsequences/
 *
 * Given two arrays nums1 and nums2.
 *
 * Return the maximum dot product between non-empty subsequences of nums1 and
 * nums2 with the same length.
 *
 * A subsequence of a array is a new array which is formed from the original
 * array by deleting some (can be none) of the characters without disturbing the
 * relative positions of the remaining characters. (ie, [2,3,5] is a subsequence
 * of [1,2,3,4,5] while [1,5,3] is not).
 *
 * ===========
 * My Approach
 * ===========
 * We will use dynamic programming, where dp[i][j] = the maximum dot product for
 * nums1[i:] and nums2[j:]. For each additional number, we either ignore it or
 * dot it with one of the characters in the other array. In other words,
 * dp[i][j] = max(dp[i-1][j], nums1[i] * nums2[k] + dp[i-1][k]), where k <= j
 * To save on memory, we can drop the index i and just overwrite dp[j] as we go.
 *
 * This has a time complexity of O(n * m^2), and space complexity of O(m),
 * where n is the size of the nums1, m is the size of nums2
 ******************************************************************************/

#include <iostream>
#include <vector>
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
	int maxDotProduct(vector<int>& nums1, vector<int>& nums2) {
		vector<int> dp(nums2.size(), 0);
		vector<int> prevdp;
		int out;

		// fill rest of dp table
		for (int i = 0; i < nums1.size(); i++) {
			// save previous dp
			prevdp = dp;
			for (int j = 0; j < nums2.size(); j++) {
				// ignore new number
				if (j != 0) dp[j] = max(dp[j], dp[j - 1]);
				// dot number with previous numbers
				for (int k = 0; k <= j; k++) {
					if (k != 0) {
						dp[j] = max(dp[j], nums1[i] * nums2[k] + prevdp[k - 1]);
					}
					else {
						dp[j] = max(dp[j], nums1[i] * nums2[k]);
					}
				}
			}
		}
		out = dp.back();

		// if max dot product is negative, calculate manually
		if (out == 0) {
			auto minmax1 = minmax_element(nums1.begin(), nums1.end());
			auto minmax2 = minmax_element(nums2.begin(), nums2.end());
			out = *minmax1.first * *minmax2.first;
			out = max(out, *minmax1.first * *minmax2.second);
			out = max(out, *minmax1.second * *minmax2.first);
			out = max(out, *minmax1.second * *minmax2.second);
		}

		return out;
	}
};

/**
 * Test cases
 */
int main(void) {
	Solution sol;
	vector<int> nums1, nums2;

	// test case 1
	nums1 = { 2,1,-2,5 };
	nums2 = { 3,0,-6 };
	std::cout << "maxDotProduct(" << nums1 << "," << nums2 << ") = ";
	std::cout << sol.maxDotProduct(nums1, nums2) << std::endl;

	// test case 2
	nums1 = { 3,-2 };
	nums2 = { 2,-6,7 };
	std::cout << "maxDotProduct(" << nums1 << "," << nums2 << ") = ";
	std::cout << sol.maxDotProduct(nums1, nums2) << std::endl;

	// test case 3
	nums1 = { -1,-1 };
	nums2 = { 1,1 };
	std::cout << "maxDotProduct(" << nums1 << "," << nums2 << ") = ";
	std::cout << sol.maxDotProduct(nums1, nums2) << std::endl;

	return 0;
}