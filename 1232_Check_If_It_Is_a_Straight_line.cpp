/*******************************************************************************
 * 1232_Check_If_It_Is_a_Straight_line.cpp
 * Billy.Ljm
 * 05 June 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/check-if-it-is-a-straight-line/
 *
 * You are given an array coordinates, coordinates[i] = [x, y], where [x, y]
 * represents the coordinate of a point. Check if these points make a straight
 * line in the XY plane.
 *
 * ===========
 * My Approach
 * ===========
 * We calculate the slope `(y2-y1)/(x2-x1)` b/w a common point `coordinates[0]`
 * and every other point. If the lines formed b/w pairs share the same slope and
 * same point, the lines will be collinear. 
 *
 * This has a time complexity of O(n) and space complexity of O(1), where n is
 * the nuber of points.
 ******************************************************************************/

#include <iostream>
#include <vector>

/**
 * Solution
 */
class Solution {
private:
	/**
	 * Gets the slope b/w two points
	 *
	 * @param pt1 xy-coordinates of 1st point
	 * @param pt2 xy-coordinates of 2nd point
	 *
	 * @return normalised vector b/w pt1 and pt2.
	 */
	float getSlope(std::vector<int> pt1, std::vector<int> pt2) {
		if (pt2[0] == pt1[0]) return FLT_MAX;
		else return 1.0 * (pt2[1] - pt1[1]) / (pt2[0] - pt1[0]);
	}

public:
	/**
	 * Checks if a list of xy coordinates lie on a straight line
	 *
	 * @param coordinates list of [x,y] coordinates
	 *
	 * @return true if all coorindates lie on the same line, false otherwise
	 */
	bool checkStraightLine(std::vector<std::vector<int>>& coordinates) {
		// get slope b/w 0 and 1
		float dir = getSlope(coordinates[0], coordinates[1]);
		// check slope b/w 0 and i
		for (int i = 2; i < coordinates.size(); i++) {
			if (getSlope(coordinates[0], coordinates[i]) != dir) return false;
		}
		// all direction same
		return true;
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
	std::vector<std::vector<int>> coordinates;

	// test case 1
	coordinates = { {1,2}, {2,3}, {3,4}, {4,5}, {5,6}, {6,7} };
	std::cout << "checkStraightLine(" << coordinates << ") = ";
	std::cout << std::boolalpha << sol.checkStraightLine(coordinates) << std::endl;

	// test case 2
	coordinates = { {1,1}, {2,2}, {3,4}, {4,5}, {5,6}, {7,7} };
	std::cout << "checkStraightLine(" << coordinates << ") = ";
	std::cout << std::boolalpha << sol.checkStraightLine(coordinates) << std::endl;

	return 0;
}