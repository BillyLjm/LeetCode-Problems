/*******************************************************************************
 * 0208-Implement_Trie_Prefix_Tree.cpp
 * Billy.Ljm
 * 17 Mar 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/implement-trie-prefix-tree/
 * A trie (pronounced as "try") or prefix tree is a tree data structure used to
 * efficiently store and retrieve keys in a dataset of strings. There are
 * various applications of this data structure, such as autocomplete and
 * spellchecker.
 *
 * Implement the Trie class:
 * - Trie() Initializes the trie object.
 * - void insert(String word) Inserts the string word into the trie.
 * - boolean search(String word) Returns true if the string word is in the trie
 *   (i.e., was inserted before), and false otherwise.
 * - boolean startsWith(String prefix) Returns true if there is a previously
 *   inserted string word that has the prefix prefix, and false otherwise.
 *
 * ===========
 * My Approach
 * ===========
 * We just have to implement the Trie structure. The children will be a map from
 * a character to another node. I chose a map because it is empirically observed
 * to improve runtime and space complexity over unordered_map. I presume it is
 * because the nodes have a relatively small range from 'a' to 'z'.
 ******************************************************************************/

#include <iostream>
#include <map>
#include <string>

/**
 * n-ary tree node
 */
struct node {
	std::map<char, node*> children; // children of node
	bool end; // true if node is end of word, false otherwise
	node() : end(false) {} // constructor
};

/**
 * Trie/Prefix Tree
 */
class Trie {
public:
	node* root; // root of prefix tree

	/**
	 * Trie/Prefix tree constructor
	 */
	Trie() {
		root = new node;
	}

	/**
	 * Inserts a word into the trie
	 *
	 * @param word word to insert
	 */
	void insert(std::string word) {
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
	 * Searches of a word in the trie
	 *
	 * @param word word to search for
	 *
	 * @return true if word is found in trie, false otherwise
	 */
	bool search(std::string word) {
		node* crawler = root;
		for (char c : word) {
			if (crawler->children.count(c) == 0) {
				return false;
			}
			else {
				crawler = crawler->children[c];
			}
		}
		return crawler->end;
	}

	/**
	 * Searches of a prefix in the trie
	 *
	 * @param prefix prefix to search for
	 *
	 * @return true if prefix is found in trie, false otherwise
	 */
	bool startsWith(std::string prefix) {
		node* crawler = root;
		for (char c : prefix) {
			if (crawler->children.count(c) == 0) {
				return false;
			}
			else {
				crawler = crawler->children[c];
			}
		}
		return true;
	}

	/**
	 * deletes the trie
	 */
	void deleteTrie() {
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
};

/**
 * Test cases
 */
int main(void) {
	// test case 1
	Trie trie = Trie();
	trie.insert("apple");
	std::cout << std::boolalpha << trie.search("apple") << std::endl;   // return True
	std::cout << std::boolalpha << trie.search("app") << std::endl;	 // return False
	std::cout << std::boolalpha << trie.startsWith("app") << std::endl; // return True
	trie.insert("app");
	std::cout << std::boolalpha << trie.search("app") << std::endl;	 // return True
	trie.deleteTrie();

	return 0;
}