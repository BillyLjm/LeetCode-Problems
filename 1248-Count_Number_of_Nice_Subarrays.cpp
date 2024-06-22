/*******************************************************************************
 * 1248-Count_Number_of_Nice_Subarrays.cpp
 * Billy.Ljm
 * 22 June 2024
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/count-number-of-nice-subarrays/
 *
 * Given an array of integers nums and an integer k. A continuous subarray is
 * called nice if there are k odd numbers on it.
 *
 * Return the number of nice sub-arrays.
 *
 * ===========
 * My Approach
 * ===========
 * We can find sub-arrays starting and ending with odd numbers, and that contain
 * k odd numbers. If there are any even numbers before/after these subarrays, we
 * can also prepend/append them to the array while maintaining their niceness.
 * Thus, we can use a sliding window to find the arrays described above, and
 * count the number of nice arrays formed by prepending/appending adjacent even
 * numbers.
 *
 * This has a time complexity of O(n) and space complexity of O(1), where n is
 * the length of the array of integers given.
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
private:
	/* advance start of subarray to next odd integer */
	pair<int, int> crawl_start(vector<int>& nums, pair<int, int> pos) {
		int nstart = 0;
		int start = get<0>(pos) + 1;
		while (start < nums.size() and nums[start] % 2 == 0) {
			start++;
			nstart++;
		}
		if (start >= nums.size() or nums[start] % 2 == 0) {
			return pair<int, int>(nums.size(), -1);
		}
		else {
			return pair<int, int>(start, nstart);
		}
	}

	/* advance end of subarray to next odd integer */
	pair<int, int> crawl_end(vector<int>& nums, pair<int, int> pos) {
		int nend = 0;
		int end = get<0>(pos) + 1;
		while (end < nums.size() and nums[end] % 2 == 0) {
			end++;
		}
		if (end >= nums.size() or nums[end] % 2 == 0) {
			return pair<int, int>(nums.size(), -1);
		}
		while (end + nend + 1 < nums.size() and nums[end + nend + 1] % 2 == 0) {
			nend++;
		}
		return pair<int, int>(end, nend);
	}

public:
	int numberOfSubarrays(vector<int>& nums, int k) {
		int nnice = 0; // number of nice arrays
		pair <int, int> start, end; // (index, num even numbers) of start and end of subarray

		// find first subarray with k odd numbers
		start = { -1,0 };
		start = crawl_start(nums, start);
		end = { get<0>(start), 0 };
		for (int i = 1; i < k; i++) {
			end = crawl_end(nums, end);
		}
		nnice += (get<1>(start) + 1) * (get<1>(end) + 1);

		// slide subarray until end is reached
		while (get<0>(end) < nums.size()) {
			start = crawl_start(nums, start);
			end = crawl_end(nums, end);
			nnice += (get<1>(start) + 1) * (get<1>(end) + 1);
		}

		return nnice;
	}
};

/**
 * Test cases
 */
int main(void) {
	Solution sol;
	int k;
	vector<int> nums;

	// test case 1
	k = 3;
	nums = { 1,1,2,1,1 };
	std::cout << "numberOfSubarrays(" << nums << ", " << k << ") = ";
	std::cout << sol.numberOfSubarrays(nums, k) << std::endl;

	// test case 2
	k = 1;
	//nums = { 2,4,6 };
	nums = { 2,3,5 };
	std::cout << "numberOfSubarrays(" << nums << ", " << k << ") = ";
	std::cout << sol.numberOfSubarrays(nums, k) << std::endl;

	// test case 3
	k = 2;
	nums = { 2,2,2,1,2,2,1,2,2,2 };
	std::cout << "numberOfSubarrays(" << nums << ", " << k << ") = ";
	std::cout << sol.numberOfSubarrays(nums, k) << std::endl;

	return 0;
}