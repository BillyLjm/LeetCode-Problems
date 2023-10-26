/*******************************************************************************
 * 0823-Binary_Tree_with_Factors.cpp
 * Billy.Ljm
 * 26 October 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/binary-trees-with-factors/
 *
 * Given an array of unique integers, arr, where each integer arr[i] is strictly
 * greater than 1.
 *
 * We make a binary tree using these integers, and each number may be used for
 * any number of times. Each non-leaf node's value should be equal to the
 * product of the values of its children.
 *
 * Return the number of binary trees we can make. The answer may be too large so
 * return the answer modulo 10^9 + 7.
 *
 * ===========
 * My Approach
 * ===========
 * We will use dynamic programming to count the number of binary trees each
 * integer can be the root of. Each integer can be the root of a single node
 * tree. Besides that, we can try to find the factors of each integer, and we
 * can prepend the integer to the trees with its factors as its root. Thus, we
 * just have to start from the smallest integer and fill up the dp table.
 *
 * This has a time complexity of O(n sqrt(n)), and space complexity of O(n),
 * where n is the number of integers
 ******************************************************************************/

#include <iostream>
#include <vector>
#include <map>
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
	int numFactoredBinaryTrees(vector<int>& arr) {
		int modval = 1e9 + 7; // number to modulo over
		map<int, int> dp; // dp table
		sort(arr.begin(), arr.end()); // smallest val first

		// fill up dp table
		for (int i : arr) {
			// for single node tree
			dp[i] = 1; 
			for (int j : arr) {
				// only iterate lower half of factors
				if (sqrt(i) < j) break;
				// check if factor exists in matrix
				if (i % j != 0 || dp.count(i / j) == 0) continue;
				// account for other half of factors
				else if (i / j == j) dp[i] = (dp[i] + 1LL * dp[j] * dp[i/j]) % modval;
				else dp[i] = (dp[i] + 1LL * dp[j] * dp[i/j] * 2) % modval;
			}
		}

		// count all trees
		int out = 0;
		for (auto i : dp) out = (out + i.second) % modval;
		return out;
	}
};

/**
 * Test cases
 */
int main(void) {
	Solution sol;
	vector<int> arr;

	// test case 1
	arr = { 2,4 };
	std::cout << "numFactoredBinaryTrees(" << arr << ") = ";
	std::cout << sol.numFactoredBinaryTrees(arr) << std::endl;

	// test case 2
	arr = { 2,4,5,10 };
	std::cout << "numFactoredBinaryTrees(" << arr << ") = ";
	std::cout << sol.numFactoredBinaryTrees(arr) << std::endl;

	return 0;
}