/*******************************************************************************
 * 2009-Minimum_Number_of_Operations_to_Make_Array_Continuous.cpp
 * Billy.Ljm
 * 10 October 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/minimum-number-of-operations-to-make-array-continuous/
 *
 * You are given an integer array nums. In one operation, you can replace any
 * element in nums with any integer.
 *
 * nums is considered continuous if both of the following conditions are
 * fulfilled:
 * - All elements in nums are unique.
 * - The difference between the maximum element and the minimum element in nums
 *   equals nums.length - 1.
 *
 * For example, nums = [4, 2, 5, 3] is continuous, but nums = [1, 2, 3, 5, 6] is
 * not continuous.
 *
 * Return the minimum number of operations to make nums continuous.
 *
 * ===========
 * My Approach
 * ===========
 * We can guess a minimum element (and thus maximum element) of the continuous
 * array. Then, we just have to count how many element of the given array do not
 * appear in the continuous array; these elements will have to be replaced. We
 * have to check for all minimum elements between min(nums) and max(nums) - n.
 * And to check this efficiently, we can count how many elements entered or
 * exited a sliding window b/w iterations.
 *
 * This has a time complexity of O(n log n), and space complexity of O(n), where
 * n is the size of the array
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
	int minOperations(vector<int>& nums) {
		int n = nums.size() - 1;
		int count = 0, maxcount = 0; // count of elements in window

		// sort & get unique elements
		set<int> unique(nums.begin(), nums.end());

		// create first sliding window of [min(nums), min(nums) + n]
		auto minit = unique.begin();
		auto maxit = unique.end()--;
		for (auto it = unique.begin(); it != unique.end(); it++) {
			if (*it <= *minit + n) count++;
			else {
				maxit = it;
				break;
			}
		}
		maxcount = count;

		// slide window
		while (maxit != unique.end()) {
			// move to next element
			minit++;
			count--;
			// update window to include new elements
			while (maxit != unique.end() and *maxit <= *minit + n) {
				count++;
				maxit++;
			}
			// remember max count
			maxcount = max(maxcount, count);
		}

		return n + 1 - maxcount;
	}
};

/**
 * Test cases
 */
int main(void) {
	Solution sol;
	vector<int> nums;

	// test case 1
	nums = { 4,2,5,3 };
	std::cout << "minOperations(" << nums << ") = ";
	std::cout << sol.minOperations(nums) << std::endl;

	// test case 2
	nums = { 1,2,3,5,6 };
	std::cout << "minOperations(" << nums << ") = ";
	std::cout << sol.minOperations(nums) << std::endl;

	// test case 3
	nums = { 41,33,29,33,35,26,47,24,18,28 };
	std::cout << "minOperations(" << nums << ") = ";
	std::cout << sol.minOperations(nums) << std::endl;

	return 0;
}