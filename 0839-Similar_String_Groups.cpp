/*******************************************************************************
 * 0839-Similar_String_Groups.cpp
 * Billy.Ljm
 * 28 Apr 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/similar-string-groups/
 * Two strings X and Y are similar if we can swap two letters (in different
 * positions) of X, so that it equals Y. Also two strings X and Y are similar if
 * they are equal.
 *
 * For example, "tars" and "rats" are similar (swapping at positions 0 and 2),
 * and "rats" and "arts" are similar, but "star" is not similar to "tars",
 * "rats", or "arts".

 * Together, these form two connected groups by similarity: {"tars", "rats",
 * "arts"} and {"star"}.  Notice that "tars" and "arts" are in the same group
 * even though they are not similar.  Formally, each group is such that a word
 * is in the group if and only if it is similar to at least one other word in
 * the group.
 *
 * We are given a list strs of strings where every string in strs is an anagram
 * of every other string in strs. How many groups are there?
 *
 * ===========
 * My Approach
 * ===========
 * We can use union-find to form the similarity groups, with the edges being
 * calculated on the fly by comparing each pair of strings. Then, we just have
 * to count the number of disjoint sets at the end.
 *
 * This has a time complexity of O(n^2 * m) and space complexity of (n),
 * where n is the number of strings and m is the max length of each string.
 ******************************************************************************/

#include <iostream>
#include <vector>
#include <string>
#include <numeric>

/**
 * Union-find/Disjoint-set data structure
 */
class UnionFind {
private:
	std::vector<int> parent, rank;

public:
	/**
	 * Class Constructor
	 *
	 * @param size total number of nodes
	 */
	UnionFind(int size) {
		parent = std::vector<int>(size);
		std::iota(std::begin(parent), std::end(parent), 0);
		rank = std::vector<int>(size, 0);
	}

	/**
	 * Find set of node. Uses path compression.
	 *
	 * @param i node to find parent of
	 *
	 * @return parent of node[i]
	 */
	int find(int i) {
		if (parent[i] != i) {
			parent[i] = find(parent[i]);
		}
		return parent[i];
	}

	/**
	 * Union of connected cities. Uses union by rank.
	 *
	 * @param x node to union with y
	 * @param y node to union with x
	 */
	void unionn(int x, int y) {
		int xroot = find(x);
		int yroot = find(y);

		if (rank[xroot] < rank[yroot]) {
			parent[xroot] = yroot;
		}
		else if (rank[xroot] > rank[yroot]) {
			parent[yroot] = xroot;
		}
		else {
			parent[yroot] = xroot;
			rank[xroot]++;
		}
	}

	/**
	 * Count number of disjoint subsets
	 *
	 * @return number of disjoint subsets
	 */
	int count() {
		int size = 0;
		for (int i = 0; i < parent.size(); i++) {
			if (parent[i] == i) {
				size++;
			}
		}
		return size;
	}
};

class Solution {
public:
	/**
	 * Checks if two strings are similar (i.e. differ by a char swap)
	 *
	 * @param str1 string to compare against str2
	 * @param str2 string to compare against str1
	 *
	 * @return true if str1 and str2 are similar, false otherwise
	 */
	bool isSimilar(std::string str1, std::string str2) {
		// check if same length
		if (str1.size() != str2.size()) {
			return false;
		}
		
		// count number of different chars
		int diff = 0;
		for (int i = 0; i < str1.size(); i++) {
			if (str1[i] != str2[i]) {
				diff++;
			}
			if (diff > 2) { // short-circuit
				return false;
			}
		}

		// check if similar
		return (diff == 0 or diff == 2);
	}

	/**
	 * Count number of similar groups in an array of strings. Strings are
	 * similar if they differ by a char swap.
	 *
	 * @param strs array of strings to check
	 *
	 * @return number of disjoint similar groups in strs
	 */
	int numSimilarGroups(std::vector<std::string>& strs) {
		UnionFind uf(strs.size());

		// union-find algorithm
		for (int i = 0; i < strs.size(); i++) {
			for (int j = i + 1; j < strs.size(); j++) {
				if (isSimilar(strs[i], strs[j])) {
					uf.unionn(i, j);
				}
			}
		}

		// count disjoint sets
		return uf.count();
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
	std::vector<std::string> strs;
	
	// test case 1
	strs = { "tars", "rats", "arts", "star" };
	std::cout << "numSimilarGroups(" << strs << ") = " <<
		sol.numSimilarGroups(strs) << std::endl;

	// test case 2
	strs = { "omv", "ovm" };
	std::cout << "numSimilarGroups(" << strs << ") = " <<
		sol.numSimilarGroups(strs) << std::endl;

	// test case 3
	strs = { "abc", "abc" };
	std::cout << "numSimilarGroups(" << strs << ") = " <<
		sol.numSimilarGroups(strs) << std::endl;

	return 0;
}