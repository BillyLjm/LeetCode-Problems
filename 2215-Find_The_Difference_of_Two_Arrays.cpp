/*******************************************************************************
 * 2215-Find_The_Difference_of_Two_Arrays.cpp
 * Billy.Ljm
 * 03 May 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/find-the-difference-of-two-arrays/
 *
 * Given two 0-indexed integer arrays nums1 and nums2, return a list answer of
 * size 2 where:
 * - answer[0] is a list of all distinct integers in nums1 which are not present
 *   in nums2.
 * - answer[1] is a list of all distinct integers in nums2 which are not present
 *   in nums1.
 *
 * Note that the integers in the lists may be returned in any order.
 *
 * ===========
 * My Approach
 * ===========
 * We can create a hashmap of both arrays for O(1) lookup and to filter unique
 * elements. Then, we just have to iterate through one array and lookup if its
 * in the other
 *
 * This has a time complexity of O(n + m) and space complexity of O(n + m),
 * where n are m and the length of each array.
 ******************************************************************************/

#include <iostream>
#include <vector>
#include <unordered_set>

class Solution {
public:
	/**
	 * Finds the set difference of two arrays
	 *
	 * @param nums1 array to find difference of with nums2
	 * @param nums2 array to find difference of with nums1
	 *
	 * @return 2D vector of the non-overlapping elements of [nums1, nums2]
	 */
	std::vector<std::vector<int>> findDifference(std::vector<int>& nums1,
		std::vector<int>& nums2) {
		// create hashmap, and finds unique elements
		std::unordered_set<int> hash1, hash2;
		for (int num1 : nums1) {
			hash1.insert(num1);
		}
		for (int num2 : nums2) {
			hash2.insert(num2);
		}

		// swap to make hash1 smaller, to save some runtime
		if (nums1.size() > nums2.size()) {
			hash1.swap(hash2);
		}

		// iterate through nums2 and remember common elements
		std::unordered_set<int>::iterator it; // erasing while iterating
		for (it = hash1.begin(); it != hash1.end(); ) {
			if (hash2.find(*it) != hash2.end()) {
				hash2.erase(*it);
				it = hash1.erase(it);
			}
			else {
				it++;
			}
		}

		// unswap if needed
		if (nums1.size() > nums2.size()) {
			hash1.swap(hash2);
		}

		// convert hashsets to vectors
		std::vector<std::vector<int>> out = { {}, {} };
		for (int num1 : hash1) {
			out[0].push_back(num1);
		}
		for (int num2 : hash2) {
			out[1].push_back(num2);
		}

		return out;
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
	std::vector<int> nums1, nums2;

	// test case 1
	nums1 = { 1, 2, 3 };
	nums2 = { 2, 4, 6 };
	std::cout << "findDifference(" << nums1 << "," << nums2 << ") = " <<
		sol.findDifference(nums1, nums2) << std::endl;

	// test case 2
	nums1 = { 1, 2, 3, 3 };
	nums2 = { 1, 1, 2, 2 };
	std::cout << "findDifference(" << nums1 << "," << nums2 << ") = " <<
		sol.findDifference(nums1, nums2) << std::endl;

	return 0;
}