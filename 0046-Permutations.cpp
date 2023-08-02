/*******************************************************************************
 * 0046-Permutations.cpp
 * Billy.Ljm
 * 02 August 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/permutations/
 *
 * Given an array nums of distinct integers, return all the possible
 * permutations. You can return the answer in any order.
 *
 * ===========
 * My Approach
 * ===========
 * Since we have to generate each possible permutation, we have no choice but to
 * iterate through each of them. Luckily, C++ has an inbuilt function for
 * iterating through permutations, which we'll use.
 *
 * This has a time complexity of O(n * n!), and a space complexity of O(n!),
 * where n is the length of the array.
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
	vector<vector<int>> permute(vector<int>& nums) {
		vector<vector<int>> out;

		sort(nums.begin(), nums.end());
		do {
			out.push_back(vector<int>());
			copy(nums.begin(), nums.end(), back_inserter(out.back()));
		} while (next_permutation(nums.begin(), nums.end()));

		return out;
	}
};

/**
 * Test cases
 */
int main(void) {
	Solution sol;
	vector<int> nums;

	// test case 1
	nums = { 1, 2, 3 };
	std::cout << "permute(" << nums << ") = ";
	std::cout << sol.permute(nums) << std::endl;

	// test case 2
	nums = { 0, 1 };
	std::cout << "permute(" << nums << ") = ";
	std::cout << sol.permute(nums) << std::endl;

	// test case 3
	nums = { 1 };
	std::cout << "permute(" << nums << ") = ";
	std::cout << sol.permute(nums) << std::endl;

	return 0;
}