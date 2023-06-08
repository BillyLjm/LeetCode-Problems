/*******************************************************************************
 * 1502-Can_Make_Arithmetic_Progression_From_Sequence.cpp
 * Billy.Ljm
 * 06 June 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/can-make-arithmetic-progression-from-sequence/
 *
 * A sequence of numbers is called an arithmetic progression if the difference
 * between any two consecutive elements is the same.
 *
 * Given an array of numbers arr, return true if the array can be rearranged to
 * form an arithmetic progression. Otherwise, return false.
 *
 * ===========
 * My Approach
 * ===========
 * Assuming the array can form an arithmetic progression, we can easily know the
 * first term which will be the minimum, and the common difference via (max -
 * min) / size`. Then, we just have to iterate again through the array, ensuring
 * all terms adhere to the rules and that are no repeated numbers
 *
 * This has a time complexity of O(n) and space complexity of O(n), where n is
 * the size of the array.
 ******************************************************************************/

#include <iostream>
#include <vector>

/**
 * Solution
 */
class Solution {
public:
	/**
	 * Determines if an array can be rearranged to form an arithmetic progression
	 *
	 * @param arr array to rearrange
	 *
	 * @return true if array can be rearranged into an arithmetic progression
	 */
	bool canMakeArithmeticProgression(std::vector<int>& arr) {
		// find min and max, and common difference
		int minn = INT_MAX;
		int maxx = INT_MIN;
		for (int ele : arr) {
			if (ele < minn) minn = ele;
			if (ele > maxx) maxx = ele;
		}
		int diff = (maxx - minn) / (arr.size() - 1);
		if ((maxx - minn) % (arr.size() - 1) != 0) return false; // non-integer difference
		else if (diff == 0) return true; // all terms are the same
		

		// check if all terms are valid
		std::vector<bool> found(arr.size(), false);
		for (int ele : arr) {
			if ((ele - minn) % diff != 0) return false; // not arithmetic progression
			else if ((ele - minn) / diff >= arr.size()) return false; // out of bounds
			else if (found[(ele - minn) / diff]) return false; // duplicate value
			found[(ele - minn) / diff] = true;
		}

		return true;
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
	std::vector<int> arr;

	// test case 1
	arr = { 3, 5, 1 };
	std::cout << "canMakeArithmeticProgression(" << arr << ") = ";
	std::cout << std::boolalpha << sol.canMakeArithmeticProgression(arr) << std::endl;

	// test case 2
	arr = { 1, 2, 4 };
	std::cout << "canMakeArithmeticProgression(" << arr << ") = ";
	std::cout << std::boolalpha << sol.canMakeArithmeticProgression(arr) << std::endl;

	return 0;
}