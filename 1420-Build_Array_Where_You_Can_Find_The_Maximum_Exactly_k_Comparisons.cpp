/*******************************************************************************
 * 1420-Build_Array_Where_You_Can_Find_The_Maximum_Exactly_k_Comparisons.cpp
 * Billy.Ljm
 * 07 October 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/build-array-where-you-can-find-the-maximum-exactly-k-comparisons/
 *
 * You are given three integers n, m and k. Consider the following algorithm to
 * find the maximum element of an array of positive integers:
 *
 * ```
 * maximum_values = -1
 * maximum_index = -1
 * search_cost = 0
 * n = arr.legnth
 * for (i = 0; i < n; i++) {
 *     if (maximum_value < arr[i]) {
 *         maximum_value = arr[i]
 *         maximum_index = i
 *         search_cost = search_cost + 1
 *     }
 * }
 * return maximum_index
 * ```
 *
 * You should build the array arr which has the following properties:
 * - arr has exactly n integers.
 * - 1 <= arr[i] <= m where (0 <= i < n).
 * - After applying the mentioned algorithm to arr, the value search_cost is
 *   equal to k.
 *
 * Return the number of ways to build the array arr under the mentioned
 * conditions. As the answer may grow large, the answer must be computed
 * modulo 10^9 + 7.
 *
 * ===========
 * My Approach
 * ===========
 * We can use dynamic programming to build compliant arrays of increasing length.
 * For each array, we need to know its length, the search cost so far, and the
 * maximum element in the list so far. If the search cost == k, then we can only
 * add elements smaller than the maximum element; and if the search cost <= k,
 * then we can add elements larger than the element and increment the search
 * cost.
 *
 * To save on memory, we can overwrite the dp table as we increase array length.
 * However, we have to overwrite tables with higher cost and maximum first,
 * since those depend on the lower cost and maximums.
 *
 * This has a time complexity of O(n * m * k), and space complexity of O(m * k),
 * where n is the size of the array, m is the maximum of the elements and k is
 * the maximum search cost.
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
	unsigned int MODVAL = 1000000007;

public:
	int numOfArrays(int n, int m, int k) {
		// dp[search cost - 1][max elem - 1]
		vector<vector<int>> dp(k, vector <int> (m, 0));

		// array length = 1
		for (int i = 0; i < m; i++) {
			dp[0][i] = 1;
		}

		// fill up dp table
		for (int lenn = 2; lenn <= n; lenn++) {
			for (int costt = k - 1; costt >= 0; costt--) {
				for (int maxx = m - 1; maxx >= 0; maxx--) {
					// add new elem more than current max
					if (costt < k - 1) {
						for (int nmax = maxx + 1; nmax < m; nmax++) {
							dp[costt + 1][nmax] = (0LL + dp[costt + 1][nmax] +
								dp[costt][maxx]) % MODVAL;
						}
					}
					// add new elem less than current max
					if (dp[costt][maxx] != 0) {
						dp[costt][maxx] = (1LL * dp[costt][maxx] * (maxx + 1))
							% MODVAL;
					}
				}
			}
		}

		// count search_cost = k
		int out = 0;
		for (int i : dp[k - 1]) {
			out = (0LL + out + i) % MODVAL;
		}
		return out;
	}
};

/**
 * Test cases
 */
int main(void) {
	Solution sol;
	int n, m, k;

	// test case 1
	n = 2;
	m = 3;
	k = 1;
	std::cout << "numOfArrays(" << n << "," << m << "," << k << ") = ";
	std::cout << sol.numOfArrays(n,m,k) << std::endl;

	// test case 2
	n = 5;
	m = 2;
	k = 3;
	std::cout << "numOfArrays(" << n << "," << m << "," << k << ") = ";
	std::cout << sol.numOfArrays(n, m, k) << std::endl;

	// test case 3
	n = 9;
	m = 1;
	k = 1;
	std::cout << "numOfArrays(" << n << "," << m << "," << k << ") = ";
	std::cout << sol.numOfArrays(n, m, k) << std::endl;

	return 0;
}