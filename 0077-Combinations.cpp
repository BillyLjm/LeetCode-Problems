/*******************************************************************************
 * 0077-Combinations.cpp
 * Billy.Ljm
 * 01 August 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/combinations/
 *
 * Given two integers n and k, return all possible combinations of k numbers
 * chosen from the range [1, n].
 *
 * You may return the answer in any order.
 *
 * ===========
 * My Approach
 * ===========
 * Since we have to generate each possible combination, we have no choice but to
 * iterate through each of them. We'll do this recursively, up to k depth.
 *
 * This has a time complexity of O(n choose k), and a space complexity of
 * O(n choose k), where n and k are the specified arguments.
 ******************************************************************************/

#include <iostream>
#include <vector>
#include <numeric>

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
		vector<vector<int>> combine(int n, int k) {
			// base case
			if (k == 0 or k > n) {
				return vector<vector<int>>(1, vector<int>());
			}
			else if (k == n) {
				vector<vector<int>> out (1, vector<int>(k));
				iota(out[0].begin(), out[0].end(), 1);
				return out;
			}
			// recursively build larger k's
			else {
				vector<vector<int>> out;
				for (int i = n; i >= k; i--) {
					// i will be the last element of the list
					vector<vector<int>> rec = combine(i - 1, k - 1);
					for (int j = 0; j < rec.size(); j++) {
						rec[j].push_back(i);
					}
					// concat to output
					out.insert(out.end(), rec.begin(), rec.end());
				}
				return out;
			}
		}
};

/**
 * Test cases
 */
int main(void) {
	Solution sol;
	int n, k;

	// test case 1
	n = 4;
	k = 2;
	std::cout << "combine(" << n << ", " << k << ") = ";
	std::cout << sol.combine(n, k) << std::endl;

	// test case 2
	n = 1;
	k = 1;
	std::cout << "combine(" << n << ", " << k << ") = ";
	std::cout << sol.combine(n, k) << std::endl;

	return 0;
}