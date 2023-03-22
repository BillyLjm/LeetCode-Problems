/*******************************************************************************
 * 2492-Minimum_Score_of_a_Path_Between_Two_Cities.cpp
 * Billy.Ljm
 * 22 Mar 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/minimum-score-of-a-path-between-two-cities/
 * You are given a positive integer n representing n cities numbered from 1 to n.
 * You are also given a 2D array roads where roads[i] = [ai, bi, distancei]
 * indicates that there is a bidirectional road between cities ai and bi with a
 * distance equal to distancei. The cities graph is not necessarily connected.
 * The score of a path between two cities is defined as the minimum distance of
 * a road in this path. Return the minimum possible score of a path between
 * cities 1 and n.
 *
 * ===========
 * My Approach
 * ===========
 * The question is essentially asking us to find the set of cities which are
 * (indirectly) linked to cities 1 and n. We can do this using a disjoint-set
 * data structure. We then have to return the minimum distance of in the
 * aforementioned set.
 *
 * https://www.geeksforgeeks.org/union-by-rank-and-path-compression-in-union-find-algorithm/
 * We will use union by rank and path compression for our union & find, as
 * described in the website above. This would result in each union/find having
 * O(n) runtime.
 *
 * Thus, the overall time complexity would be O(n*e), and space complexity be
 * O(n), where n is the number of cities and e is the number of edges.
 *
 * Apparently, this doesn't do very well in terms of runtime in LeetCode. It
 * seems to be in the bottom 5th percentile. Nevertheless, I never implemented
 * this algorithm before and think it'll be cool to keep.
 ******************************************************************************/

#include <iostream>
#include <vector>
#include <map>

class Solution {
public:
	/**
	 * Finds the minimum road distance that is connected to city 1 and city n
	 *
	 * @param n index of city to connect to, other than city 1
	 * @param roads [city1, city2, distance] of each road
	 *
	 * @return minimum road distance that is connected to city 1 and city n
	 */
	int minScore(int n, std::vector<std::vector<int>>& roads) {
		std::map<int, int> mindist; // {city: minimum road distance}
		std::map<int, subset> subsets; // disjoint-set {child/city: parent/set}

		for (const std::vector<int> road : roads) {
			// update mindist
			if (mindist[road[0]] == NULL or mindist[road[0]] > road[2]) {
				mindist[road[0]] = road[2];
			}
			if (mindist[road[1]] == NULL or mindist[road[1]] > road[2]) {
				mindist[road[1]] = road[2];
			}

			// insert new cities into set
			if (subsets.find(road[0]) == subsets.end()) {
				subsets[road[0]].parent = road[0];
				subsets[road[0]].rank = 0;
			}
			if (subsets.find(road[1]) == subsets.end()) {
				subsets[road[1]].parent = road[1];
				subsets[road[1]].rank = 0;
			}

			// disjoint-set algorithm
			unionn(subsets, find(subsets, road[0]), find(subsets, road[1]));
		}

		// check city 0 and n connected
		int index = find(subsets, 1);
		if (index != find(subsets, n)) {
			return -1;
		}

		// find minimum distance of desired set
		int out = mindist[1];
		for (const auto& x : mindist) {
			if (x.second < out) {
				if (find(subsets, x.first) == index) {
					out = x.second;
				}
			}
		}
		return out;
	}

private:
	/**
	 * Disjoint-set data structure
	 * https://www.geeksforgeeks.org/union-by-rank-and-path-compression-in-union-find-algorithm/
	 */
	struct subset {
		int parent;
		int rank;
	};

	/**
	 * Find set of city. Uses path compression.
	 * https://www.geeksforgeeks.org/union-by-rank-and-path-compression-in-union-find-algorithm/
	 *
	 * @param subsets disjoint-set {child/city: parent/set}
	 * @param i city to find
	 *
	 * @return parent of city i
	 */
	int find(std::map<int, subset>& subsets, int i) {
		if (subsets[i].parent != i) {
			subsets[i].parent = find(subsets, subsets[i].parent);
		}
		return subsets[i].parent;
	}

	/**
	 * Union of connected cities. Uses union by rank.
	 * https://www.geeksforgeeks.org/union-by-rank-and-path-compression-in-union-find-algorithm/
	 *
	 * @param subsets disjoint-set {child/city: parent/set}
	 * @param xroot parent of city x
	 * @param yroot parent of city y
	 */
	void unionn(std::map<int, subset>& subsets, int xroot, int yroot) {
		if (subsets[xroot].rank < subsets[yroot].rank) {
			subsets[xroot].parent = yroot;
		}
		else if (subsets[xroot].rank > subsets[yroot].rank) {
			subsets[yroot].parent = xroot;
		}
		else {
			subsets[yroot].parent = xroot;
			subsets[xroot].rank++;
		}
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
	int n;
	std::vector<std::vector<int>> roads;

	// test case 1
	n = 4;
	roads = { {1,2,9}, {2,3,6}, {2,4,5}, {1,4,7} };
	std::cout << "minScore(" << n << ", " << roads << ") = "
		<< sol.minScore(n, roads) << std::endl;

	// test case 2
	n = 4;
	roads = { {1,2,2}, {1,3,4}, {3,4,7} };
	std::cout << "minScore(" << n << ", " << roads << ") = "
		<< sol.minScore(n, roads) << std::endl;

	return 0;
}