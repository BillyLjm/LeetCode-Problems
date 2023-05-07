/*******************************************************************************
 * 1964-Find_the_Longest_Valid_Obstacle_Course_at_each_Position.cpp
 * Billy.Ljm
 * 07 May 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/find-the-longest-valid-obstacle-course-at-each-position/
 *
 * You want to build some obstacle courses. You are given a 0-indexed integer
 * array obstacles of length n, where obstacles[i] describes the height of the
 * ith obstacle.
 *
 * For every index i between 0 and n - 1 (inclusive), find the length of the
 * longest obstacle course in obstacles such that:
 *
 * - You choose any number of obstacles between 0 and i inclusive.
 * - You must include the ith obstacle in the course.
 * - You must put the chosen obstacles in the same order as they appear in
 *   obstacles.
 * - Every obstacle (except the first) is taller than or the same height as the
 *   obstacle immediately before it.
 *
 * Return an array ans of length n, where ans[i] is the length of the longest
 * obstacle course for index i as described above.
 *
 * ===========
 * My Approach
 * ===========
 * We will use dynamic programming, where for each index, we find the earlier
 * index with the maximum obstacle course length but with a shorter height.
 * Then, we just have to add one to this found index.

 * To find this index efficiently, we can create a dictionary of {height:length}
 * for all earlier indices, and binary search any new indices within it. This
 * is conveniently already implemented in std::map::upper_bound.
 *
 * This has a time complexity of O(n * log(n)) and space complexity of O(n),
 * where n is the length of the array of obstacle heights.
 ******************************************************************************/

#include <iostream>
#include <vector>
#include <map>

/**
 * Solution
 */
class Solution {
public:
	/**
	 * Finds the longest obstacle course that be constructed with each element
	 * and any in-order combination of preceding elements. An obstacle course
	 * must have obstacles whose height are non-decreasing.
	 *
	 * @param obstacles height of the obstacles
	 *
	 * @return a vector where the i-th element is the maximum length of an
	 *         obstacle course which includes obstacle[i]
	 */
	std::vector<int> longestObstacleCourseAtEachPosition(
		std::vector<int>& obstacles) {

		std::vector<int> ans; // max length at each index
		std::map<int, int> height2length; // {height : max length} so far

		for (int i = 0; i < obstacles.size(); i++) {
			// find next smallest/equal height plus 1
			auto it = height2length.upper_bound(obstacles[i]);

			// if no smaller height found, then max length is 1
			if (it == height2length.begin()) {
				ans.push_back(1);
			}
			// else, add 1
			else {
				it--;
				ans.push_back(it->second + 1);
				it++;
			}

			// update larger heights w/ smaller lengths
			while (it != height2length.end() && it->second <= ans[i]) {
				it = height2length.erase(it); 
			}
			// update current height
			height2length[obstacles[i]] = ans[i];
		}

		return ans;
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
	std::vector<int> obstacles;

	// test case 1
	obstacles = { 1, 2, 3, 2 };
	std::cout << "longestObstacleCourseAtEachPosition(" << obstacles << ") = "
		<< sol.longestObstacleCourseAtEachPosition(obstacles) << std::endl;

	// test case 2
	obstacles = { 2, 2, 1 };
	std::cout << "longestObstacleCourseAtEachPosition(" << obstacles << ") = "
		<< sol.longestObstacleCourseAtEachPosition(obstacles) << std::endl;

	// test case 3
	obstacles = { 3, 1, 5, 6, 4, 2 };
	std::cout << "longestObstacleCourseAtEachPosition(" << obstacles << ") = "
		<< sol.longestObstacleCourseAtEachPosition(obstacles) << std::endl;

	return 0;
}