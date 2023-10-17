/*******************************************************************************
 * 1361-Validate_Binary_Tree_Nodes.cpp
 * Billy.Ljm
 * 17 October 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/validate-binary-tree-nodes/
 *
 * You have n binary tree nodes numbered from 0 to n - 1 where node i has two
 * children leftChild[i] and rightChild[i], return true if and only if all the
 * given nodes form exactly one valid binary tree.
 *
 * If node i has no left child then leftChild[i] will equal -1, similarly for
 * the right child.
 *
 * Note that the nodes have no values and that we only use the node numbers in
 * this problem.
 *
 * ===========
 * My Approach
 * ===========
 * Each parent is already guaranteed to at most have 2 children. Thus, all that
 * is left to check is that each child has only one parent, that all nodes are
 * connected, and that there are no no cycles in the tree. All of these can be
 * checked in a modified union-find algorithm.
 *
 * This has a time complexity of O(n * alpha(n)), and space complexity of O(n),
 * where n is number of nodes. 
 ******************************************************************************/

#include <iostream>
#include <vector>
#include <numeric>

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
 * Union-find/Disjoint-set data structure
 */
class UnionFind {
private:
	std::vector<int> parent;

public:
	/**
	 * Class Constructor
	 *
	 * @param size total number of nodes
	 */
	UnionFind(int size) {
		parent = std::vector<int>(size);
		std::iota(std::begin(parent), std::end(parent), 0);
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
	 * @param pnode parent node to union with child node
	 * @param cnode child node to union with parent node
	 * @return true if a non-binary-tree is detected
	 */
	bool unionn(int pnode, int cnode) {
		// path compression
		int proot = find(pnode);
		int croot = find(cnode);

		// checks
		if (croot != cnode) return true; // check if child has parents
		else if (proot == croot) return true; // check for cycles
		else { // all checks passed, union-find
			parent[cnode] = proot;
			return false;
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

/**
 * Solution
 */
class Solution {
public:
	bool validateBinaryTreeNodes(int n, vector<int>& leftChild, vector<int>& rightChild) {
		UnionFind uf(n);

		// union-find; checking for no cycles and one parent
		for (int i = 0; i < n; i++) {
			if (leftChild[i] != -1 && uf.unionn(i, leftChild[i])) return false;
			if (rightChild[i] != -1 && uf.unionn(i, rightChild[i])) return false;
		}

		// checking for disjoint subsets
		return (uf.count() == 1);
	}
};

/**
 * Test cases
 */
int main(void) {
	Solution sol;
	int n;
	vector<int> leftChild, rightChild;

	// test case 1
	n = 4;
	leftChild = { 1,-1,3,-1 };
	rightChild = { 2,-1,-1,-1 };
	std::cout << "validateBinaryTreeNodes(" << n << "," << leftChild << ","
		<< rightChild << ") = ";
	std::cout << std::boolalpha <<
		sol.validateBinaryTreeNodes(n, leftChild, rightChild) << std::endl;

	// test case 2
	n = 4;
	leftChild = { 1,-1,3,-1 };
	rightChild = { 2,3,-1,-1 };
	std::cout << "validateBinaryTreeNodes(" << n << "," << leftChild << ","
		<< rightChild << ") = ";
	std::cout << std::boolalpha <<
		sol.validateBinaryTreeNodes(n, leftChild, rightChild) << std::endl;

	// test case 3
	n = 2;
	leftChild = { 1,0 };
	rightChild = { -1,-1 };
	std::cout << "validateBinaryTreeNodes(" << n << "," << leftChild << ","
		<< rightChild << ") = ";
	std::cout << std::boolalpha <<
		sol.validateBinaryTreeNodes(n, leftChild, rightChild) << std::endl;

	return 0;
}