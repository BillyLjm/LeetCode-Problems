/*******************************************************************************
 * 1052-Grumpy_Bookstore_Owner.cpp
 * Billy.Ljm
 * 21 June 2024
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/grumpy-bookstore-owner/
 *
 * There is a bookstore owner that has a store open for n minutes. Every minute,
 * some number of customers enter the store. You are given an integer array
 * customers of length n where customers[i] is the number of the customer that
 * enters the store at the start of the ith minute and all those customers leave
 * after the end of that minute.
 *
 * On some minutes, the bookstore owner is grumpy. You are given a binary array
 * grumpy where grumpy[i] is 1 if the bookstore owner is grumpy during the ith
 * minute, and is 0 otherwise.
 *
 * When the bookstore owner is grumpy, the customers of that minute are not
 * satisfied, otherwise, they are satisfied.
 *
 * The bookstore owner knows a secret technique to keep themselves not grumpy
 * for `minutes` consecutive minutes, but can only use it once.
 *
 * Return the maximum number of customers that can be satisfied throughout the
 * day.
 *
 * ===========
 * My Approach
 * ===========
 * We can just use a sliding window to consider when to use the technique.
 *
 * This has a time complexity of O(n) and space complexity of O(1), where n is
 * the length of the input vectors `customers` and `grumpy`
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
public:
	int maxSatisfied(vector<int>& customers, vector<int>& grumpy, int minutes) {
		int nsatisfied = 0; // number of customers satisfied by default
		int slide = 0; // number of extra satisfied customers in sliding window
		int maxslide = 0;
		int tmp;

		for (int i = 0; i < customers.size(); i++) {
			// count number satisfied by default
			if (grumpy[i] == 0) {
				nsatisfied += customers[i];
			}
			// apply technique to sliding window
			slide = slide + customers[i] * grumpy[i];
			if (i >= minutes) {
				slide = slide - customers[i - minutes] * grumpy[i - minutes];
			}
			maxslide = max(slide, maxslide);
		}

		return nsatisfied + maxslide;
	}
};

/**
 * Test cases
 */
int main(void) {
	Solution sol;
	int minutes;
	vector<int> customers, grumpy;

	// test case 1
	minutes = 3;
	customers = { 1,0,1,2,1,1,7,5 };
	grumpy =    { 0,1,0,1,0,1,0,1 };
	std::cout << "maxSatisfied(" << customers << ", " << grumpy << ", " <<
		minutes << ") = ";
	std::cout << sol.maxSatisfied(customers, grumpy, minutes) << std::endl;

	// test case 2
	minutes = 1;
	customers = { 1 };
	grumpy = { 0 };
	std::cout << "maxSatisfied(" << customers << ", " << grumpy << ", " <<
		minutes << ") = ";
	std::cout << sol.maxSatisfied(customers, grumpy, minutes) << std::endl;

	return 0;
}