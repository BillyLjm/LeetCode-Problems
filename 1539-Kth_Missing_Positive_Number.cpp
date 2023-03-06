/*******************************************************************************
 * 1539-Kth_Missing_Positive_Number.cpp
 * Billy.Ljm
 * 06 Mar 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/kth-missing-positive-number/
 * Given an array arr of positive integers sorted in a strictly increasing
 * order, and an integer k. Return the kth positive integer that is missing from
 * this array
 *
 * ===========
 * My Approach
 * ===========
 * We can iterate every integer, until we reach the desired missing integer k.
 * Or, we can iterate through the input array, and use maths to calculate the
 * all the missing integers b/w adjacent elements in one fell swoop. I'll
 * implement the latter.
 ******************************************************************************/

#include <iostream>
#include <vector>

class Solution {
public:
	/**
	 * Finds the k-th positive integer that is missing from a sorted array
	 *
	 * @param arr sorted array to find missing integers in
	 * @param k number of missing positive integers to ignore
	 *
	 * @return the k-th missing positive integer
	 */
	int findKthPositive(std::vector<int>& arr, int k) {
		// process first interval [0, arr[0]]
		int nmiss = arr[0] - 1; // num missing integers b/w adjacent values
		if (nmiss < k) { // subtract any missing
			k -= nmiss;
		}
		else { // k is before start of array
			return k;
		}

		for (int i = 1; i < arr.size(); ++i) {
			nmiss = arr[i] - arr[i - 1] - 1;
			if (nmiss == 0) { // no missing integers, dont do anything
				continue;
			}
			else if (nmiss < k) { // nearer to k, but haven't reached
				k -= nmiss;
			}
			else { // reached k
				return arr[i-1] + k;
			}
		}

		// k is beyond end of arr
		return arr.back() + k;
	}
};

/**
 * Print function for vector
 */
template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& v) {
	os << "[";
	for (int i = 0; i < v.size(); ++i) {
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
	std::vector<int> arr;

	//test case 1
	arr = { 2, 3, 4, 7, 11 };
	std::cout << "findKthPositive(" << arr << ",5) = " <<
		sol.findKthPositive(arr, 5) << std::endl;

	//test case 2
	arr = { 1, 2, 3, 4 };
	std::cout << "findKthPositive(" << arr << ",2) = " <<
		sol.findKthPositive(arr, 2) << std::endl;

	//test case 2
	arr = { 2 };
	std::cout << "findKthPositive(" << arr << ",1) = " <<
		sol.findKthPositive(arr, 1) << std::endl;
}