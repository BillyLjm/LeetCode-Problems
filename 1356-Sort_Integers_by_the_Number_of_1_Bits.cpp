/*******************************************************************************
 * 1356-Sort_Integers_by_the_Number_of_1_Bits.cpp
 * Billy.Ljm
 * 30 October 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/sort-integers-by-the-number-of-1-bits/
 *
 * You are given an integer array arr. Sort the integers in the array in
 * ascending order by the number of 1's in their binary representation and in
 * case of two or more integers have the same number of 1's you have to sort
 * them in ascending order.
 *
 * Return the array after sorting it.
 *
 * ===========
 * My Approach
 * ===========
 * We'll use the default sort operator with a custom comparator calculating the
 * number of 1 bits with Brian Kerninghan's algorithm.
 *
 * This has a time complexity of O(n log n) and space complexity of O(log n),
 * where n is the length of the array; identical to plain sorting since ints
 * have fixed number of bits and counting them takes constant time.
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
	int countbits(int val) {
		int count = 0;
		while (val > 0) {
			count++;
			val = val & (val - 1);
		}
		return count;
	}

	vector<int> sortByBits(vector<int>& arr) {
		sort(arr.begin(), arr.end(), [this](int left, int right) {
			int nleft = countbits(left);
			int nright = countbits(right);
			if (nleft != nright) return nleft < nright;
			else return left < right;
		});
		return arr;
	}
};

/**
 * Test cases
 */
int main(void) {
	Solution sol;
	vector<int> arr;

	// test case 1
	arr = { 0,1,2,3,4,5,6,7,8 };
	std::cout << "sortByBits(" << arr << ") = ";
	std::cout << sol.sortByBits(arr) << std::endl;

	// test case 2
	arr = { 1024,512,256,128,64,32,16,8,4,2,1 };
	std::cout << "sortByBits(" << arr << ") = ";
	std::cout << sol.sortByBits(arr) << std::endl;

	return 0;
}