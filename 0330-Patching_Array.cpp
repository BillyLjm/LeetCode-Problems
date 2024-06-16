/*******************************************************************************
 * 0330-Patching_Array.cpp
 * Billy.Ljm
 * 16 June 2024
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/patching-array/
 *
 * Given a sorted integer array nums and an integer n, add/patch elements to the
 * array such that any number in the range [1, n] inclusive can be formed by the
 * sum of some elements in the array.
 *
 * Return the minimum number of patches required.
 *
 * ===========
 * My Approach
 * ===========
 * We will start from the first formable range [1,x] given the integer array.
 * Since x+1 is not in the range yet, we have to patch it in. The optimal and
 * greedy way is to patch x+1 into the integer array, which would extend the
 * formable range the most to [1,2x+1]. And if this extended range includes a
 * value already in the integer array, we must remember to extend the range with
 * that value since its a free extension.
 *
 * This has a time complexity of O(k + log n) and space complexity of O(1),
 * where k is the size of `nums` and n is the given argument `n`
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
	int minPatches(vector<int>& nums, int n) {
		int npatches = 0; // number of patches required
		long maxrange = nums[0] == 1 ? 1 : 0; // max of formable range
		int numsidx = nums[0] == 1 ? 1 : 0; // index for iterating nums

		// extend formable range
		while (maxrange < n) {
			// extend with given nums
			if (numsidx < nums.size() and nums[numsidx] <= maxrange + 1) {
				maxrange += nums[numsidx];
				numsidx++;
			}
			// extend by patching maxrange + 1
			else {
				maxrange += maxrange + 1;
				npatches++;
			}
		}

		return npatches;
	}
};

/**
 * Test cases
 */
int main(void) {
	Solution sol;
	int n;
	std::vector<int> nums;

	// test case 1
	n = 6;
	nums = { 1,3 };
	std::cout << "minPatches(" << nums << ", " << n << ") = ";
	std::cout << sol.minPatches(nums, n) << std::endl;

	// test case 2
	n = 20;
	nums = { 1,5,10 };
	std::cout << "minPatches(" << nums << ", " << n << ") = ";
	std::cout << sol.minPatches(nums, n) << std::endl;

	// test case 3
	n = 5;
	nums = { 1,2,2 };
	std::cout << "minPatches(" << nums << ", " << n << ") = ";
	std::cout << sol.minPatches(nums, n) << std::endl;

	return 0;
}