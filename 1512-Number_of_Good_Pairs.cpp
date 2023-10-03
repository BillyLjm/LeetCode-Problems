/*******************************************************************************
 * 1512-Number_of_Good_Pairs.cpp
 * Billy.Ljm
 * 03 October 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/number-of-good-pairs/
 *
 * Given an array of integers nums, return the number of good pairs.
 *
 * A pair (i, j) is called good if nums[i] == nums[j] and i < j.
 *
 * ===========
 * My Approach
 * ===========
 * We can iterate through the array, updating the number of occurrences of each
 * number. At each number, we can then form as many good pairs as the current
 * number of occurrences of that specific number.
 *
 * This has a time complexity of O(n), and a space complexity of O(n), where n
 * is the size of the array
 ******************************************************************************/

#include <iostream>
#include <vector>
#include <map>

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
	int numIdenticalPairs(vector<int>& nums) {
		int numpairs = 0; // number of good pairs
		map<int, int> count; // count of each number

		// count number of pairs
		for (int num : nums) {
			numpairs += count[num];
			count[num]++;
		}

		return numpairs;
	}
};

/**
 * Test cases
 */
int main(void) {
	Solution sol;
	vector<int> nums;

	// test case 1
	nums = { 1,2,3,1,1,3 };
	std::cout << "numIdenticalPairs(" << nums << ") = ";
	std::cout << sol.numIdenticalPairs(nums) << std::endl;

	// test case 2
	nums = { 1,1,1,1 };
	std::cout << "numIdenticalPairs(" << nums << ") = ";
	std::cout << sol.numIdenticalPairs(nums) << std::endl;

	// test case 3
	nums = { 1,2,3 };
	std::cout << "numIdenticalPairs(" << nums << ") = ";
	std::cout << sol.numIdenticalPairs(nums) << std::endl;

	return 0;
}