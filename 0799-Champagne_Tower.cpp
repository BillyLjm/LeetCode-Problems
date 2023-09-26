/*******************************************************************************
 * 0799-Champagne_Tower.cpp
 * Billy.Ljm
 * 24 September 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/champagne-tower/
 *
 * We stack glasses in a pyramid, where the first row has 1 glass, the second
 * row has 2 glasses, and so on until the 100th row.  Each glass holds one cup
 * of champagne.
 *
 * Then, some champagne is poured into the first glass at the top.  When the
 * topmost glass is full, any excess liquid poured will fall equally to the
 * glass immediately to the left and right of it.  When those glasses become
 * full, any excess champagne will fall equally to the left and right of those
 * glasses, and so on.  (A glass at the bottom row has its excess champagne fall
 * on the floor.)
 *
 * For example, after one cup of champagne is poured, the top most glass is full.
 * After two cups of champagne are poured, the two glasses on the second row are
 * half full.  After three cups of champagne are poured, those two cups become
 * full - there are 3 full glasses total now.  After four cups of champagne are
 * poured, the third row has the middle glass half full, and the two outside
 * glasses are a quarter full, as pictured below.
 *
 * Now after pouring some non-negative integer cups of champagne, return how
 * full the jth glass in the ith row is (both i and j are 0-indexed.)
 *
 * ===========
 * My Approach
 * ===========
 * We can simulate the actual physical process described above. Pouring n cups
 * of champagne into the top glass translates to a deterministic number of cups
 * flowing through each of the lower glasses, varying based on the exact location
 * of the lower glasses.
 *
 * This has a time complexity of O(n^2), and a space complexity of O(n^2), where
 * n is the row number of queried glass.
 ******************************************************************************/

#include <iostream>
#include <vector>

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
	double champagneTower(int poured, int query_row, int query_glass) {
		// flow[i][j] = cups flowing through i-th row's j-th glass
		vector<vector<double>> flow(query_row + 1);
		flow[0] = { (double) poured };
		for (int i = 1; i <= query_row; i++) flow[i] = vector<double>(i + 1, 0.0);

		// simulate process
		for (int i = 1; i <= query_row; i++) {
			for (int j = 0; j < i + 1; j++) {
				if (j < i) flow[i][j] += max(0.0, (flow[i - 1][j] - 1) / 2);
				if (j - 1 >= 0) flow[i][j] += max(0.0, (flow[i - 1][j - 1] - 1) / 2);
			}
		}

		return min(1.0, flow[query_row][query_glass]);
	}
};

/**
 * Test cases
 */
int main(void) {
	Solution sol;
	int poured, query_row, query_glass;

	// test case 1
	poured = 1;
	query_row = 1;
	query_glass = 1;
	std::cout << "champagneTower(" << poured << "," << query_row << "," <<
		query_glass << ") = ";
	std::cout << sol.champagneTower(poured, query_row, query_glass) << std::endl;

	// test case 2
	poured = 2;
	query_row = 1;
	query_glass = 1;
	std::cout << "champagneTower(" << poured << "," << query_row << "," <<
		query_glass << ") = ";
	std::cout << sol.champagneTower(poured, query_row, query_glass) << std::endl;

	// test case 3
	poured = 100000009;
	query_row = 33;
	query_glass = 17;
	std::cout << "champagneTower(" << poured << "," << query_row << "," <<
		query_glass << ") = ";
	std::cout << sol.champagneTower(poured, query_row, query_glass) << std::endl;

	return 0;
}