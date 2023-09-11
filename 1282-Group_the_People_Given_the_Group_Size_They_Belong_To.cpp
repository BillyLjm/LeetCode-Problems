/*******************************************************************************
 * 1282-Group_the_People_Given_the_Group_Size_They_Belong_To.cpp
 * Billy.Ljm
 * 11 September 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/group-the-people-given-the-group-size-they-belong-to/
 *
 * There are n people that are split into some unknown number of groups. Each
 * person is labelled with a unique ID from 0 to n - 1.
 *
 * You are given an integer array groupSizes, where groupSizes[i] is the size of
 * the group that person i is in. For example, if groupSizes[1] = 3, then person
 * 1 must be in a group of size 3.
 *
 * Return a list of groups such that each person i is in a group of size
 * groupSizes[i].
 *
 * ===========
 * My Approach
 * ===========
 * We can just iterate through the list and allocate the people of similar group
 * sizes together, up until the specified group size is reached.
 *
 * This has a time complexity of O(n), and a space complexity of O(1), where
 * n is the number of people.
 ******************************************************************************/

#include <iostream>
#include <vector>
#include <map>

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
	vector<vector<int>> groupThePeople(vector<int>& groupSizes) {
		vector<vector<int>> out;
		map<int, int> grpidx; // out[grpidx[grpsize]] is group to fill

		for (int i = 0; i < groupSizes.size(); i++) {
			// first group of current size, or previous group filled
			if (grpidx.find(groupSizes[i]) == grpidx.end() or
				out[grpidx[groupSizes[i]]].size() == groupSizes[i]) {
				out.push_back({ i });
				grpidx[groupSizes[i]] = out.size() - 1;
			}
			// current group yet to be filled
			else {
				out[grpidx[groupSizes[i]]].push_back(i);
			}
		}

		return out;
	}
};

/**
 * Test cases
 */
int main(void) {
	Solution sol;
	vector<int> groupSizes;

	// test case 1
	groupSizes = { 3,3,3,3,3,1,3 };
	std::cout << "groupThePeople(" << groupSizes << ") = ";
	std::cout << sol.groupThePeople(groupSizes) << std::endl;

	// test case 2
	groupSizes = { 2,1,3,3,3,2 };
	std::cout << "groupThePeople(" << groupSizes << ") = ";
	std::cout << sol.groupThePeople(groupSizes) << std::endl;

	return 0;
}