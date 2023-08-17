/*******************************************************************************
 * 0542-01_Matrix.cpp
 * Billy.Ljm
 * 17 August 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/01-matrix/
 *
 * Given an m x n binary matrix mat, return the distance of the nearest 0 for
 * each cell.
 *
 * The distance between two adjacent cells is 1.
 *
 * ===========
 * My Approach
 * ===========
 * We'll use breadth-first search where we visit all the 0's first and add any
 * adjacent cells to the queue. Then, we iterate through the queue which will
 * first include cells of distance 1 then distance 2 and so on.
 *
 * This has a time complexity of O(n*m), and a space complexity of  O(n*m), 
 * where n and m is the height and width of the matrix.
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
	vector<vector<int>> updateMatrix(vector<vector<int>>& mat) {
		size_t nrows = mat.size(), ncols = mat[0].size();
		vector<vector<int>> out(nrows, vector<int>(ncols, -1));
		queue<pair<int, int>> tovisit;

		// initialisation
		for (int i = 0; i < mat.size(); i++) {
			for (int j = 0; j < mat[0].size(); j++) {
				if (mat[i][j] == 0) {
					out[i][j] = 0;
					if (i + 1 < nrows and out[i + 1][j] == -1) {
						tovisit.push({ i + 1, j });
					}
					if (i - 1 >= 0 and out[i - 1][j] == -1) {
						tovisit.push({ i - 1, j });
					}
					if (j + 1 < ncols and out[i][j + 1] == -1) {
						tovisit.push({ i, j + 1 });
					}
					if (j - 1 >= 0 and out[i][j - 1] == -1) {
						tovisit.push({ i, j - 1 });
					}
				}
			}
		};

		// breadth-first search
		int dist = 0;
		int qsize, i, j;
		while (tovisit.size() > 0) {
			dist++;
			qsize = tovisit.size();
			for (int k = 0; k < qsize; k++) {
				// pop queue
				i = tovisit.front().first;
				j = tovisit.front().second;
				tovisit.pop();
				// write current distance
				if (out[i][j] == -1) out[i][j] = dist;
				// queue neigbours
				if (i + 1 < nrows and out[i + 1][j] == -1) {
					tovisit.push({ i + 1, j });
				}
				if (i - 1 >= 0 and out[i - 1][j] == -1) {
					tovisit.push({ i - 1, j });
				}
				if (j + 1 < ncols and out[i][j + 1] == -1) {
					tovisit.push({ i, j + 1 });
				}
				if (j - 1 >= 0 and out[i][j - 1] == -1) {
					tovisit.push({ i, j - 1 });
				}
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
	vector<vector<int>> mat;

	// test case 1
	mat = { {0,0,0},{0,1,0},{0,0,0} };
	std::cout << "updateMatrix(" << mat << ") = ";
	std::cout << sol.updateMatrix(mat) << std::endl;

	// test case 2
	mat = { {0,0,0},{0,1,0},{1,1,1} };
	std::cout << "updateMatrix(" << mat << ") = ";
	std::cout << sol.updateMatrix(mat) << std::endl;

	return 0;
}