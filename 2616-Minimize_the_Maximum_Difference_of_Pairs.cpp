/*******************************************************************************
 * 2616-Minimize_the_Maximum_Difference_of_Pairs.cpp
 * Billy.Ljm
 * 09 August 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/minimize-the-maximum-difference-of-pairs/
 *
 * You are given a 0-indexed integer array nums and an integer p. Find p pairs
 * of indices of nums such that the maximum difference amongst all the pairs is
 * minimized. Also, ensure no index appears more than once amongst the p pairs.
 *
 * Note that for a pair of elements at the index i and j, the difference of this
 * pair is |nums[i] - nums[j]|, where |x| represents the absolute value of x.
 *
 * Return the minimum maximum difference among all p pairs. We define the
 * maximum of an empty set to be zero.
 *
 * ===========
 * My Approach
 * ===========
 * We'll use binary search to search for the minimum threshold under which we
 * can form p pairs. To find the number of pairs for a given threshold, we will
 * sort the array and greedily pair adjacent numbers together.
 *
 * This has a time complexity of O(n log k), and a space complexity of  O(1),
 * where n and k is the length and maximum element of the array respectively.
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
	for (int i = 0; i < v.size(); i++) {
		os << v[i] << ",";
	}
	os << "\b]";
	return os;
}

/**
 * Solution
 */
class Solution {
public:
	/**
	 * Finds the number of pairs with distance under a threshold
	 *
	 * @param nums array of numbers sorted in ascending order
	 * @param threshold distance threshold under which numbers will be paired
	 * @return number of pairs with distance under threshold
	 */
	int numPairs(vector<int>& nums, int threshold) {
		int npairs = 0;
		int index = 1;

		// try to pair adjacent numbers
		// non-adjacent numbers have higher distances, and you'd never break up
		// an adjacent pair for non-adjacent ones
		while (index < nums.size()) {
			if (nums[index] - nums[index - 1] <= threshold) {
				npairs += 1;
				index++; // increment index by 2
			}
			index++;
		}

		return npairs;
	}

	/**
	 * Finds the p pairs with the smallest maximum distance betwen pairs
	 *
	 * @param nums array of numbers to pair
	 * @param p number of pairs to form
	 * @return smallest maximum distance b/w pairs
	 */
	int minimizeMax(vector<int>& nums, int p) {
		// sort for numPairs helper
		sort(nums.begin(), nums.end());

		// binary search for threshold distance
		int start = 0, end = nums.back() - nums[0], mid;
		while (end - start > 1) {
			mid = start + (end - start) / 2;
			if (numPairs(nums, mid) >= p) end = mid;
			else start = mid;
		}

		// check last 2 possible thresholds
		if (numPairs(nums, start) >= p) return start;
		else return end;
	}
};

/**
 * Test cases
 */
int main(void) {
	Solution sol;
	vector<int> nums;
	int p;

	// test case 1
	nums = { 10,1,2,7,1,3 };
	p = 2;
	std::cout << "minimizeMax(" << nums << "," << p << ") = ";
	std::cout << sol.minimizeMax(nums, p) << std::endl;

	// test case 2
	nums = { 4,2,1,2 };
	p = 1;
	std::cout << "minimizeMax(" << nums << "," << p << ") = ";
	std::cout << sol.minimizeMax(nums, p) << std::endl;

	nums = { 10,1,2,7,1,3 };
	p = 2;
	std::cout << "minimizeMax(" << nums << "," << p << ") = ";
	std::cout << sol.minimizeMax(nums, p) << std::endl;

	return 0;
}