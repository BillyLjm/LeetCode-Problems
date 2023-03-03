/*******************************************************************************
 * 0028-Find_The_Index_Of_The_First_Occurence_In_A_String.cpp
 * Billy.Ljm
 * 03 Mar 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/find-the-index-of-the-first-occurrence-in-a-string/
 * Given two strings needle and haystack, return the index of the first
 * occurrence of needle in haystack, or -1 if needle is not part of haystack.
 *
 * ===========
 * My Approach
 * ===========
 * I'll implement the Knuth–Morris–Pratt algorithm (KMP) algorithm. The KMP
 * keeps track of phrases at the end of the checked substring which resemble
 * the starting of the checked substring (i.e. lps). In that way, if there is a
 * mismatch, we immediately know that a phrase matches, and can skip checking it.
 *
 * This allows the crawling through the haystack to never reverse, ensuring a
 * time complexity of O(n), where n is the length of the haystack. The space
 * complexity is O(m), where m is the length of the needle, since we need to
 * store the length of the matched phrases for each substring of the needle.
 *
 * note: we are not ignoring copies of the matched phrases which appear in the
 * middle of the checked string. Since if the the middle phrase is separated by
 * non-matching sections (e.g. ab in ababac, abdabfabac), then there would have
 * been a mismatch before we even reached the middle. And if separated by
 * matching sections (e.g. ab in ababac, abababac), the matching phrase would
 * have been part of an even larger matched phrase (aba).
 ******************************************************************************/

#include <iostream>
#include <string>
#include <vector>

class Solution {
public:
	/**
	 * KMP Algorithm
	 *
	 * @param haystack string to search for needle in
	 * @param needle substring to search in haystack for
	 *
	 * @return index of first occurrence of needle in haystack; -1 if not found
	 */
	int strStr(std::string haystack, std::string needle) {
		int nsize = int(needle.size());
		int hsize = int(haystack.size());
		int len = 0; // length of matched pre/suffix

		// find the lps
		std::vector <int> lps(nsize, 0);
		len = 0;
		for (int i = 1; i < nsize; i++) {
			// if next char matches, lps increments from previous
			if (needle[i] == needle[len]) {
				len++;
				lps[i] = len;
			}
			// else, we still matched the pre/suffix of needle[:len-1], check
			// that until math found or all options exhausted
			else {
				while (needle[i] != needle[len] and len > 0) {
					len = lps[len - 1];
				}
				if (needle[i] == needle[len]) {
					len++;
				}
				lps[i] = len;
			}
		}

		// search for needle in haystack
		len = 0;
		for (int i = 0; i < hsize; i++) {
			// full needle found, return first index
			if (len == nsize) {
				return i - len;
			}
			// another char of the needle found, check for next char
			else if (haystack[i] == needle[len]) {
				len++;
			}
			// else, we still matched the pre/suffix of needle[:len-1], check
			// that until math found or all options exhausted
			else {
				while (haystack[i] != needle[len] and len > 0) {
					len = lps[len - 1];
				}
				// if we matched, increment len; else start over w/ next char
				if (haystack[i] == needle[len]) {
					len++;
				}
			}
		}

		// check one last time for haystack[-1]
		if (len == nsize) { // needle found in last char
			return hsize - len;
		}
		else { // needle not found
			return -1;
		}
	}
};


/**
 * Test cases
 */
int main(void) {
	Solution sol;

	// test case 1
	std::cout << "sad in sadbutsad: " << sol.strStr("sadbutsad", "sad") << std::endl;

	// test case 1
	std::cout << "leeto in leetcode: " << sol.strStr("leetcode", "leeto") << std::endl;

	// test case 3
	std::cout << "pi in mississippi: " << sol.strStr("mississippi", "pi") << std::endl;

	// test case 4
	std::cout << "aabaaac in aabaaabaaac: " << sol.strStr("aabaaabaaac", "aabaaac") << std::endl;
}