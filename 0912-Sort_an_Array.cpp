/*******************************************************************************
 * 0912-Sort_an_Array.cpp
 * Billy.Ljm
 * 01 Mar 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/sort-an-array/description/
 * Given an array of integers nums, sort the array in ascending order and return
 * it.You must solve the problem without using any built-in functions in
 * O(nlog(n)) time complexity and with the smallest space complexity possible.
 *
 * ===========
 * My Approach
 * ===========
 * The problem is asking for Heapsort. It has a time complexity of O(nlog(n)),
 * albeit it is typically slow in practice, and the space complexity is O(1)
 * since it is sort-in-place. Thus, it satisfies the required scaling of time
 * complexity and minimises the space complexity as requested.
 ******************************************************************************/

#include <iostream>
#include <vector>

class Solution {
public:
	/**
	 * Heapsorts an array
	 *
	 * @param nums The array to be converted into a Max-Heap.
	 *
	 * @return the sorted array; the array is sorted in-place but also returned.
	 */
	std::vector<int> sortArray(std::vector<int>& nums) {
		// creates Max-Heap from (unordered) array
		int n = int(nums.size());
		buildHeap(nums, int(n));

		for (int i = n - 1; i >= 0; i--) {
			// swaps the largest root element with the end of the array
			std::swap(nums[0], nums[i]);
			// heapifies the remainder of the array
			// the left and right subtrees are individually max-heaped already
			heapify(nums, i, 0);
		}

		return nums;
	}

private:
	/**
	 * Helps create a Max-Heap from the given array.
	 *
	 * @param nums The array to be converted into a Max-Heap.
	 * @param n The size of the array.
	 * @param i The root of the subtree to heapify
	 */
	void heapify(std::vector<int>& nums, int n, int i) {
		int largest = i;
		int l = 2 * i + 1;
		int r = 2 * i + 2;

		if (l < n && nums[l] > nums[largest]) {
			largest = l;
		}

		if (r < n && nums[r] > nums[largest]) {
			largest = r;
		}

		if (largest != i) {
			std::swap(nums[i], nums[largest]);
			heapify(nums, n, largest);
		}
	}

	/**
	 * Creates a Max-Heap from the given array.
	 * Iterates through the binary tree from bottom to top, and heapifies
	 *
	 * @params nums The array to be converted into a Max-Heap.
	 * @params n The size of the array.
	 */
	void buildHeap(std::vector<int>& nums, int n) {
		for (int i = n / 2 - 1; i >= 0; i--) {
			heapify(nums, n, i);
		}
	}
};

/**
 * Test Cases
 */
int main() {
	Solution solution;

	// test case 1
	std::vector<int> nums = {5, 2, 3, 1};
	std::cout << "unsorted: ";
	for (int i = 0; i < nums.size(); i++) {
		std::cout << nums[i] << " ";
	}
	std::cout << "\nsorted: ";
	solution.sortArray(nums);
	for (int i = 0; i < nums.size(); i++) {
		std::cout << nums[i] << " ";
	}
	std::cout << std::endl;

	// test case 2
	nums = {5, 1, 1, 2, 0, 0};
	std::cout << "unsorted: ";
	for (int i = 0; i < nums.size(); i++) {
		std::cout << nums[i] << " ";
	}
	std::cout << "\nsorted: ";
	solution.sortArray(nums);
	for (int i = 0; i < nums.size(); i++) {
		std::cout << nums[i] << " ";
	}
	std::cout << std::endl;

	return 0;
}