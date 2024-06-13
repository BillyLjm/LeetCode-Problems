/*******************************************************************************
 * 2037-Minimum_Number_of_Moves_to_Seat_Everyone.cpp
 * Billy.Ljm
 * 13 June 2024
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/minimum-number-of-moves-to-seat-everyone/
 *
 * There are n seats and n students in a room. You are given an array seats of
 * length n, where seats[i] is the position of the ith seat. You are also given
 * the array students of length n, where students[j] is the position of the jth
 * student.
 *
 * You may perform the following move any number of times:
 * - Increase or decrease the position of the ith student by 1 (i.e., moving the
 *   ith student from position x to x + 1 or x - 1)
 *
 * Return the minimum number of moves required to move each student to a seat
 * such that no two students are in the same seat.
 *
 * Note that there may be multiple seats or students in the same position at the
 * beginning
 *
 * ===========
 * My Approach
 * ===========
 * We can just allocate the leftmost unseated student to the leftmost unoccupied
 * seat. This is optimal since its a 1D plane and the resulting movements are
 * all one-directional, with no students crossing paths in opposite directions.
 * Thus, we can just sort the two arrays to find the student-seat allocation and
 * subtract the two arrays to find the distance each student has to move.
 *
 * This has a time complexity of O(n log n) and space complexity of O(1), where
 * n is the size of the array.
 *
 * We can also get the time complexity down to O(n) by using counting sort
 * instead of the built-in cpp sorting algorithm. But this uses more practical
 * space since we have to store the additional count of 100 values.
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
	int minMovesToSeat(vector<int>& seats, vector<int>& students) {
		int out = 0;

		// allocate students to seats
		sort(seats.begin(), seats.end());
		sort(students.begin(), students.end());

		// count number of moves
		for (int i = 0; i < seats.size(); i++) {
			out += abs(students[i] - seats[i]);
		}
		return out;
	}
};

/**
 * Test cases
 */
int main(void) {
	Solution sol;
	vector<int> seats, students;

	// test case 1
	seats = { 3,1,5 };
	students = { 2,7,4 };
	std::cout << "minMovesToSeat(" << seats << ", " << students << ") = ";
	std::cout << sol.minMovesToSeat(seats, students) << std::endl;

	// test case 2
	seats = { 4,1,5,9 };
	students = { 1,3,2,6 };
	std::cout << "minMovesToSeat(" << seats << ", " << students << ") = ";
	std::cout << sol.minMovesToSeat(seats, students) << std::endl;

	// test case 3
	seats = { 2,2,6,6 };
	students = { 1,3,2,6 };
	std::cout << "minMovesToSeat(" << seats << ", " << students << ") = ";
	std::cout << sol.minMovesToSeat(seats, students) << std::endl;

	return 0;
}