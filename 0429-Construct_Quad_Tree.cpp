/******************************************************************************
 * 429-Construct_Quad_Tree.cpp
 * Billy.Ljm
 * 27 Feb 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/construct-quad-tree/description/
 * Given a n * n matrix grid of 0's and 1's only. We want to represent the grid
 * with a Quad-Tree. Return the root of the Quad-Tree representing the grid.
 *
 * ===========
 * My Approach
 * ===========
 * I will recursively break down the matrix into smaller and smaller quadrants.
 * The base quadrant will be a single matrix element, and larger quadrants can
 * be constructed by aggregating 4 of the smaller quadrants each time.
 *
 * This would result in a log(n)-deep recursion tree, with 4 leaves per nodes
 * and a constant number of operations per node. Thus, it has a time complexity
 * of O(n^2) and a space complexity of O(log(n)), where n is the width of one
 * axis of the matrix.
 *
 * Care has to be taken to ensure there is no memory leak from losing track of
 * any allocated nodes that get aggregated into a single leaf.
 *****************************************************************************/

#include <iostream>
#include <vector>
#include <cassert>

/**
 * Definition for a QuadTree node.
 */
class Node {
public:
	bool val;
	bool isLeaf;
	Node* topLeft;
	Node* topRight;
	Node* bottomLeft;
	Node* bottomRight;

	Node() {
		val = false;
		isLeaf = false;
		topLeft = NULL;
		topRight = NULL;
		bottomLeft = NULL;
		bottomRight = NULL;
	}

	Node(bool _val, bool _isLeaf) {
		val = _val;
		isLeaf = _isLeaf;
		topLeft = NULL;
		topRight = NULL;
		bottomLeft = NULL;
		bottomRight = NULL;
	}

	Node(bool _val, bool _isLeaf, Node* _topLeft, Node* _topRight,
		Node* _bottomLeft, Node* _bottomRight) {
		val = _val;
		isLeaf = _isLeaf;
		topLeft = _topLeft;
		topRight = _topRight;
		bottomLeft = _bottomLeft;
		bottomRight = _bottomRight;
	}
};

class Solution {
public:
	/**
	 * Constructs QuadTree from square matrix given by `grid`
	 *
	 * @param grid matrix grid to convert into a QuadTree
	 *
	 * @return root of the converted QuadTree
	 */
	Node* construct(std::vector<std::vector<int>>& grid) {
		assert(grid.size() == grid[0].size());
		return recurse(grid, 0, 0, grid.size());
	}

	/**
	 * Delete and deallocate QuadTree
	 *
	 * @param node root of the QuadTree to be deleted
	 *
	 * @return 0 if normal termination
	 */
	int del(Node* node) {
		if (not node->isLeaf) {
			del(node->topLeft);
			del(node->topRight);
			del(node->bottomLeft);
			del(node->bottomRight);
		}
		delete node;
		return 0;
	}

private:
	/**
	 * Recursively construct QuadTree from square matrix
	 *
	 * @param grid large matrix containing the submatrix to construct from
	 * @param x first x-index of submatrix (i.e. grid[x: x + length][y])
	 * @param y first y-index of submatrix (i.e. grid[x][y: y + length])
	 * @param length length (along one axis) of submatrix
	 *
	 * @return root of the converted QuadTree
	 */
	Node* recurse(std::vector<std::vector<int>>& grid, size_t x, size_t y,
		size_t length) {
		// base case: 1 element matrix
		if (length == 1) {
			return new Node(grid[y][x], true);
		}
		else {
			// recursively construct sub-tree from sub-quadrants
			size_t nlength = length / 2;
			Node* topLeft = recurse(grid, x, y, nlength);
			Node* topRight = recurse(grid, x + nlength, y, nlength);
			Node* bottomLeft = recurse(grid, x, y + nlength, length - nlength);
			Node* bottomRight = recurse(grid, x + nlength, y + nlength,
				length - nlength);

			// if sub-tree are leaves with all 0's or all 1's, construct leaf
			if (topLeft->isLeaf and topRight->isLeaf and
				bottomLeft->isLeaf and bottomRight->isLeaf and
				topLeft->val == topRight->val and
				topLeft->val == bottomLeft->val and
				bottomLeft->val == bottomRight->val) {
				// data cleanup
				bool val = topLeft->val;
				delete topLeft;
				delete topRight;
				delete bottomLeft;
				delete bottomRight;
				// construct leaf
				return new Node(val, true);
			}
			// else construct branch
			else {
				return new Node(true, false, topLeft, topRight, bottomLeft,
					bottomRight);
			}
		}
	}
};

/**
 * Print operator for the vector class
 */
std::ostream& operator<<(std::ostream& os,
	const std::vector<std::vector<int>> vector) {
	os << "[";
	for (size_t i = 0; i < vector.size(); i++) {
		os << "[";
		for (size_t j = 0; j < vector[0].size(); j++) {
			os << vector[i][j] << ",";
		}
		os << "\b],";
	}
	os << "\b]";
	return os;
};

/**
 * Print operator for the Node/QuadTree class
 * Note: this is different from the problem statement; this is recursive order,
 * not a breadth-first/layer wise ordering
 */
std::ostream& operator<<(std::ostream& os, const Node* node) {
	os << "[" << node->isLeaf << "," << node->val << "],";
	if (not node->isLeaf) {
		os << node->topLeft << node->topRight << node->bottomLeft <<
			node->bottomRight;
	}
	return os;
};

/**
 * Test cases
 */
int main() {
	Solution sol;

	// test case 1
	std::vector<std::vector<int>> grid1{ {0, 1}, {1, 0} };
	Node* tree1 = sol.construct(grid1);
	std::cout << "grid: " << grid1 << "\ntree: " << tree1 << "\n";


	// test case 2
	std::vector<std::vector<int>> grid2{
		{1,1,1,1,0,0,0,0},{1,1,1,1,0,0,0,0},{1,1,1,1,1,1,1,1},{1,1,1,1,1,1,1,1},
		{1,1,1,1,0,0,0,0},{1,1,1,1,0,0,0,0},{1,1,1,1,0,0,0,0},{1,1,1,1,0,0,0,0}
	};
	Node* tree2 = sol.construct(grid2);
	std::cout << "grid: " << grid2 << "\ntree: " << tree2 << "\n";

	return 0;
}