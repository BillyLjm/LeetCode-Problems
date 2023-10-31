/*******************************************************************************
 * 2433-Find_the_Original_Array_of_Prefix_XOR.cpp
 * Billy.Ljm
 * 31 October 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/find-the-original-array-of-prefix-xor/
 *
 * You are given an integer array pref of size n. Find and return the array arr
 * of size n that satisfies:
 * - pref[i] = arr[0] ^ arr[1] ^ ... ^ arr[i].
 *
 * Note that ^ denotes the bitwise-xor operation.
 *
 * It can be proven that the answer is unique.
 *
 * ===========
 * My Approach
 * ===========
 * The condition simplifies to pref[i-1] ^ pref[i] = arr[i]. So, we can
 * calculate the XOR's one by one, iteratively.
 *
 * This has a time complexity of O(n) and space complexity of O(1), where n is
 * the size of the array.
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
	vector<int> findArray(vector<int>& pref) {
		for (int i = pref.size() - 1; i > 0; i--) {
			pref[i] = pref[i] ^ pref[i - 1];
		}
		return pref;
	}
};

/**
 * Test cases
 */
int main(void) {
	Solution sol;
	vector<int> pref;

	// test case 1
	pref = { 5,2,0,3,1 };
	std::cout << "findArray(" << pref << ") = ";
	std::cout << sol.findArray(pref) << std::endl;

	// test case 2
	pref = { 13 };
	std::cout << "findArray(" << pref << ") = ";
	std::cout << sol.findArray(pref) << std::endl;

	return 0;
}