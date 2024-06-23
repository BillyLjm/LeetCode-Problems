/*******************************************************************************
 * 1438_Longest-Continuous-Subarray-With-Absolute-Diff-Less-Than-or-Equal-to-Limit.cpp
 * Billy.Ljm
 * 23 June 2024
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/longest-continuous-subarray-with-absolute-diff-less-than-or-equal-to-limit/
 *
 * Given an array of integers nums and an integer limit, return the size of the
 * longest non-empty subarray such that the absolute difference between any two
 * elements of this subarray is less than or equal to limit.
 *
 * ===========
 * My Approach
 * ===========
 * We can use a sliding window to determine what subarrays to check. If the
 * subarray is within the limit, then we can try extending it with another
 * element to the right. If not, we have to reduce the subarray by removing
 * the left-most element. Additionally, to find the min/max of the subarrays
 * efficiently, we will use double ended queues. If an element is added, then
 * we will pop elements from the back of the min/max deque that are smaller/
 * larger than the new element, since they will never become the min/max. If
 * an min/max is removed, we will pop it from the front of the deque and the
 * next min/max will automatically become the front of the deque.
 *
 * This has a time complexity of O(n) and space complexity of O(n), where n is
 * the length of the array of integers given.
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
	int longestSubarray(vector<int>& nums, int limit) {
		int maxsize = 1; // max size of compliant subarray
		int start = 0, end = 0; // index of sliding window
		deque<int> maxx = { nums[0] }, minn = { nums[0] }; // to find min/max

		while (end < nums.size() - 1) {
			// extend subarray by 1 element
			end++;
			while (!maxx.empty() and nums[end] > maxx.back()) {
				maxx.pop_back();
			}
			while (!minn.empty() and nums[end] < minn.back()) {
				minn.pop_back();
			}
			maxx.push_back(nums[end]);
			minn.push_back(nums[end]);
			// reduce subarray if limit exceeded
			while (start < nums.size() and maxx.front() - minn.front() > limit) {
				if (nums[start] == maxx.front()) {
					maxx.pop_front();
				}
				if (nums[start] == minn.front()) {
					minn.pop_front();
				}
				start++;
			}
			cout << start << ", " << end << endl;
			// remember max subarray size
			maxsize = max(maxsize, end - start + 1);
		}

		return maxsize;
	}
};

/**
 * Test cases
 */
int main(void) {
	Solution sol;
	int limit;
	vector<int> nums;

	// test case 1
	limit = 4;
	nums = { 8,2,4,7 };
	std::cout << "longestSubarray(" << nums << ", " << limit << ") = ";
	std::cout << sol.longestSubarray(nums, limit) << std::endl;

	// test case 2
	limit = 5;
	nums = { 10,1,2,4,7,2 };
	std::cout << "longestSubarray(" << nums << ", " << limit << ") = ";
	std::cout << sol.longestSubarray(nums, limit) << std::endl;

	// test case 3
	limit = 0;
	nums = { 4,2,2,2,4,4,2,2 };
	std::cout << "longestSubarray(" << nums << ", " << limit << ") = ";
	std::cout << sol.longestSubarray(nums, limit) << std::endl;

	return 0;
}