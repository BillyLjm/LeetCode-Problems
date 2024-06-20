/*******************************************************************************
 * 1552-Magnetic_Force_Between_Two_Balls.cpp
 * Billy.Ljm
 * 20 June 2024
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/magnetic-force-between-two-balls/
 *
 * In the universe Earth C-137, Rick discovered a special form of magnetic force
 * between two balls if they are put in his new invented basket. Rick has n
 * empty baskets, the ith basket is at position[i], Morty has m balls and needs
 * to distribute the balls into the baskets such that the minimum magnetic force
 * between any two balls is maximum.
 *
 * Rick stated that magnetic force between two different balls at positions x
 * and y is |x - y|.
 *
 * Given the integer array position and the integer m. Return the required force.
 *
 * ===========
 * My Approach
 * ===========
 * To rephrase the problem, we just want to place the balls as far apart on the
 * 1D line as the baskets would allow, and return the minimum separation. To do
 * this, we can use binary search to test each minimum separation and figure out
 * its maximum.
 *
 * This has a time complexity of O(n log m) and space complexity of O(1), where
 * n is the length of the argument `position` and m is the argument `m`
 ******************************************************************************/

#include <iostream>
#include <vector>
#include <algorithm>

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
	int maxDistance(vector<int>& position, int m) {
		int min, max, mid; // for binary search
		int nballs, prev_pos; // to try filling balls

		// init variables
		sort(position.begin(), position.end());
		min = 1;
		max = position.back() / (m - 1);

		// binary search
		while (max > min) {
			mid = (min + max + 1) / 2;
			// calculate if all balls are fillable
			nballs = 1;
			prev_pos = position.front();
			for (int pos : position) {
				if (pos >= prev_pos + mid) {
					nballs++;
					prev_pos = pos;
				}
				if (nballs >= m) break;
			}
			// update binary search
			if (nballs >= m) {
				min = mid;
			}
			else {
				max = mid - 1;
			}
		}

		return max;
	}
};

/**
 * Test cases
 */
int main(void) {
	Solution sol;
	int m;
	vector<int> position;

	// test case 1
	m = 3;
	position = { 1,2,3,4,7 };
	std::cout << "maxDistance(" << position << ", " << m << ") = ";
	std::cout << sol.maxDistance(position, m) << std::endl;

	// test case 2
	m = 2;
	position = { 5,4,3,2,1,1000000000 };
	std::cout << "maxDistance(" << position << ", " << m << ") = ";
	std::cout << sol.maxDistance(position, m) << std::endl;

	return 0;
}