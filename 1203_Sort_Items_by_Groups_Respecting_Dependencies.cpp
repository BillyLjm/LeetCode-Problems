/*******************************************************************************
 * 1203_Sort_Items_by_Groups_Respecting_Dependencies.cpp
 * Billy.Ljm
 * 20 August 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/sort-items-by-groups-respecting-dependencies/
 *
 * There are n items each belonging to zero or one of m groups where group[i] is
 * the group that the i-th item belongs to and it's equal to -1 if the i-th item
 * belongs to no group. The items and the groups are zero indexed. A group can
 * have no item belonging to it.
 *
 * Return a sorted list of the items such that:
 * - The items that belong to the same group are next to each other in the
 *   sorted list.
 * - There are some relations between these items where beforeItems[i] is a list
 *   containing all the items that should come before the i-th item in the
 *   sorted array (to the left of the i-th item).
 *
 * Return any solution if there is more than one solution and return an empty
 * list if there is no solution.
 *
 * ===========
 * My Approach
 * ===========
 * Items of the same group must be adjacent to each other, so we can think of
 * each group as one block. Then, beforeItems will dictate the relative ordering
 * of these groups, which can be seen as topological sorting of these groups.
 * We also have to topological sort within the group, since they also might have
 * relative ordering.
 *
 * This has a time complexity of O(n^2), and a space complexity of O(n^2), where 
 * n is the number of items to be sorted.
 ******************************************************************************/

#include <iostream>
#include <vector>
#include <set>
#include <queue>

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
	vector<int> sortItems(int n, int m, vector<int>& group,
		vector<vector<int>>& beforeItems) {
		// assign groups
		vector<vector<int>> elems(m);
		for (int i = 0; i < group.size(); i++) {
			if (group[i] != -1) elems[group[i]].push_back(i);
			else {
				group[i] = m;
				elems.push_back({ i });
				m++;
			}
		}

		// count in-degree and adjacency within groups
		vector<int> indeg(n, 0); // indegree of each element
		vector<set<int>> after(n); // after[i] = element after i, within the group
		for (int i = 0; i < beforeItems.size(); i++) {
			for (int j : beforeItems[i]) {
				if (after[j].find(i) == after[j].end() and group[i] == group[j]) {
					after[j].insert(i);
					indeg[i]++;
				}
			}
		}

		// topological sort within each group
		queue<int> qq;
		vector<int> tmp;
		for (int j = 0; j < m; j++) {
			// ignore any single element groups
			if (elems[j].size() == 1) continue;
			// else sort
			tmp.clear();
			for (int i : elems[j]) {
				if (indeg[i] == 0) qq.push(i);
			}
			while (qq.size() > 0) {
				tmp.push_back(qq.front());
				for (int i : after[qq.front()]) {
					indeg[i]--;
					if (indeg[i] == 0) qq.push(i);
				}
				qq.pop();
			}
			// overwrite elems with sorted version
			elems[j].clear();
			elems[j].insert(elems[j].end(), tmp.begin(), tmp.end());
		}
		for (int i : indeg) { // if no topological ordering
			if (i != 0) return vector<int>();
		}

		// count in-degree and adjacency of groups
		indeg = vector<int>(m, 0); // indegree of each group
		after = vector<set<int>>(m); // after[i] = groups after i
		for (int i = 0; i < beforeItems.size(); i++) {
			for (int j : beforeItems[i]) {
				if (after[group[j]].find(group[i]) == after[group[j]].end()
					and group[i] != group[j]) {
					after[group[j]].insert(group[i]);
					indeg[group[i]]++;
				}
			}
		}

		// topological sort groups
		vector<int> grouporder;
		for (int i = 0; i < m; i++) {
			if (indeg[i] == 0) qq.push(i);
		}
		while (qq.size() > 0) {
			grouporder.push_back(qq.front());
			for (int i : after[qq.front()]) {
				indeg[i]--;
				if (indeg[i] == 0) qq.push(i);
			}	
			qq.pop();
		}
		for (int i : indeg) { // if no topological ordering
			if (i != 0) return vector<int>(); 
		}

		// form output
		vector<int> out;
		for (int group : grouporder) {
			out.insert(out.end(), elems[group].begin(), elems[group].end());
		}
		return out;
	}
};

/**
 * Test cases
 */
int main(void) {
	Solution sol;
	int n, m;
	vector<int> group;
	vector<vector<int>> beforeItems;

	// test case 1
	n = 8;
	m = 2;
	group = { -1,-1,1,0,0,1,0,-1 };
	beforeItems = { {},{6},{5},{6},{3,6},{},{},{} };
	std::cout << "sortItems(" << n << "," << m << "," << group << ","
		<< beforeItems << ") = ";
	std::cout << sol.sortItems(n, m, group, beforeItems) << std::endl;

	// test case 2
	n = 8;
	m = 2;
	group = { -1,-1,1,0,0,1,0,-1 };
	beforeItems = { {},{6},{5},{6},{3},{},{4},{} };
	std::cout << "sortItems(" << n << "," << m << "," << group << ","
		<< beforeItems << ") = ";
	std::cout << sol.sortItems(n, m, group, beforeItems) << std::endl;

	return 0;
}