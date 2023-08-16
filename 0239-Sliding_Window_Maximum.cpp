/*******************************************************************************
 * 0239-Sliding_Window_Maximum.cpp
 * Billy.Ljm
 * 16 August 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/sliding-window-maximum/
 *
 * You are given an array of integers nums, there is a sliding window of size k
 * which is moving from the very left of the array to the very right. You can
 * only see the k numbers in the window. Each time the sliding window moves
 * right by one position.
 *
 * Return the max sliding window.
 *
 * ===========
 * My Approach
 * ===========
 * As we slide the window, we can forget all elements that are smaller than the
 * newly-inserted element, since they will never become the maximum. Doing this
 * at every step results in an array which is always sorted in ascending order,
 * with the new element at the back, and the maximum of the window at the front.
 *
 * This array will be implemented with a double-ended array, since we have to
 * access and pop the front and back elements frequently.
 *
 * This has a time complexity of O(n), and a space complexity of  O(k), where
 * n is the length of the array and k is the length of the sliding window.
 ******************************************************************************/

#include <iostream>
#include <vector>
#include <deque>

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
	vector<int> maxSlidingWindow(vector<int>& nums, int k) {
		deque<int> window; // relevant elements in window
		vector<int> out; // output

		// base case
		if (k < 1) return vector<int>(0);
		else if (k == 1) return nums;

		// remaining cases
		for (int i = 0; i < nums.size(); i++) {
			// add new element, forgetting all other smaller values
			while (window.size() != 0 && window.back() < nums[i]) {
				window.pop_back();
			}
			window.push_back(nums[i]);
			// pop last element (if still in relevant elements)
			if (i - k >= 0 && window.front() == nums[i - k]) {
				window.pop_front();
			}
			// append maximum element
			if (i >= k - 1) {
				out.push_back(window.front());
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
	vector<int> nums;
	int k;

	// test case 1
	nums = { 1,3,-1,-3,5,3,6,7 };
	k = 3;
	std::cout << "maxSlidingWindow(" << nums << "," << k << ") = ";
	std::cout << sol.maxSlidingWindow(nums, k) << std::endl;

	// test case 2
	nums = { 1 };
	k = 1;
	std::cout << "maxSlidingWindow(" << nums << "," << k << ") = ";
	std::cout << sol.maxSlidingWindow(nums, k) << std::endl;

	return 0;
}