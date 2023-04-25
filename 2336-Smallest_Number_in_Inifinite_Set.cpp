/*******************************************************************************
 * 2336-Smallest_Number_in_Inifinite_Set.cpp
 * Billy.Ljm
 * 25 Apr 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/smallest-number-in-infinite-set/
 * You have a set which contains all positive integers [1, 2, 3, 4, 5, ...].
 *
 * Implement the SmallestInfiniteSet class:
 * - `SmallestInfiniteSet()` Initializes the SmallestInfiniteSet object to
 *    contain all positive integers.
 * - `int popSmallest()` Removes and returns the smallest integer contained in
 *    the infinite set.
 * - `void addBack(int num)` Adds a positive integer num back into the infinite
 *    set, if it is not already in the infinite set.
 *
 * ===========
 * My Approach
 * ===========
 * We just have to remember the smallest integer that hasn't been popped yet,
 * and the integers that have been added back into the set via an ordered set.
 *
 * `popSmallest` has a time complexity of O(1), `addBack` is O(log n), and the
 * `SmallestInfiniteSet` class itself has a space complexity of O(n), where n is
 * the number of integers added back.
 ******************************************************************************/

#include <iostream>
#include <set>

/**
 * Creates an set of all positive integers, and allows the user to pop the
 * smallest integer from the set, and add integers back into the set.
 */
class SmallestInfiniteSet {
private:
	int smallest;
	std::set<int> added;

public:
	SmallestInfiniteSet() {
		smallest = 1;
		added.clear();
	}

	/**
	 * Pops the smallest integer from the set
	 *
	 * @return the smallest integer from the set
	 */
	int popSmallest() {
		if (added.empty()) {
			return smallest++;
		}
		else {
			int smallestAdded = *added.begin();
			added.erase(added.begin());
			return smallestAdded;
		}
	}

	/**
	 * Add an integer back into the set, if not already in the set
	 *
	 * @param num integer to add back into the set
	 */
	void addBack(int num) {
		if (num < smallest) {
			added.insert(num);
		}
	}
};

/**
 * Test cases
 */
int main(void) {
	SmallestInfiniteSet* obj = new SmallestInfiniteSet();

	// test case 1
	obj->addBack(2);
	std::cout << "addBack(2)" << std::endl;
	std::cout << "popSmallest() = " << obj->popSmallest() << std::endl;
	std::cout << "popSmallest() = " << obj->popSmallest() << std::endl;
	std::cout << "popSmallest() = " << obj->popSmallest() << std::endl;
	obj->addBack(1);
	std::cout << "addBack(1)" << std::endl;
	std::cout << "popSmallest() = " << obj->popSmallest() << std::endl;
	std::cout << "popSmallest() = " << obj->popSmallest() << std::endl;
	std::cout << "popSmallest() = " << obj->popSmallest() << std::endl;

	return 0;
}