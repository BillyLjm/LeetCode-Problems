/*******************************************************************************
 * 0403-Frog_Jump.cpp
 * Billy.Ljm
 * 27 August 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/frog-jump/
 *
 * A frog is crossing a river. The river is divided into some number of units,
 * and at each unit, there may or may not exist a stone. The frog can jump on a
 * stone, but it must not jump into the water.
 *
 * Given a list of stones' positions (in units) in sorted ascending order,
 * determine if the frog can cross the river by landing on the last stone.
 * Initially, the frog is on the first stone and assumes the first jump must be
 * 1 unit.
 *
 * If the frog's last jump was k units, its next jump must be either k - 1, k,
 * or k + 1 units. The frog can only jump in the forward direction.
 *
 * ===========
 * My Approach
 * ===========
 * We have to consider all possibilities of the frogs path. For efficiency, we
 * can memoise identical states where the frog is on the same stone and can jump
 * the same distance.
 *
 * This has a time complexity of O(n^2), and a space complexity of O(n^2), where 
 * n is the length of the river.
 ******************************************************************************/

#include <iostream>
#include <vector>
#include <map>
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
private:
	vector<int>* stones;
	map<pair<int,int>, bool> memo;

	bool recurse(int stone, int dist) {
		pair<int, int> memoid = make_pair(stone, dist);
		// base case
		if (not binary_search(stones->begin(), stones->end(), stone)) return false;
		else if (dist < 0) return false;
		else if (stone == stones->back()) return true;
		// memoised
		else if (memo.find(memoid) != memo.end()) return memo[memoid];
		// recurse
		else {
			if (dist != 0) memo[memoid] = recurse(stone + dist, dist);
			memo[memoid] = memo[memoid] or recurse(stone + dist + 1, dist + 1);
			memo[memoid] = memo[memoid] or recurse(stone + dist - 1, dist - 1);
			return memo[memoid];
		}
	}

public:
	bool canCross(vector<int>& stones) {
		this->stones = &stones;
		this->memo.clear();
		return recurse(0, 0);
	}
};

/**
 * Test cases
 */
int main(void) {
	Solution sol;
	vector<int> stones;

	// test case 1
	stones = { 0,1,3,5,6,8,12,17 };
	std::cout << "canCross(" << stones << ") = ";
	std::cout << std::boolalpha << sol.canCross(stones) << std::endl;

	// test case 2
	stones = { 0,1,2,3,4,8,9,11 };
	std::cout << "canCross(" << stones << ") = ";
	std::cout << std::boolalpha << sol.canCross(stones) << std::endl;

	return 0;
}