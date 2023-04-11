/*******************************************************************************
 * 2390-Removing_Stars_From_a_String.cpp
 * Billy.Ljm
 * 11 Apr 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/removing-stars-from-a-string/
 * You are given a string s, which contains stars *.
 *
 * In one operation, you can:
 * - Choose a star in s.
 * - Remove the closest non-star character to its left, as well as remove the
 *   star itself.
 *
 * Return the string after all stars have been removed.
 *
 * ===========
 * My Approach
 * ===========
 * We just have to iterate through the string, and if the current character is
 * not a star, append it to the stack. Otherwise, pop the top of the stack.
 *
 * This has a time complexity of O(n) and space complexity of O(n), where n is
 * the length of the string.
 ******************************************************************************/

#include <iostream>
#includ e <string>
#include <vector>

class Solution {
public:
    /**
     * Remove stars and its preceding character from a string
     * 
     * @param s string to remove from
     * 
     * @return string with stars and its preceding character removed
     */
	std::string removeStars(std::string s) {
		std::vector<char> out;

		for (char c : s) {
			if (c != '*') {
				out.push_back(c);
			}
			else if (not out.empty()) {
				out.pop_back();
			}
		}

		return std::string(out.begin(), out.end());
	}
};

/**
 * Test cases
 */
int main(void) {
	Solution sol;
	std::string s;

	// test case 1
	s = "leet**cod*e";
	std::cout << "removeStars(" << s << ") = " << sol.removeStars(s) << std::endl;

	// test case 2
	s = "erase*****";
	std::cout << "removeStars(" << s << ") = " << sol.removeStars(s) << std::endl;

	return 0;
}