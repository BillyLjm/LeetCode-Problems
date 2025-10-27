"""
0127-Word_Ladder.py
Billy.Ljm
27 October 2025

=======
Problem
=======
https://leetcode.com/problems/word-ladder/

A transformation sequence from word beginWord to word endWord using a dictionary
wordList is a sequence of words beginWord -> s1 -> s2 -> ... -> sk such that:
- Every adjacent pair of words differs by a single letter.
- Every s_i for 1 <= i <= k is in wordList. Note that beginWord does not need to
  be in wordList.
- s_k == endWord

Given two words, beginWord and endWord, and a dictionary wordList, return the
number of words in the shortest transformation sequence from beginWord to
endWord, or 0 if no such sequence exists.

===========
My Approach
===========
We use bidirectional breadth-first search to find the shortest transformation.
At each step, we use sets to quickly compare the overlaps between the wordlist,
begin frontier, and end frontier.

This has a time complexity of O(nL), and a space complexity of O(nL), where n is
the size of wordList and L is the maximum size of each word in wordList.
"""

class Solution(object):
    def ladderLength(self, beginWord, endWord, wordList):
        """
        :type beginWord: str
        :type endWord: str
        :type wordList: List[str]
        :rtype: int
        """
        # init from beginWord & endWord
        wordList = set(wordList)
        beginList = set([beginWord,])
        endList = set([endWord,])
        dist = 2

        # edge case
        if endWord not in wordList:
            return 0

        # breadth-first search
        while len(beginList) != 0:
            # advance one depth
            wordList -= beginList
            beginList = wordList & set([
                word[:i] + c + word[i+1:]
                for word in beginList
                for i in range(len(word))
                for c in 'abcdefghijklmnopqrstuvwxyz'
            ])
            # if transformation found, return
            if len(beginList & endList) > 0:
                return dist
            # else alternate between begin and end frontier
            else:
                beginList, endList = endList, beginList
                dist += 1

        # no path found
        return 0

"""
Test cases
"""
if __name__ == "__main__":
    sol = Solution()

    # test case 1
    beginWord = "hit"
    endWord = "cog"
    wordList = ["hot","dot","dog","lot","log","cog"]
    print(f"ladderLength({beginWord}, {endWord}, {wordList}) = " +
       str(sol.ladderLength(beginWord, endWord, wordList)))

    # test case 2
    beginWord = "hit"
    endWord = "cog"
    wordList = ["hot","dot","dog","lot","log"]
    print(f"ladderLength({beginWord}, {endWord}, {wordList}) = " +
       str(sol.ladderLength(beginWord, endWord, wordList)))