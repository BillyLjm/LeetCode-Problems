/*******************************************************************************
 * 1456-Maximum_Number_of_Vowels_in_a_Substing_of_Given_Length.cpp
 * Billy.Ljm
 * 05 May 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/maximum-number-of-vowels-in-a-substring-of-given-length/
 *
 * Given a string s and an integer k, return the maximum number of vowel letters
 * in any substring of s with length k.
 *
 * Vowel letters in English are 'a', 'e', 'i', 'o', and 'u'.
 *
 * ===========
 * My Approach
 * ===========
 * We can check the first substring, pop the first character and add the next
 * one (checking if each is a vowel), and then iterate until the end of the
 * string.
 *
 * This has a time complexity of O(n) and space complexity of O(1), where n is
 * the length of the string.
 ******************************************************************************/

#include <iostream>
#include <vector>
#include <string>

/**
 * Solution
 */
class Solution {
public:
	/**
	 * Finds the maximum number of vowels in any substring of given length
	 * 
	 * @param s string to take substrings of
	 * @param k length of substrings to take
	 * 
	 * @return maximum number of vowels in any k-long substring of string s
	 */
	int maxVowels(std::string s, int k) {
		int num = 0; // number of vowels in current substring
		int maxnum = 0; // max number of vowels
		auto isvowel = [](char c) { // lambda function to check if char is vowel
			return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
		};

		// count  first substring
		for (int i = 0; i < k; i++) {
			if (isvowel(s[i])) {
				num++;
			}
		}
		maxnum = num;

		// consider all other substrings
		for (int i = k; i < s.size(); i++) {
			if (isvowel(s[i - k])) { // delete previous char
				num--;
			}
			if (isvowel(s[i])) { // add next char
				num++;
			}
			if (num > maxnum) { // remember max
				maxnum = num;
			}
		}

		return maxnum;
	}
};

/**
 * Test cases
 */
int main(void) {
	Solution sol;
	std::string s;
	int k;

	// test case 1
	s = "abciiidef";
	k = 3;
	std::cout << "maxVowels(" << s << "," << k << ") = " << sol.maxVowels(s, k)
		<< std::endl;

	// test case 2
	s = "aeiou";
	k = 2;
	std::cout << "maxVowels(" << s << "," << k << ") = " << sol.maxVowels(s, k)
		<< std::endl;

	// test case 3
	s = "leetcode";
	k = 3;
	std::cout << "maxVowels(" << s << "," << k << ") = " << sol.maxVowels(s, k)
		<< std::endl;

	return 0;
}