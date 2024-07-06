/*******************************************************************************
 * 2582-Pass_the_Pillow.cpp
 * Billy.Ljm
 * 06 July 2024
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/pass-the-pillow/
 *
 * There are n people standing in a line labeled from 1 to n. The first person
 * in the line is holding a pillow initially. Every second, the person holding
 * the pillow passes it to the next person standing in the line. Once the pillow
 * reaches the end of the line, the direction changes, and people continue
 * passing the pillow in the opposite direction.
 *
 * For example, once the pillow reaches the nth person they pass it to the
 * (n - 1)th person, then to the (n - 2)th person and so on.
 *
 * Given the two positive integers n and time, return the index of the person
 * holding the pillow after time seconds.
 *
 * ===========
 * My Approach
 * ===========
 * We can just calculate the solution directly. The situation repeats after 2n-2
 * time steps, so we take the time mod (2n-2) and find out who holds the pillow.
 *
 * This has a time complexity of O(1) and space complexity of O(1).
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
	int passThePillow(int n, int time) {
		time = time % (2*n - 2);
		if (time < n) return time + 1;
		else return 2*n - 1 - time;
	}
};

/**
 * Test cases
 */
int main(void) {
	Solution sol;
	int n, time;

	// test case 1
	n = 4;
	time = 5;
	std::cout << "passThePillow(" << n << ", " << time << ") = ";
	std::cout << sol.passThePillow(n, time) << std::endl;

	// test case 2
	n = 3;
	time = 2;
	std::cout << "passThePillow(" << n << ", " << time << ") = ";
	std::cout << sol.passThePillow(n, time) << std::endl;

	return 0;
}