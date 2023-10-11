/*******************************************************************************
 * 2251-Number_of_Flowers_in_Full_Bloom.cpp
 * Billy.Ljm
 * 11 October 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/number-of-flowers-in-full-bloom/
 *
 * You are given a 0-indexed 2D integer array flowers, where flowers[i] =
 * [starti, endi] means the ith flower will be in full bloom from starti to endi
 * (inclusive). You are also given a 0-indexed integer array people of size n,
 * where people[i] is the time that the ith person will arrive to see the flowers.
 *
 * Return an integer array answer of size n, where answer[i] is the number of
 * flowers that are in full bloom when the ith person arrives.
 *
 * ===========
 * My Approach
 * ===========
 * We can count the number of flowers that have bloomed and that have withered,
 * and their difference will be the number that are currently blooming. The
 * number of timesteps can be very large, up to 10^9, thus we will not simulate
 * every time step. Instead, we will count the numbers for each person using
 * binary search.
 * 
 * This has a time complexity of O((f + p) log f), and space complexity of
 * O(f), where f and p are the number of flowers and people respectively.
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
	vector<int> fullBloomFlowers(vector<vector<int>>& flowers, vector<int>& people) {
		// separate start and end
		vector<int> start(flowers.size());
		vector<int> end(flowers.size());
		for (int i = 0; i < flowers.size(); i++) {
			start[i] = flowers[i][0];
			end[i] = flowers[i][1];
		}

		// sort for binary search
		sort(start.begin(), start.end());
		sort(end.begin(), end.end());

		// binary search for each person
		vector<int> out(people.size());
		for (int i = 0; i < people.size(); i++) {
			out[i] = upper_bound(start.begin(), start.end(), people[i])
				- start.begin();
			out[i] -= upper_bound(end.begin(), end.end(), people[i] - 1)
				- end.begin();
		}

		return out;
	}
};

/**
 * Test cases
 */
int main(void) {
	Solution sol;
	vector<vector<int>> flowers;
	vector<int> people;

	// test case 1
	flowers = { {1,6},{3,7},{9,12},{4,13} };
	people = { 2,3,7,11 };
	std::cout << "fullBloomFlowers(" << flowers << "," << people << ") = ";
	std::cout << sol.fullBloomFlowers(flowers, people) << std::endl;

	// test case 2
	flowers = { {1,10},{3,3} };
	people = { 3,3,2 };
	std::cout << "fullBloomFlowers(" << flowers << "," << people << ") = ";
	std::cout << sol.fullBloomFlowers(flowers, people) << std::endl;

	return 0;
}