/*******************************************************************************
 * 1269-Number_of_Ways_to_Stay_in_the_Same_Place_After_Some_Steps.cpp
 * Billy.Ljm
 * 15 October 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/number-of-ways-to-stay-in-the-same-place-after-some-steps/
 *
 * You have a pointer at index 0 in an array of size arrLen. At each step, you
 * can move 1 position to the left, 1 position to the right in the array, or
 * stay in the same place (The pointer should not be placed outside the array at
 * any time).
 *
 * Given two integers steps and arrLen, return the number of ways such that your
 * pointer is still at index 0 after exactly steps steps. Since the answer may
 * be too large, return it modulo 10^9 + 7.
 *
 * ===========
 * My Approach
 * ===========
 * We can use dynamic programming to calculate the number of ways to reach each
 * index at each step number. Additionally, we can only reach up to the steps-th
 * index by moving right every time, thus any larger indices can be ignored.
 *
 * This has a time complexity of O(n^2), and space complexity of O(n), where n
 * is the number of steps.
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
	int numWays(int steps, int arrLen) {
		arrLen = min(steps, arrLen); // ignore unreachable indices
		int modval = 1000000007;
		vector<int> prevdp;
		vector<int> dp(arrLen, 0);
		dp[0] = 1;

		for (int i = 0; i < steps; i++) {
			prevdp = dp;
			for (int j = 0; j < arrLen; j++) {
				// stay is already included by using previous dp
				if (j + 1 < arrLen) dp[j] = (0L + dp[j] + prevdp[j + 1]) % modval; // move left
				if (j - 1 >= 0) dp[j] = (0L + dp[j] + prevdp[j - 1]) % modval; // move right
			}
		}

		return dp[0];
	}
};

/**
 * Test cases
 */
int main(void) {
	Solution sol;
	int steps, arrLen;

	// test case 1
	steps = 3;
	arrLen = 2;
	std::cout << "numWays(" << steps << "," << arrLen << ") = ";
	std::cout << sol.numWays(steps, arrLen) << std::endl;

	// test case 2
	steps = 2;
	arrLen = 4;
	std::cout << "numWays(" << steps << "," << arrLen << ") = ";
	std::cout << sol.numWays(steps, arrLen) << std::endl;

	// test case 3
	steps = 4;
	arrLen = 2;
	std::cout << "numWays(" << steps << "," << arrLen << ") = ";
	std::cout << sol.numWays(steps, arrLen) << std::endl;

	return 0;
}