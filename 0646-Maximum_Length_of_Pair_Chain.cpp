/*******************************************************************************
 * 0646-Maximum_Length_of_Pair_Chain.cpp
 * Billy.Ljm
 * 26 August 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/maximum-length-of-pair-chain/
 *
 * You are given an array of n pairs pairs where pairs[i] = [lefti, righti] and
 * lefti < righti.
 *
 * A pair p2 = [c, d] follows a pair p1 = [a, b] if b < c. A chain of pairs can
 * be formed in this fashion.
 *
 * Return the length longest chain which can be formed.
 *
 * ===========
 * My Approach
 * ===========
 * We can use dynamic programming to calculate the longest chain in [-k,-k+1],
 * which informs that of [-k,-k+2] and so on. To make it more efficient, instead
 * of incrementing the right limit by 1, we can increment it by the next right
 * value present in the pairs. Then, it becomes just iterating through the pairs
 * in increasing right value and greedily picking all valid pairs.
 *
 * This has a time complexity of O(n log n), and a space complexity of O(1),
 * where n is the number of pairs.
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
	int findLongestChain(vector<vector<int>>& pairs) {
		// sort in increasing right values
		sort(pairs.begin(), pairs.end(),
			[](vector<int> i, vector<int> j) { return i[1] < j[1]; });

		// greedily pick valid pairs
		int nchain = 0; // number of pairs in chain
		int curr = pairs[0][0] - 1; // current right limit
		for (vector<int> pair : pairs) {
			if (pair[0] > curr) {
				nchain++;
				curr = pair[1];
			}
		}

		return nchain;
	}
};

/**
 * Test cases
 */
int main(void) {
	Solution sol;
	vector<vector<int>> pairs;

	// test case 1
	pairs = { {1,2},{2,3},{3,4} };
	std::cout << "findLongestChain(" << pairs << ") = ";
	std::cout << sol.findLongestChain(pairs) << std::endl;

	// test case 2
	pairs = { {1,2},{7,8},{4,5} };
	std::cout << "findLongestChain(" << pairs << ") = ";
	std::cout << sol.findLongestChain(pairs) << std::endl;

	return 0;
}