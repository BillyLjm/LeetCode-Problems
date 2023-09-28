/*******************************************************************************
 * 0905-Sort_Array_by_Parity.cpp
 * Billy.Ljm
 * 28 September 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/sort-array-by-parity/
 *
 * Given an integer array nums, move all the even integers at the beginning of
 * the array followed by all the odd integers.
 *
 * Return any array that satisfies this condition.
 *
 * ===========
 * My Approach
 * ===========
 * We can iterate through the array, swapping any even integers to the front
 * and odd integers to the back.
 *
 * This has a time complexity of O(n), and a space complexity of O(1), where n
 * is the size of the array.
 ******************************************************************************/

#include <iostream>
#include <vector>
#include <string>

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
	vector<int> sortArrayByParity(vector<int>& nums) {
		int front = 0, back = nums.size() - 1; // index of sorted sections

		while (front != back) {
			// keep even integers at front
			if (nums[front] % 2 == 0) {
				front++;
			}
			// swap odd integers to back
			else {
				swap(nums[front], nums[back]);
				back--;
			}
		}

		return nums;
	}
};

/**
 * Test cases
 */
int main(void) {
	Solution sol;
	vector<int> nums;

	// test case 1
	nums = { 3,1,2,4 };
	std::cout << "sortArrayByParity(" << nums << ") = ";
	std::cout << sol.sortArrayByParity(nums) << std::endl;

	// test case 2
	nums = { 0 };
	std::cout << "sortArrayByParity(" << nums << ") = ";
	std::cout << sol.sortArrayByParity(nums) << std::endl;

	return 0;
}