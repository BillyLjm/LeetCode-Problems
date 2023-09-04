/*******************************************************************************
 * 1326-Minimum_Number_of_Taps_to_Open_to_Water_a_Garden.cpp
 * Billy.Ljm
 * 31 August 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/minimum-number-of-taps-to-open-to-water-a-garden/
 *
 * There is a one-dimensional garden on the x-axis. The garden starts at the
 * point 0 and ends at the point n. (i.e., the length of the garden is n).
 *
 * There are n + 1 taps located at points [0, 1, ..., n] in the garden.
 *
 * Given an integer n and an integer array ranges of length n + 1 where
 * ranges[i] (0-indexed) means the i-th tap can water the area
 * [i - ranges[i], i + ranges[i]] if it was open.
 *
 * Return the minimum number of taps that should be open to water the whole
 * garden, If the garden cannot be watered return -1.
 *
 * ===========
 * My Approach
 * ===========
 * Instead of considering the taps to be at the midpoint of its range, we can
 * just consider the minimum and maximum of their ranges. And at each garden
 * plot we will only want to choose the tap which can reach to the highest
 * watered plot[i]. Thus, at any current plot, we will choose this highest
 * plot[i], and subsequently iterate from the current plot to plot[i] to find
 * the next largest jump.
 *
 * This has a time complexity of O(n), and a space complexity of O(n), where n
 * is the length of garden.
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
	int minTaps(int n, vector<int>& ranges) {
		// find taps whose range starts at i but stretches to the highest plot
		int start, end; // start & end of current tap ranges
		vector<int> maxrange(n + 1, 0);
		for (int i = 0; i < ranges.size(); i++) {
			start = max(i - ranges[i], 0);
			end = min(i + ranges[i], n);
			maxrange[start] = max(maxrange[start], end);
		}

		// iterate through garden plots, trying to jump to highest plot each time
		int ntaps = 0; // number of taps to turn on
		start = 0; // reuse var: start of current jump
		end = maxrange[0]; // reuse var: end of current jump
		int tmp; // maximum of maxrange[start:end]
		while (start < end) {
			// find next biggest jump
			for (int i = start; i <= end; i++) {
				tmp = max(tmp, maxrange[i]);
			}
			// take next biggest jump
			ntaps++;
			start = end;
			end = tmp;
			tmp = 0;
		}

		// check if all plots watered/jumped over
		if (start >= n) return ntaps;
		else return -1;
	}
};

/**
 * Test cases
 */
int main(void) {
	Solution sol;
	int n;
	vector<int> ranges;

	// test case 1
	n = 5;
	ranges = { 3,4,1,1,0,0 };
	std::cout << "minTaps(" << n << "," << ranges << ") = ";
	std::cout << sol.minTaps(n, ranges) << std::endl;

	// test case 2
	n = 3;
	ranges = { 0,0,0,0 };
	std::cout << "minTaps(" << n << "," << ranges << ") = ";
	std::cout << sol.minTaps(n, ranges) << std::endl;

	return 0;
}