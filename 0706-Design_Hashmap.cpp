/*******************************************************************************
 * 0706-Design_Hashmap.cpp
 * Billy.Ljm
 * 04 October 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/design-hashmap/
 *
 * Design a HashMap without using any built-in hash table libraries.
 *
 * Implement the MyHashMap class:
 * - MyHashMap() initializes the object with an empty map.
 * - void put(int key, int value) inserts a (key, value) pair into the HashMap.
 *   If the key already exists in the map, update the corresponding value.
 * - int get(int key) returns the value to which the specified key is mapped,
 *   or -1 if this map contains no mapping for the key.
 * - void remove(key) removes the key and its corresponding value if the map
 *   contains the mapping for the key.
 *
 * ===========
 * My Approach
 * ===========
 * We'll use the trivial identity hash function, and just store the values in
 * a vector. Since the values are guaranteed to be >= 0, we can use -1 as a
 * placeholder for empty keys.
 *
 * This has a time complexity of O(1) for all methods, and a space complexity of
 * O(1) since the maximum space is always used.
 ******************************************************************************/

#include <iostream>
#include <vector>
#include <map>

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
class MyHashMap {
public:
	vector<int> hash;

	MyHashMap() {
		hash = vector<int>(1000001, -1);
	}

	void put(int key, int value) {
		hash[key] = value;
	}

	int get(int key) {
		return hash[key];
	}

	void remove(int key) {
		hash[key] = -1;
	}
};

/**
 * Test cases
 */
int main(void) {
	// test case 1
	MyHashMap myHashMap = MyHashMap();
	myHashMap.put(1, 1); // The map is now [[1,1]]
	myHashMap.put(2, 2); // The map is now [[1,1], [2,2]]
	std::cout << myHashMap.get(1) << endl;    // return 1, The map is now [[1,1], [2,2]]
	std::cout << myHashMap.get(3) << endl;    // return -1 (i.e., not found), The map is now [[1,1], [2,2]]
	myHashMap.put(2, 1); // The map is now [[1,1], [2,1]] (i.e., update the existing value)
	std::cout << myHashMap.get(2) << endl;    // return 1, The map is now [[1,1], [2,1]]
	myHashMap.remove(2); // remove the mapping for 2, The map is now [[1,1]]
	std::cout << myHashMap.get(2) << endl;    // return -1 (i.e., not found), The map is now [[1,1]]

	return 0;
}