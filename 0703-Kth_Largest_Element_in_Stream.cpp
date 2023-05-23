/*******************************************************************************
 * 0703-Kth_Largest_Element_in_Stream.cpp
 * Billy.Ljm
 * 23 May 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/kth-largest-element-in-a-stream/
 *
 * Design a class to find the kth largest element in a stream. Note that it is
 * the kth largest element in the sorted order, not the kth distinct element.
 *
 * Implement KthLargest class:
 * - KthLargest(int k, int[] nums) Initializes the object with the integer k and
 *   the stream of integers nums.
 * - int add(int val) Appends the integer val to the stream and returns the
 *   element representing the kth largest element in the stream.
 *
 * ===========
 * My Approach
 * ===========
 * We'll use the standard priority queue to remember the k largest elements.
 * To optimise for space, we'll constantly pop from the queue such that there
 * are only k elements in it.	
 *
 * This has a time complexity of O(n log k) and space complexity of O(k), where
 * n is the size of the stream, and k the number of largest elements to return.
 ******************************************************************************/

#include <iostream>
#include <vector>
#include <queue>

/**
 * Remembers the k-th largest element from a stream
 */
class KthLargest {
private:
	std::priority_queue<int, std::vector<int>, std::greater<int>> pq;
	int k;

public:
	/**
	 * Class constructor
	 *
	 * @param k number of largest element to return
	 * @param nums vector of initial values of the stream
	 */
	KthLargest(int k, std::vector<int>& nums) {
		// remember size
		this->k = k;
		// insert values
		for (int num : nums) {
			pq.push(num);
			if (pq.size() > k) pq.pop();
		}
	}

	/**
	 * Adds a value from the stream
	 *
	 * @param val value to add
	 *
	 * @return k-th largest element from the stream so far
	 */
	int add(int val) {
		// insert value
		pq.push(val);
		if (pq.size() > this->k) pq.pop();
		// return k-th largest value
		return pq.top();
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
	// test case 1
	int k = 3;
	std::vector<int> nums = { 4, 5, 8, 2 };
	KthLargest* kthLargest = new KthLargest(k, nums);
	std::cout << "kthLargest(" << k << "," << nums << ")" << std::endl;
	std::cout << kthLargest->add(3) << std::endl;   // return 4
	std::cout << kthLargest->add(5) << std::endl;   // return 5
	std::cout << kthLargest->add(10) << std::endl;  // return 5
	std::cout << kthLargest->add(9) << std::endl;   // return 8
	std::cout << kthLargest->add(4) << std::endl;   // return 8
	delete kthLargest;

	return 0;
}