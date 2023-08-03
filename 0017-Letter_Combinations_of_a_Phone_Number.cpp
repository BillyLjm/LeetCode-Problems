/*******************************************************************************
 * 0017-Letter_Combinations_of_a_Phone_Number.cpp
 * Billy.Ljm
 * 03 August 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/letter-combinations-of-a-phone-number/
 *
 * Given a string containing digits from 2-9 inclusive, return all possible
 * letter combinations that the number could represent. Return the answer in any
 * order.
 *
 * ===========
 * My Approach
 * ===========
 * Since we have to generate each possible permutation, we have no choice but to
 * iterate through each of them. We'll do this recursively, one digit at a time.
 *
 * This has a time complexity of O(3^n * n), and a space complexity of O(3^n),
 * where n is the length of the string.
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
	for (int i = 0; i < v.size(); i++) {
		os << v[i] << ",";
	}
	os << "\b]";
	return os;
}

/**
 * Solution
 */
class Solution {
private:
	map<char, vector<char>> mapp;

public:
	Solution() {
		// telephone button mappings
		mapp.insert({ '2', vector<char>({'a', 'b', 'c'}) });
		mapp.insert({ '3', vector<char>({'d', 'e', 'f'}) });
		mapp.insert({ '4', vector<char>({'g', 'h', 'i'}) });
		mapp.insert({ '5', vector<char>({'j', 'k', 'l'}) });
		mapp.insert({ '6', vector<char>({'m', 'n', 'o'}) });
		mapp.insert({ '7', vector<char>({'p', 'q', 'r', 's'}) });
		mapp.insert({ '8', vector<char>({'t', 'u', 'v'}) });
		mapp.insert({ '9', vector<char>({'w', 'x', 'y', 'z'}) });
		mapp.insert({ '0', vector<char>({' '}) });
	}

	vector<string> letterCombinations(string digits) {
		// edge case
		if (digits.size() == 0) return vector<string>(0);

		// base case
		if (digits.size() == 1) {
			vector<string> out;
			for (char c : mapp[digits.back()]) {
				out.push_back(string(1, c));
			}
			return out;
		}

		// general case
		else {
			// recrurse preceeding digit
			vector<string> prev = letterCombinations(digits.substr(0, digits.size() - 1));
			// add last digit
			vector<string> out;
			for (char c : mapp[digits.back()]) {
				for (string s : prev) {
					out.push_back(s + c);
				}
			}
			return out;
		}
		
	}
};

/**
 * Test cases
 */
int main(void) {
	Solution sol;
	string digits;

	// test case 1
	digits = "23";
	std::cout << "letterCombinations(" << digits << ") = ";
	std::cout << sol.letterCombinations(digits) << std::endl;

	// test case 2
	digits = "";
	std::cout << "letterCombinations(" << digits << ") = ";
	std::cout << sol.letterCombinations(digits) << std::endl;

	// test case 3
	digits = "2";
	std::cout << "letterCombinations(" << digits << ") = ";
	std::cout << sol.letterCombinations(digits) << std::endl;

	return 0;
}