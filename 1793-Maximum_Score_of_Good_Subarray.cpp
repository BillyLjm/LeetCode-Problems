/*******************************************************************************
 * 1793-Maximum_Score_of_Good_Subarray.cpp
 * Billy.Ljm
 * 22 October 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/maximum-score-of-a-good-subarray/
 *
 * You are given an array of integers nums (0-indexed) and an integer k.
 *
 * The score of a subarray (i, j) is defined as min(nums[i], nums[i+1], ...,
 * nums[j]) * (j - i + 1). A good subarray is a subarray where i <= k <= j.
 *
 * Return the maximum possible score of a good subarray.
 *
 * ===========
 * My Approach
 * ===========
 * To maximise the score, we want to choose the longest subarray around the k-th
 * element with largest minimum value. So we can do this greedily by starting
 * with just the k-th element, and then adding the larger of the value to the
 * left or right of our subarray; essentially calculating the max score for each
 * subarray length. Then, we just have to return the max score for all lengths.
 *
 * This has a time complexity of O(n), and space complexity of O(1), where n is
 * the length of the array.
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
	int maximumScore(vector<int>& nums, int k) {
		// subarray = {nums[k]}
		int i = k, j = k; // left, right boundary of subarray
		int minele = nums[k];
		int maxscore = minele * (j - i + 1);

		// add left or right element
		while (j - i < nums.size() - 1) {
			if (i - 1 >= 0 && (j + 1 >= nums.size() || nums[i - 1] > nums[j + 1])) {
				minele = min(minele, nums[i - 1]);
				i--;
				maxscore = max(maxscore, minele * (j - i + 1));
			}
			else {
				minele = min(minele, nums[j + 1]);
				j++;
				maxscore = max(maxscore, minele * (j - i + 1));
			}
		}

		return maxscore;
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
	nums = { 1,4,3,7,4,5 };
	k = 3;
	std::cout << "maximumScore(" << nums << "," << k << ") = ";
	std::cout << sol.maximumScore(nums, k) << std::endl;

	// test case 2
	nums = { 5,5,4,5,4,1,1,1 };
	k = 0;
	std::cout << "maximumScore(" << nums << "," << k << ") = ";
	std::cout << sol.maximumScore(nums, k) << std::endl;

	return 0;
}