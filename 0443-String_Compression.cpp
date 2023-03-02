/*******************************************************************************
 * 0443-Sort_an_Array.cpp
 * Billy.Ljm
 * 02 Mar 2023
 *
 * =======
 * Problem
 * =======
 * Given an array of characters chars, compress it using the following
 * algorithm: Begin with an empty string s. For each group of consecutive
 * repeating characters in chars, if the group's length is 1, append the
 * character to s. Otherwise, append the character followed by the group's
 * length. The compressed string s should not be returned separately, but
 * instead, be stored in the input character array chars. Note that group
 * lengths that are 10 or longer will be split into multiple characters in
 * chars. After you are done modifying the input array, return the new length of
 * the array. You must write an algorithm that uses only constant extra space.
 *
 * ===========
 * My Approach
 * ===========
 * The approach is pretty straightforward, just iterate through each character,
 * remember if the previous character(s) is different or the same, and mutate
 * the input array accordingly. We'll have two crawling indices, one for
 * iterating through the input array (i), and one for remembering the end of our
 * new array consisting of the overwritten elements (nlen).
 *
 * The time complexity is O(n), and the space complexity is O(1), were n is the
 * size of the input array.
 ******************************************************************************/

#include <iostream>
#include <vector>
#include <string>

class Solution {
public:
	/**
	 * Compresses a string, with consecutive identical characters being
	 * compressed into [..., prev_char, identical_char, num_identical, ...]
	 *
	 * @param chars string to be compressed
	 *
	 * @return length of compressed string; original string is mutated
	 */
	int compress(std::vector<char>& chars) {
		int count = 1; // to count consecutive number of current char
		int nlen = 0; // length of compressed array

		for (int i = 1; i < chars.size(); i++) {
			// if previous char different from current, write compressed array
			if (chars[i] != chars[i - 1]) {
				chars[nlen++] = chars[i - 1]; // write char
				if (count > 1) { // write number
					std::string tmp = std::to_string(count);
					for (char c : tmp) {
						chars[nlen++] = c;
					}
				}
				count = 1; // reset count
			}
			// else, continue counting
			else {
				count++;
			}
		}

		// write last char
		chars[nlen++] = chars.back();
		if (count > 1) {
			std::string tmp = std::to_string(count);
			for (char c : tmp) {
				chars[nlen++] = c;
			}
		}

		return nlen;
	}
};

/**
 * Test Cases
 */
int main() {
	Solution s;

	// test case 1
	std::vector<char> chars = {'a','a','b','b','c','c','c'};
	std::cout << "chars: [";
	for (int i=0; i<chars.size() ; i++) std::cout << chars[i] << ",";
	std::cout << "\b]" << std::endl;
	int nlen = s.compress(chars);
	std::cout << "compressed chars: [";
	for (int i = 0; i < nlen; i++) std::cout << chars[i] << ",";
	std::cout << "\b]" << std::endl;

	// test case 2
	chars = {'a'};
	std::cout << "chars: [";
	for (int i = 0; i < chars.size(); i++) std::cout << chars[i] << ",";
	std::cout << "\b]" << std::endl;
	nlen = s.compress(chars);
	std::cout << "compressed chars: [";
	for (int i = 0; i < nlen; i++) std::cout << chars[i] << ",";
	std::cout << "\b]" << std::endl;

	// test case 3
	chars = {'a','b','b','b','b','b','b','b','b','b','b','b','b'};
	std::cout << "chars: [";
	for (int i = 0; i < chars.size(); i++) std::cout << chars[i] << ",";
	std::cout << "\b]" << std::endl;
	nlen = s.compress(chars);
	std::cout << "compressed chars: [";
	for (int i = 0; i < nlen; i++) std::cout << chars[i] << ",";
	std::cout << "\b]" << std::endl;

	return 0;
}