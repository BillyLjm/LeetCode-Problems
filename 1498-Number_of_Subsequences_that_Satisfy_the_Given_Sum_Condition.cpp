/*******************************************************************************
 * 1498-Number_of_Subsequences_that_Satisfy_the_Given_Sum_Condition.cpp
 * Billy.Ljm
 * 06 May 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/number-of-subsequences-that-satisfy-the-given-sum-condition/
 *
 * You are given an array of integers nums and an integer target.
 *
 * Return the number of non-empty subsequences of nums such that the sum of the
 * minimum and maximum element on it is less or equal to target. Since the
 * answer may be too large, return it modulo 10^9 + 7.
 *
 * ===========
 * My Approach
 * ===========
 * We can sort the array, then pair the smallest element with the next largest
 * element which still satisfies the sum condition, using binary search. The
 * number of subsequences is then all permutations (w/ removal) of the subarrays
 * bounded by these two elements, which can be directly calculated with the
 * indices. We then have to repeat this for the next smallest element and so on.
 *
 * We also have to use (binary) modular exponentiation instead of std::pow, 
 * since the exponents can be so huge that no data types can contain it.
 *
 * This has a time complexity of O(n * log(n)) and space complexity of O(1), 
 * where n is the length of the array of integers.
 ******************************************************************************/

#include <iostream>
#include <vector>
#include <algorithm>

/**
 * Solution
 */
class Solution {
private:
	/**
	 * Binary search for the largest element in a sorted sub-array which is 
	 * smaller than a specified maximum
	 *
	 * @param nums array to search in (sorted in ascending order)
	 * @param start index to start searching from
	 * @param end index to end searching at
	 * @param maxx the upper bound of the element to search for
	 *
	 * @return index of the largest element in nums[start:end] which is smaller
	 * than maxx. If there are no elemnts, return -1.
	 */
	size_t binarySearch(std::vector<int>& nums, size_t start, size_t end,
		int maxx) {
		size_t mid = start + (end - start) / 2;

		// if indices don't make sense, return
		if (end < start) {
			return -1;
		}

		while (end - start > 1) {
			// if number does not exist return
			if (nums[start] > maxx) {
				return -1;
			}
			// else do binary search loop
			else if (nums[mid] > maxx) {
				end = mid;
			}
			else {
				start = mid;
			}
			mid = start + (end - start) / 2;
		}

		// check last elments and return
		return nums[end] <= maxx ? end : start;
	}

	/**
	 * Calculates a modular exponentiation
	 *
	 * @param base base of exponent
	 * @param exp power of exponent
	 * @param mod number to take modulus around
	 *
	 * @return base^exp % mod
	 */
	int modularExponent(int base, int exp, int mod) {
		int result = 1; // to return

		// loop through each bit of exp
		while (exp > 0) {
			// if bit is 1, multiply result by base
			if (exp & 1) {
				result = (1L * result * base) % mod;
			}
			// square base and divide exp by 2
			base = (1L * base * base) % mod;
			exp >>= 1;
		}

		return result;
	}

public:
	/**
	 * Finds number of subsequences where the maximum and minimum elements sum
	 * to less than a specified target
	 *
	 * @param nums array to find subseqeunces in
	 * @param target target to keep sum of max and min elements under
	 *
	 * @return number of subsequences whose max and min elements sum to less
	 *         than target
	 */
	int numSubseq(std::vector<int>& nums, int target) {
		int mod = 1e9 + 7; // value to take modulus over
		int numseq = 0; // number of subsequences; to return
		size_t j = nums.size() - 1; // index of next largest element which satisifies sum
		std::sort(nums.begin(), nums.end()); // sort array

		for (size_t i = 0; i < nums.size(); i++) {
			// find next largest element which is the biggest set
			j = binarySearch(nums, i, j, target - nums[i]);
			// if no element, break loop and return
			if (j == -1) {
				break;
			}
			// if only one element, check sum w/ itself
			else if (j == i) {
				if (nums[i] * 2 <= target) {
					numseq++;
				}
			}
			// else calculate all subsets; include each element or not
			else {
				numseq = (numseq + modularExponent(2, j - i, mod)) % mod;
			}
		}

		return numseq;
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
	int target;

	// test case 1
	nums = { 3, 5, 6, 7 };
	target = 9;
	std::cout << "numSubseq(" << nums << "," << target << ") = " 
		<< sol.numSubseq(nums, target) << std::endl;

	// test case 2
	nums = { 3, 3, 6, 8 };
	target = 10;
	std::cout << "numSubseq(" << nums << "," << target << ") = "
		<< sol.numSubseq(nums, target) << std::endl;

	// test case 3
	nums = { 2, 3, 3, 4, 6, 7 };
	target = 12;
	std::cout << "numSubseq(" << nums << "," << target << ") = "
		<< sol.numSubseq(nums, target) << std::endl;

	return 0;
}