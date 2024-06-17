/*******************************************************************************
 * 0633-Sum_of_Square_Numbers.cpp
 * Billy.Ljm
 * 17 June 2024
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/sum-of-square-numbers/
 *
 * Given a non-negative integer c, decide whether there're two integers a and b
 * such that a^2 + b^2 = c.
 *
 * ===========
 * My Approach
 * ===========
 * I assume that we want to avoid using sqrt since it can be a time-intensive
 * computation. Thus, we just have to guess a and b within an integer range of
 * [1, floor(sqrt(c))]. However, we also know that small a's have to be paired
 * with large b's to add up to c, and thus a and b are on opposite end of the
 * integer range. Thus, the algorithm is just walking of two pointers across
 * the integer range until they meet in the middle.
 *
 * This has a time complexity of O(sqrt(c)) and space complexity of O(1),
 * where c is the given argument `c`.
 ******************************************************************************/

#include <iostream>
#include <vector>
#include <cmath>

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
	bool judgeSquareSum(int c) {
		int a = 0;
		int b;
		long tmp;

		// binary search ~sqrt(c)
		int min = 0, max = c;
		while (max >= min) {
			b = (min + max) / 2;
			tmp = 1L * b * b;
			if (tmp == c) {
				return true;
			}
			else if (tmp > c) {
				max = b - 1;
			}
			else {
				min = b + 1;
			}
		}

		// linear search a^2 + b^2 = c
		while (b >= a) {
			tmp = 1L * a * a + 1L * b * b;
			if (tmp == c) {
				return true;
			}
			else if (tmp > c) {
				b--;
			}
			else {
				a++;
			}
		}

		return false;
	}
};

/**
 * Test cases
 */
int main(void) {
	Solution sol;
	int c;

	// test case 1
	c = 5;
	std::cout << "judgeSquareSum(" << c << ") = ";
	std::cout << std::boolalpha << sol.judgeSquareSum(c) << std::endl;

	// test case 2
	c = 3;
	std::cout << "judgeSquareSum(" << c << ") = ";
	std::cout << std::boolalpha << sol.judgeSquareSum(c) << std::endl;

	return 0;
}