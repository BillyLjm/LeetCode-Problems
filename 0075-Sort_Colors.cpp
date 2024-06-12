/*******************************************************************************
 * 0075-Sort_Colors.cpp
 * Billy.Ljm
 * 12 June 2024
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/sort-colors/
 *
 * Given an array nums with n objects colored red, white, or blue, sort them
 * in-place so that objects of the same color are adjacent, with the colors in
 * the order red, white, and blue.
 *
 * We will use the integers 0, 1, and 2 to represent the color red, white, and
 * blue, respectively.
 *
 * You must solve this problem without using the library's sort function.
 *
 * ===========
 * My Approach
 * ===========
 * Since there are only 3 values, we can use counting sort where we just count
 * the occurrences of each values and sort them later. Additionally, since the
 * values are fungible, we can create/delete them instead of swapping them.
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
	void sortColors(vector<int>& nums) {
		// count number of occurences of each value
		vector<int> count(3, 0);
		for (int i = 0; i < nums.size(); i++) {
			count[nums[i]]++;
		}

		// create sorted list
		for (int i = 0; i < nums.size(); i++) {
			if (i < count[0]) {
				nums[i] = 0;
			}
			else if (i < count[0] + count[1]) {
				nums[i] = 1;
			}
			else {
				nums[i] = 2;
			}
		}
	}
};

/**
 * Test cases
 */
int main(void) {
	Solution sol;
	vector<int> nums;

	// test case 1
	nums = { 2,0,2,1,1,0 };
	std::cout << "sortColors(" << nums << ") = ";
	sol.sortColors(nums);
	std::cout << nums << std::endl;

	// test case 2
	nums = { 2,0,1 };
	std::cout << "sortColors(" << nums << ") = ";
	sol.sortColors(nums);
	std::cout << nums << std::endl;

	return 0;
}