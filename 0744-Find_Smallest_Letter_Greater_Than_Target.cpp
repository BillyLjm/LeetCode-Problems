/*******************************************************************************
 * 0744-Find_Smallest_Letter_Greater_Than_Target.cpp
 * Billy.Ljm
 * 09 June 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/find-smallest-letter-greater-than-target/
 *
 * You are given an array of characters letters that is sorted in non-decreasing
 * order, and a character target. There are at least two different characters in 
 * letters.
 *
 * Return the smallest character in letters that is lexicographically greater
 * than target. If such a character does not exist, return the first character
 * in letters.
 *
 * ===========
 * My Approach
 * ===========
 * We'll use binary search to identify the desired character.
 *
 * This has a time complexity of O(log n) and space complexity of O(1), where n
 * is the size of the array.
 ******************************************************************************/

#include <iostream>
#include <vector>

/**
 * Solution
 */
class Solution {
public:
	/**
	 * Finds the next letter in the array that is greater than the target
	 *
	 * @param letters array to search in, sorted in increasing order
	 * @param target threshold to find next greater letter than
	 *
	 * @return next greater letter than target
	 */
	char nextGreatestLetter(std::vector<char>& letters, char target) {
		// edge case
		if (letters[letters.size() - 1] <= target) return letters[0];

		// binary search index
		int minn = 0;
		int maxx = letters.size() - 1;
		int mid;

		// binary search
		while (maxx - minn != 1) {
			mid = (maxx + minn) / 2;
			if (letters[mid] > target) maxx = mid;
			else minn = mid;
		}

		// last check
		if (letters[minn] > target) return letters[minn];
		else return letters[maxx];
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
	std::vector<char> letters;
	char target;

	// test case 1
	letters = { 'c', 'f', 'j' };
	target = 'a';
	std::cout << "nextGreatestLetter(" << letters << "," << target << ") = ";
	std::cout << sol.nextGreatestLetter(letters, target) << std::endl;

	// test case 2
	letters = { 'c', 'f', 'j' };
	target = 'c';
	std::cout << "nextGreatestLetter(" << letters << "," << target << ") = ";
	std::cout << sol.nextGreatestLetter(letters, target) << std::endl;

	// test case 3
	letters = { 'x', 'x', 'y', 'y' };
	target = 'z';
	std::cout << "nextGreatestLetter(" << letters << "," << target << ") = ";
	std::cout << sol.nextGreatestLetter(letters, target) << std::endl;

	return 0;
}