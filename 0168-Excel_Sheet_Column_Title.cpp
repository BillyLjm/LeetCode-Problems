/*******************************************************************************
 * 0168-Excel_Sheet_Column_Title.cpp
 * Billy.Ljm
 * 22 August 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/excel-sheet-column-title/
 *
 * Given an integer columnNumber, return its corresponding column title as it
 * appears in an Excel sheet.
 *
 * For example:
 * A -> 1
 * B -> 2
 * C -> 3
 * ...
 * Z -> 26
 * AA -> 27
 * AB -> 28
 * ...
 *
 * ===========
 * My Approach
 * ===========
 * This is identical to decimal to binary conversion.
 *
 * This has a time complexity of O(log n), and a space complexity of O(log n),
 * where n is the column number.
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
	string convertToTitle(int columnNumber) {
		string out = "";
		while (columnNumber > 0) {
			columnNumber--;
			out = out + (char)('A' + (columnNumber % 26));
			columnNumber = columnNumber / 26;
		}
		reverse(out.begin(), out.end());
		return out;
	}
};

/**
 * Test cases
 */
int main(void) {
	Solution sol;
	int columnNumber;

	// test case 1
	columnNumber = 1;
	std::cout << "convertToTitle(" << columnNumber << ") = ";
	std::cout << sol.convertToTitle(columnNumber) << std::endl;

	// test case 2
	columnNumber = 28;
	std::cout << "convertToTitle(" << columnNumber << ") = ";
	std::cout << sol.convertToTitle(columnNumber) << std::endl;

	// test case 3
	columnNumber = 701;
	std::cout << "convertToTitle(" << columnNumber << ") = ";
	std::cout << sol.convertToTitle(columnNumber) << std::endl;

	return 0;
}