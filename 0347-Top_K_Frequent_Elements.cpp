/*******************************************************************************
 * 0347-Top_K_Frequent_Elements.cpp
 * Billy.Ljm
 * 22 May 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/top-k-frequent-elements/
 *
 * Given an integer array nums and an integer k, return the k most frequent
 * elements. You may return the answer in any order.
 *
 * ===========
 * My Approach
 * ===========
 * We'll count the frequency of each integer in a map of {integer : occurrences},
 * and use the quickselect algorithm to find the k smallest ones.
 *
 * This has a time complexity of O(n) and space complexity of O(n), where n is
 * the number of integers.
 ******************************************************************************/

#include <iostream>
#include <vector>
#include <map>

/**
 * Solution
 */
class Solution {
private:
	/**
	 * One iteration of quickselect. Select last element as pivot value.
	 *
	 * @param arr vector of {key, value} to sort by value
	 * @param start starting index to sort from
	 * @param end ending index to sort from
	 *
	 * @return sorted index of pivot value
	 */
	int quickSelect(std::vector<std::pair<int, int>>& arr, int start, int end) {
		int idx = start; // index to insert into

		for (int i = start; i < end; i++) {
			// note strictly greater than, otherwise quickselect can infinitely
			// loop when there are multiple kth frequent values. (e.g. {a, b}
			// with equal frequency will put pivot into 1 and never 0)
			if (arr[i].second > arr[end].second) { 
				std::swap(arr[idx], arr[i]);
				idx++;
			}
		}
		std::swap(arr[idx], arr[end]);

		return idx;
	}

public:
	/**
	 * Finds the k most frequent integers in a vector
	 *
	 * @param nums vector to search in
	 * @param k number of most frequent integers to return
	 *
	 * @return vector of the k most frequent integers
	 */
	std::vector<int> topKFrequent(std::vector<int>& nums, int k) {
		// count number of occurences
		std::map<int, int> freq;
		for (int num : nums) {
			if (freq.find(num) == freq.end()) {
				freq[num] = 1;
			}
			else {
				freq[num]++;
			}
		}

		// convert to vector for sorting
		std::vector<std::pair<int, int>> vec;
		for (auto it : freq) {
			vec.push_back({ it.first, it.second });
		}

		// quickselect algorithm
		if (vec.size() > k) {
			int start = 0;
			int end = vec.size() - 1;
			int pivot = quickSelect(vec, start, end);
			while (pivot != k) {
				if (pivot > k)  end = pivot - 1;
				else start = pivot + 1;
				pivot = quickSelect(vec, start, end);
			}
		}

		// convert to ouput
		std::vector<int> out;
		for (int i = 0; i < k; i++) {
			out.push_back(vec[i].first);
		}
		return out;
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
	int k;

	// test case 1
	nums = { 1, 1, 1, 2, 2, 3 };
	k = 2;
	std::cout << "topKFrequent(" << nums << "," << k << ") = " <<
		sol.topKFrequent(nums, k) << std::endl;

	// test case 2
	nums = { 1 };
	k = 1;
	std::cout << "topKFrequent(" << nums << "," << k << ") = " <<
		sol.topKFrequent(nums, k) << std::endl;

	return 0;
}