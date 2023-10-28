/*******************************************************************************
 * 1220-Count_Vowels_Permutation.cpp
 * Billy.Ljm
 * 28 October 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/count-vowels-permutation/
 *
 * Given an integer n, your task is to count how many strings of length n can be
 * formed under the following rules:
 * - Each character is a lower case vowel ('a', 'e', 'i', 'o', 'u')
 * - Each vowel 'a' may only be followed by an 'e'.
 * - Each vowel 'e' may only be followed by an 'a' or an 'i'.
 * - Each vowel 'i' may not be followed by another 'i'.
 * - Each vowel 'o' may only be followed by an 'i' or a 'u'.
 * - Each vowel 'u' may only be followed by an 'a'.
 *
 * Since the answer may be too large, return it modulo 10^9 + 7.
 *
 * ===========
 * My Approach
 * ===========
 * We will use dynamic programming to count the number of strings of increasing 
 * lengths ending with each vowel.
 *
 * This has a time complexity of O(n) and space complexity of O(1), where n is
 * the length of the string.
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
	int countVowelPermutation(int n) {
		int modval = 1e9 + 7;
		int a = 1, e = 1, i = 1, o = 1, u = 1;
		int na, ne, ni, no, nu;

		for (int ii = 2; ii <= n; ii++) {
			// calculate new values
			na = (0L + e + i + u) % modval;
			ne = (0L + a + i) % modval;
			ni = (0L + e + o) % modval;
			no = i;
			nu = (0L + i + o) % modval;
			// update new values
			a = na;
			e = ne;
			i = ni;
			o = no;
			u = nu;
		}

		return (0L + a + e + i + o + u) % modval;
	}
};

/**
 * Test cases
 */
int main(void) {
	Solution sol;
	int n;

	// test case 1
	n = 1;
	std::cout << "countVowelPermutation(" << n << ") = ";
	std::cout << sol.countVowelPermutation(n) << std::endl;

	// test case 2
	n = 2;
	std::cout << "countVowelPermutation(" << n << ") = ";
	std::cout << sol.countVowelPermutation(n) << std::endl;

	// test case 3
	n = 5;
	std::cout << "countVowelPermutation(" << n << ") = ";
	std::cout << sol.countVowelPermutation(n) << std::endl;

	return 0;
}