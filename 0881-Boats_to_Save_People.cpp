/*******************************************************************************
 * 0881-Boats_to_Save_People.cpp
 * Billy.Ljm
 * 03 Apr 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/boats-to-save-people/
 * You are given an array people where people[i] is the weight of the ith
 * person, and an infinite number of boats where each boat can carry a maximum
 * weight of limit. Each boat carries at most two people at the same time,
 * provided the sum of the weight of those people is at most limit.
 *
 * Return the minimum number of boats to carry every given person.
 *
 * ===========
 * My Approach
 * ===========
 * The optimal way is the greedy way: pair the heaviest person with the lightest
 * person if possible. Thus, we just have to sort the array, put the heaviest
 * person in the boat, and see if the lightest person can be squeezed in. This
 * is repeated until all people are in boats, and we have our answer
 *
 * It has a time complexity of O(n log n) due to sorting, where n is the number
 * of people. The space complexity will be O(1), since we'll sort in place and
 * mutate the input variable.
 ******************************************************************************/

#include <iostream>
#include <vector>
#include <algorithm>

class Solution {
public:
	/**
	 * Finds the minimum number of boats needed to save people, given each boat
	 * can carry at most 2 people and up to a specified weight limit
	 *
	 * @param people vector of people's weights
	 * @param limit weight limit of each boat
	 *
	 * @return minimum number of boats needed
	 */
	int numRescueBoats(std::vector<int>& people, int limit) {
		int numboats = 0;
		size_t mini = 0, maxi = people.size() - 1; // crawlers
		std::sort(people.begin(), people.end(),  std::greater<int>());

		while (mini <= maxi) {
			if (people[mini] + people[maxi] <= limit) {
				maxi--;
			}
			mini++;
			numboats++;
		}

		return numboats;
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
	std::vector<int> people;
	int limit;

	// test case 1
	people = { 1,2 };
	limit = 3;
	std::cout << "numRescueBoats(" << people << ", " << limit << ") = " <<
		sol.numRescueBoats(people, limit) << std::endl;

	// test case 2
	people = { 3,2,2,1 };
	limit = 3;
	std::cout << "numRescueBoats(" << people << ", " << limit << ") = " <<
		sol.numRescueBoats(people, limit) << std::endl;

	// test case 3
	people = { 3,5,3,4 };
	limit = 5;
	std::cout << "numRescueBoats(" << people << ", " << limit << ") = " <<
		sol.numRescueBoats(people, limit) << std::endl;

	return 0;
}