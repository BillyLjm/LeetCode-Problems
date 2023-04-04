/*******************************************************************************
 * 2405-Optimal_Partition_of_String.cpp
 * Billy.Ljm
 * 04 Apr 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/optimal-partition-of-string/
 * Given a string s, partition the string into one or more substrings such that
 * the characters in each substring are unique. That is, no letter appears in a
 * single substring more than once.
 *
 * Return the minimum number of substrings in such a partition.
 *
 * ===========
 * My Approach
 * ===========
 * The optimal approach is the greedy approach: if a character is not already in
 * the current substring, force it into the substring; otherwise, a new
 * substring/partition has to be created.
 *
 * It has a time complexity of O(n) and a space complexity of O(1), where n is
 * the length of the string.
 ******************************************************************************/

#include <iostream>
#include <string>
#include <vector>

class Solution {
public:
	/**
	 * Finds minimum number of partitions in a string to ensure each substring
	 * has no repeating characters
	 *
	 * @param s string to partition
	 *
	 * @return minimum number of partitions
	 */
	int partitionString(std::string s) {
		std::vector<int> seen(26, -1); // seen[0] = index of last seen 'a'
		int hash = 0; // hash of current char; 'a' to 0, 'b' to 1, etc.
		int currindex = 0; // starting index of current partition
		int numpartition = 1; // number of partitions

		for (int i = 0; i < s.size(); i++) {
			hash = int(s[i]) - 97;
			if (seen[hash] >= currindex) { // new partition to be created
				currindex = i;
				numpartition++;
			}
			seen[hash] = i;
		}

		return numpartition;
	}
};

/**
 * Test cases
 */
int main(void) {
	Solution sol;
	std::string s;

	// test case 1
	s = "abacaba";
	std::cout << "partitionString(" << s << ") = " <<
		sol.partitionString(s) << std::endl;

	// test case 2
	s = "ssssss";
	std::cout << "partitionString(" << s << ") = " <<
		sol.partitionString(s) << std::endl;

	return 0;
}