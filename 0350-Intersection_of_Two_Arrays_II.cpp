/*******************************************************************************
 * 0350-Intersection_of_Two_Arrays_II.cpp
 * Billy.Ljm
 * 02 July 2024
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/intersection-of-two-arrays-ii/
 *
 * Given two integer arrays nums1 and nums2, return an array of their
 * intersection. Each element in the result must appear as many times as it
 * shows in both arrays and you may return the result in any order.
 *
 * ===========
 * My Approach
 * ===========
 * We can make a set out of the smaller array, and iterate through the larger
 * array to check if each element is in the set.
 *
 * This has a time complexity of O(n log(m)) and space complexity of O(m), where
 * n and m are the length of the longer and shorter array respectively.
 ******************************************************************************/

#include <iostream>
#include <vector>
#include <set>

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
	vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
		vector<int> out;
		multiset<int> sett;
		vector<int> *shortarr, *longarr;

		// find longer and shroter array
		if (nums1.size() < nums2.size()) {
			shortarr = &nums1;
			longarr = &nums2;
		}
		else {
			shortarr = &nums2;
			longarr = &nums1;
		}

		// create set
		for (int i : *shortarr) {
			sett.insert(i);
		}

		// find intersect
		for (int i : *longarr) {
			auto itr = sett.find(i);
			if (itr != sett.end()) {
				out.push_back(i);
				sett.erase(itr);
			}
		}

		return out;
	}
};

/**
 * Test cases
 */
int main(void) {
	Solution sol;
	vector<int> nums1, nums2;

	// test case 1
	nums1 = { 1,2,2,1 };
	nums2 = { 2,2 };
	std::cout << "intersect(" << nums1 << ", " << nums2 << ") = ";
	std::cout << sol.intersect(nums1, nums2) << std::endl;

	// test case 2
	nums1 = { 4,9,5 };
	nums2 = { 9,4,9,8,4 };
	std::cout << "intersect(" << nums1 << ", " << nums2 << ") = ";
	std::cout << sol.intersect(nums1, nums2) << std::endl;

	return 0;
}