/*******************************************************************************
 * 0779-Kth_Symbol_in_Grammar.cpp
 * Billy.Ljm
 * 25 October 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/k-th-symbol-in-grammar/
 *
 * We build a table of n rows (1-indexed). We start by writing 0 in the 1st row.
 * Now in every subsequent row, we look at the previous row and replace each
 * occurrence of 0 with 01, and each occurrence of 1 with 10.
 *
 * For example, for n = 3, the 1st row is 0, the 2nd row is 01, and the 3rd row
 * is 0110.
 *
 * Given two integer n and k, return the kth (1-indexed) symbol in the nth row
 * of a table of n rows.
 *
 * ===========
 * My Approach
 * ===========
 * We can think of the table as a binary tree; if the node is 0, then its left
 * children is 0 and right children is 1. Then, we just have to traverse the
 * one specific branch corresponding to the k-th element
 *
 * This has a time complexity of O(n), and space complexity of O(1), where n is
 * the number of row / layers of replacements.
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
	int kthGrammar(int n, int k) {
		bool curr = 0; // current node value
		int start = 0, end = pow(2, n - 1), mid; // range of index being expanded

		// expand binary tree
		while (end - start > 1) {
			mid = (start + end) / 2;
			cout << mid << endl;
			if (k > mid) {
				curr = !curr;
				start = mid;
			}
			else {
				curr = curr;
				end = mid;
			}
		}

		// find last node
		if (k - 1 == start) return curr;
		else return !curr;
	}
};

/**
 * Test cases
 */
int main(void) {
	Solution sol;
	int n, k;

	// test case 1
	n = 1;
	k = 1;
	std::cout << "kthGrammar(" << n << "," << k << ") = ";
	std::cout << sol.kthGrammar(n, k) << std::endl;

	// test case 2
	n = 2;
	k = 1;
	std::cout << "kthGrammar(" << n << "," << k << ") = ";
	std::cout << sol.kthGrammar(n, k) << std::endl;

	// test case 3
	n = 2;
	k = 2;
	std::cout << "kthGrammar(" << n << "," << k << ") = ";
	std::cout << sol.kthGrammar(n, k) << std::endl;

	return 0;
}