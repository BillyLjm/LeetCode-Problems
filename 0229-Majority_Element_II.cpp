/*******************************************************************************
 * 0229-Majority_Element_II.cpp
 * Billy.Ljm
 * 05 October 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/majority-element-ii/
 *
 * Given an integer array of size n, find all elements that appear more than
 * floor(n/3) times.
 *
 * ===========
 * My Approach
 * ===========
 * We will use the Boyer-Moore majority voting algorithm, modified for 1/3
 * majority. We will remember 2 candidate integers and keep a count for each.
 * As we iterate through the array, if the candidate integer is seen then its 
 * count is incremented by 1, and if neither candidates are seen then both
 * count decrement by 1. This way, the count of any majority integer will be
 * non-negative; in the worse case there will be 2*n majority integers followed
 * by n of the other integers. Thus, if the count drops below zero, we can write
 * off the current candidate and choose a new one. However, if there are no
 * majority integers, this algorithm will still pick up two candidates that
 * simply occurred at the end of the array. Thus, we still have to validate the
 * candidates afterwards.
 *
 * This has a time complexity of O(n), and a space complexity of O(1), where n
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
	vector<int> majorityElement(vector<int>& nums) {
		// choose candidate integers
		int cand1 = 0, count1 = 0;
		int cand2 = 0, count2 = 0;
		for (int num : nums) {
			// count matches
			if (num == cand1) count1++;
			else if (num == cand2) count2++;
			// reselect candidate if needed, ensuring that they're distinct
			else if (count1 <= 0 and num != cand2) {
				cand1 = num;
				count1 = 1;
			}
			else if (count2 <= 0 and num != cand1) {
				cand2 = num;
				count2 = 1;
			}
			// decerement count if no matches or reslection
			else {
				count1--;
				count2--;
			}
		}

		// check candidates
		count1 = 0;
		count2 = 0;
		for (int num : nums) {
			if (num == cand1) count1++;
			else if (num == cand2) count2++;
		}

		// create output
		vector<int> out;
		if (count1 > nums.size() / 3) out.push_back(cand1);
		if (count2 > nums.size() / 3) out.push_back(cand2);
		return out;
	}
};

/**
 * Test cases
 */
int main(void) {
	Solution sol;
	vector<int> nums;

	// test case 1
	nums = { 3,2,3 };
	std::cout << "majorityElement(" << nums << ") = ";
	std::cout << sol.majorityElement(nums) << std::endl;

	// test case 2
	nums = { 1 };
	std::cout << "majorityElement(" << nums << ") = ";
	std::cout << sol.majorityElement(nums) << std::endl;

	// test case 3
	nums = { 1,2 };
	std::cout << "majorityElement(" << nums << ") = ";
	std::cout << sol.majorityElement(nums) << std::endl;

	return 0;
}