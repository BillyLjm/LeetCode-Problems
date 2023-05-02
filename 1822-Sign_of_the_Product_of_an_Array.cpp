/*******************************************************************************
 * 1822-Sign_of_the_Product_of_an_Array.cpp
 * Billy.Ljm
 * 02 May 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/sign-of-the-product-of-an-array/
 * 
 * There is a function signFunc(x) that returns:
 * - 1 if x is positive.
 * - -1 if x is negative.
 * - 0 if x is equal to 0.
 *
 * You are given an integer array nums. Let product be the product of all values
 * in the array nums.
 *
 * Return signFunc(product).
 *
 * ===========
 * My Approach
 * ===========
 * We just have to calculate the sign of the product, not the numeric value.
 * Thus, we iterate through the array and if the integer is positive we don't
 * flip the sign, if it's negative we flip, and if it's zero we immediately
 * return.
 *
 * This has a time complexity of O(n) and space complexity of O(1), where n is
 * the length of the array.
 ******************************************************************************/

#include <iostream>
#include <vector>

/**
 * Solution
 */
class Solution {
public:
	/**
	 * Return the sign of the product of an integer array
	 *
	 * @param nums integer array to multiply
	 *
	 * @return 1 if the product is positive, -1 if negative, 0 if zero
	 */
	int arraySign(std::vector<int>& nums) {
		bool ispos = true;

		for (int num : nums) {
			if (num == 0) { // if zero, immediately return
				return 0;
			}
			else if (num < 0) { // if negative, flip sign
				ispos = !ispos;
			}
			// if positive, don't flip sign
		}

		return ispos ? 1 : -1;
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
	std::vector<int> nums;

	// test case 1
	nums = { -1, -2, -3, -4, 3, 2, 1 };
	std::cout << "arraySign(" << nums << ") = " << sol.arraySign(nums) << std::endl;

	// test case 2
	nums = { 1, 5, 0, 2, -3 };
	std::cout << "arraySign(" << nums << ") = " << sol.arraySign(nums) << std::endl;

	// test case 2
	nums = { -1, 1, -1, 1, -1 };
	std::cout << "arraySign(" << nums << ") = " << sol.arraySign(nums) << std::endl;

	return 0;
}