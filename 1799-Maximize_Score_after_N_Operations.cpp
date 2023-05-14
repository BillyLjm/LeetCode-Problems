/*******************************************************************************
 * 1799-Maximize_Score_after_N_Operations.cpp
 * Billy.Ljm
 * 14 May 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/maximize-score-after-n-operations/
 *
 * You are given nums, an array of positive integers of size 2 * n. You must
 * perform n operations on this array.
 *
 * In the ith operation (1-indexed), you will:
 * - Choose two elements, x and y.
 * - Receive a score of i * gcd(x, y).
 * - Remove x and y from nums.
 *
 * Return the maximum score you can receive after performing n operations.
 *
 * The function gcd(x, y) is the greatest common divisor of x and y.
 *
 * ===========
 * My Approach
 * ===========
 * We have to consider all pairings to determine which yields the maximum score.
 * However, we can use dynamic programming to speed it up, since [a,b,c,d,...]
 * can be split into [[a,b],[c,d],[...]] or [[a,c],[b,d],[...]]. In both cases,
 * we need to find maximum score of [...], which will be calculated only once
 * with dynamic programming. We will index the dynamic programming table using
 * an array of booleans indicating if the element has yet to be paired, and
 * converting it to an integer
 *
 * This has a time complexity of O(4^n * n^2 * log A) and space complexity of 
 * O(4^n), where n is size of the array and A is the elemnts in the array.
 ******************************************************************************/

#include <iostream>
#include <vector>

/**
 * Solution
 */
class Solution {
private:
	/**
	 * Finds the greatest common denominator, via the Euclidean algorithm
	 *
	 * @param x number to find GCD of wrt y
	 * @param y number to find GCD of wrt x
	 *
	 * @return greatest common denominator of x and y
	 */
	int gcd(int x, int y) {
		if (x < y) {
			return gcd(y, x);
		}
		else if (y == 0) {
			return x;
		}
		else {
			return gcd(y, x % y);
		}
	}

	/**
	 * Recursively finds the maximum score attainable, as described above
	 *
	 * @param bitstr i-th element represent in nums[i] has yet to be paired
	 * @param nums numbers to pair
	 * @param dp dynamic programming table; dp[bitstr] = max score for bitstr
	 * @param depth current recursion depth
	 *
	 * @return maximum score attainable
	 */
	int recurse(int bitstr, int depth, const std::vector<int>& nums, std::vector<int>& dp) {
		int score;

		// base case
		if (bitstr == 0) { 
			return 0;
		}
		// if already calculated
		else if (dp[bitstr] != 0) {
			return dp[bitstr];
		}
		// else create a pair and recurse
		else {
			// choose bitstr[i] = 1
			for (int i = 0; i < nums.size(); i++) {
				if ((bitstr & (1 << i)) == 0) continue;
				// choose bitstr[j] = 1
				for (int j = i + 1; j < nums.size(); j++) {
					if ((bitstr & (1 << j)) == 0) continue;
					// pair i, j and recurse
					score = recurse(bitstr & ~(1 << i) & ~(1 << j),
						depth + 1, nums, dp);
					score = score + depth * gcd(nums[i], nums[j]);
					// fill table
					dp[bitstr] = std::max(dp[bitstr], score);
				}
			}
			// return after all pairs considered
			return dp[bitstr];
		}
	}

public:
	/**
	 * Finds the maximum score attainable, as described above
	 *
	 * @param nums vector of numbers to pair
	 *
	 * @return maximum score attainable
	 */
	int maxScore(std::vector<int>& nums) {
		// dp[bitstring] = max score if bitstring[i] means ith number not paired
		std::vector<int> dp (1 << nums.size(), 0);

		// recursively find maximum score
		return recurse((1 << nums.size()) - 1, 1, nums, dp);
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
	std::vector<int> nums;

	// test case 1
	nums = { 1, 2 };
	std::cout << "maxScore(" << nums << ") = " << sol.maxScore(nums) << std::endl;

	// test case 2
	nums = { 3, 4, 6, 8 };
	std::cout << "maxScore(" << nums << ") = " << sol.maxScore(nums) << std::endl;

	// test case 3
	nums = { 1, 2, 3, 4, 5, 6 };
	std::cout << "maxScore(" << nums << ") = " << sol.maxScore(nums) << std::endl;

	return 0;
}