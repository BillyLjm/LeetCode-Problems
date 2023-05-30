/*******************************************************************************
 * 0705-Design_HashSet.cpp
 * Billy.Ljm
 * 30 May 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/design-hashset/
 *
 * Design a HashSet without using any built-in hash table libraries.
 *
 * Implement MyHashSet class:
 * - `void add(key)` Inserts the value key into the HashSet.
 * - `bool contains(key)` Returns whether the value key exists in the HashSet or
 *    not.
 * - `void remove(key)` Removes the value key in the HashSet. If key does not
 *    exist in the HashSet, do nothing.
 *
 * ===========
 * My Approach
 * ===========
 * The keys are stated to be 0 <= key <= 10^6, which is a relatively small range.
 * Thus, we can just create a bool vector of 10^6 size, which will just be 1Mb.
 * And just remember if the key is inserted or not
 *
 * This has a time complexity of O(1) and space complexity of O(1), where n is
 * the number of keys inserted.
 ******************************************************************************/

#include <iostream>
#include <vector>

/**
 * Hash set
 */
class MyHashSet {
private:
	std::vector<bool> hashset; // hashset[i] = true if i is in set

public:
	/**
	 * Instantiates an empty hash set
	 */
	MyHashSet() {
		this->hashset = std::vector<bool>(1e6 + 1, false);
	}

	/**
	 * Adds a key to the hash set
	 *
	 * @param key key to add
	 */
	void add(int key) {
		this->hashset[key] = true;
	}

	/**
	 * Removes a key from the hash set
	 *
	 * @param key key to remove
	 */
	void remove(int key) {
		this->hashset[key] = false;
	}

	/**
	 * Check if hash set contains a specific key
	 *
	 * @param key key to check for
	 *
	 * @return true if key is in hash set, false otherwise
	 */
	bool contains(int key) {
		return this->hashset[key];
	}
};

/**
 * Test cases
 */
int main(void) {
	MyHashSet myHashSet = MyHashSet();
	myHashSet.add(1);      // set = [1]
	myHashSet.add(2);      // set = [1, 2]
	std::cout << std::boolalpha << myHashSet.contains(1) << std::endl; // return True
	std::cout << std::boolalpha << myHashSet.contains(3) << std::endl; // return False, (not found)
	myHashSet.add(2);      // set = [1, 2]
	std::cout << std::boolalpha << myHashSet.contains(2) << std::endl; // return True
	myHashSet.remove(2);   // set = [1]
	std::cout << std::boolalpha << myHashSet.contains(2) << std::endl; // return False, (already removed)

	return 0;
}