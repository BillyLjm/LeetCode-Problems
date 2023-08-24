/*******************************************************************************
 * 0068-Text_Justification.cpp
 * Billy.Ljm
 * 24 August 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/text-justification/
 *
 * Given an array of strings words and a width maxWidth, format the text such
 * that each line has exactly maxWidth characters and is fully (left and right)
 * justified.
 *
 * You should pack your words in a greedy approach; that is, pack as many words
 * as you can in each line. Pad extra spaces ' ' when necessary so that each
 * line has exactly maxWidth characters.
 *
 * Extra spaces between words should be distributed as evenly as possible. If
 * the number of spaces on a line does not divide evenly between words, the
 * empty slots on the left will be assigned more spaces than the slots on the
 * right.
 *
 * For the last line of text, it should be left-justified, and no extra space is
 * inserted between words.
 *
 * ===========
 * My Approach
 * ===========
 * We will first choose as many words as can fit into the current line, with
 * spaces. Then, we calculate the extra white-spaces left and distribute them
 * accordingly between each word. This repeats until all the words have be
 * justified.
 *
 * This has a time complexity of O(n), and a space complexity of O(n), where n
 * is the number of words.
 ******************************************************************************/

#include <iostream>
#include <vector>
#include <string>

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
	vector<string> fullJustify(vector<string>& words, int maxWidth) {
		vector<string> currline, out;
		int currwidth = 0 , nspaces;

		// justify all words
		for (string word : words) {
			// if word overflows, return
			if (word.size() > maxWidth) return vector<string>();
			// append word to current line
			else if (currwidth + word.size() <= maxWidth) {
				currline.push_back(word);
				currwidth = currwidth + word.size() + 1;
			}
			// output single word line
			else if (currline.size() == 1) {
				out.push_back(currline[0]);
				out.back() = out.back() + string(maxWidth - out.back().size(), ' ');
				// append first word of next line
				currline = { word };
				currwidth = word.size() + 1;
			}
			// output current line and create new line
			else {
				// calculate whitespaces
				currwidth--; // remove trailing whitespace
				nspaces = (maxWidth - currwidth) / (currline.size() - 1);
				currwidth = currwidth + nspaces * (currline.size() - 1);
				// create line
				out.push_back("");
				for (int i = 0; i < maxWidth - currwidth; i++) {
					out.back() = out.back() + currline[i];
					out.back() = out.back() + string(nspaces + 2, ' ');
				}
				for (int i = maxWidth - currwidth; i < currline.size(); i++) {
					out.back() = out.back() + currline[i];
					if (i != currline.size() - 1) {
						out.back() = out.back() + string(nspaces + 1, ' ');
					}
				}
				// append first word of next line
				currline = { word };
				currwidth = word.size() + 1;
			}
			
		}

		// last line
		out.push_back("");
		for (int i = 0; i < currline.size(); i++) {
			out.back() = out.back() + currline[i];
			if (i != currline.size() - 1) {
				out.back() = out.back() + ' ';
			}
		}
		out.back() = out.back() + string(maxWidth - out.back().size(), ' ');
		return out;
	}
};

/**
 * Test cases
 */
int main(void) {
	Solution sol;
	vector<string> words;
	int maxWidth;

	// test case 1
	words = { "This","is","an","example","of","text","justification." };
	maxWidth = 16;
	std::cout << "fullJustify(" << words << ", " << maxWidth << ") = " << endl;
	std::cout << "[" << endl;
	for (string s : sol.fullJustify(words, maxWidth)) {
		std::cout << "    " << s << endl;
	}
	std::cout << "]" << endl;

	// test case 2
	words = { "What","must","be","acknowledgment","shall","be" };
	maxWidth = 16;
	std::cout << "fullJustify(" << words << ", " << maxWidth << ") = " << endl;
	std::cout << "[" << endl;
	for (string s : sol.fullJustify(words, maxWidth)) {
		std::cout << "    " << s << endl;
	}
	std::cout << "]" << endl;

	// test case 3
	words = { "Science","is","what","we","understand","well","enough","to",
		"explain","to","a","computer.","Art","is","everything","else","we","do" };
	maxWidth = 20;
	std::cout << "fullJustify(" << words << ", " << maxWidth << ") = " << endl;
	std::cout << "[" << endl;
	for (string s : sol.fullJustify(words, maxWidth)) {
		std::cout << "    " << s << endl;
	}
	std::cout << "]" << endl;

	return 0;
}