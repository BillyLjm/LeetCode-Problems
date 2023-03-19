/*******************************************************************************
 * 0211-Design_Add_and_Search_Words_Data_Structure.cpp
 * Billy.Ljm
 * 19 Mar 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/design-add-and-search-words-data-structure/
 * Design a data structure that supports adding new words and finding if a
 * string matches any previously added string. Implement the WordDictionary
 * class:
 *
 * - `WordDictionary()` Initializes the object.
 * - `void addWord(word)` Adds word to the data structure, it can be matched
 *   later.
 * - `bool search(word)` Returns true if there is any string in the data
 *   structure that matches word or false otherwise. word may contain dots '.'
 *   where dots can be matched with any letter.
 *
 * ===========
 * My Approach
 * ===========
 * We'll us a Trie/prefix tree to store the remembered words. When looking up a
 * widlcard, we simply iteratively check all the children of the Trie node.
 *
 * This will have a time complexity of O(n) for adding a word and O(n k) for
 * searching for a word. It will also have a space complexity of O(n k), where n
 * is the length of the word and k is the number of remembered words.
 ******************************************************************************/

#include <iostream>
#include <string>
#include <map>

/**
* n-ary tree node
*/
struct node {
	std::map<char, node*> children; // children of node
	bool end; // true if node is end of word, false otherwise
	node() : end(false) {} // constructor
};

/**
 * word dictionary implemented as Trie/prefix tree
 */
class WordDictionary {
public:
	node* root; // root of prefix tree

	WordDictionary() {
		root = new node;
	}

	/**
	 * Add a word into the WordDictionary
	 *
	 * @param word word to be added
	 */
	void addWord(std::string word) {
		node* crawler = root;
		for (char c : word) {
			if (crawler->children[c] == NULL) {
				crawler->children[c] = new node;
			}
			crawler = crawler->children[c];
		}
		crawler->end = true;
	}

	/**
	 * Search if the word is in the WordDictionary
	 *
	 * @param word word to be searched
	 */
	bool search(std::string word) {
		return recurse(word, 0, root);
	}

	/**
	 * deletes the WordDictionary
	 */
	void deleteDict() {
		deleteNode(root);
	}

private:
	/**
	 * Deletes a node and all its children
	 */
	void deleteNode(node* nodee) {
		for (const auto& child : nodee->children) {
			deleteNode(child.second);
		}
	}

	/**
	 * Recursively search for string w/ wildcard char in prefix tree
	 *
	 * @param word word to search for
	 * @param index index that has been searched up to
	 * @param crawler current node in prefix tree
	 *
	 * @return true if word is found, false otherwise
	 */
	bool recurse(std::string& word, size_t index, node* crawler) {
		if (crawler == nullptr) {
			return false;
		}
		else if (index == word.size()) {
			return crawler->end;
		}
		else if (word[index] == '.') {
			for (const auto& child : crawler->children) {
				if (recurse(word, index + 1, child.second)) {
					return true;
				}
			}
			return false;
		}
		else {
			if (crawler->children[word[index]] == NULL) {
				return false;
			}
			else {
				return recurse(word, index + 1, crawler->children[word[index]]);
			}
		}
	}
};

int main(void) {
	WordDictionary wordDictionary = WordDictionary();
	wordDictionary.addWord("bad");
	wordDictionary.addWord("dad");
	wordDictionary.addWord("mad");
	std::cout << std::boolalpha << wordDictionary.search("pad") << std::endl; // return False
	std::cout << std::boolalpha << wordDictionary.search("bad") << std::endl; // return True
	std::cout << std::boolalpha << wordDictionary.search(".ad") << std::endl; // return True
	std::cout << std::boolalpha << wordDictionary.search("b..") << std::endl; // return True

	return 0;
}