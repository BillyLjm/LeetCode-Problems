/*******************************************************************************
 * 1146-Snapshot_Array.cpp
 * Billy.Ljm
 * 11 June 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/snapshot-array/
 *
 * Implement a SnapshotArray that supports the following interface:
 * - SnapshotArray(int length): initializes an array-like data structure with
 *   the given length. Initially, each element equals 0.
 * - void set(index, val) sets the element at the given index to be equal to val.
 * - int snap() takes a snapshot of the array and returns the snap_id: the total
 *   number of times we called snap() minus 1.
 * - int get(index, snap_id) returns the value at the given index, at the time
 *   we took the snapshot with the given snap_id
 *
 * ===========
 * My Approach
 * ===========
 * Instead of snapshotting the whole array, we'll snapshot only the elements
 * that changed, like git. So for each index, we'll store a pair of integers of
 * the snapshot id and the value. Based on the desired snapshot id, we'll then
 * find the latest value and construct the array accordingly.
 *
 * This has a time complexity of O(log d) and space complexity of O(n * d), 
 * where d is the number of snapshots and n the number of elements.
 ******************************************************************************/

#include <iostream>
#include <vector>

/**
 * Array which the user can take snapshots of and retrieve older values later
 */
class SnapshotArray {
private:
	int snapid; // snapshot id
	std::vector<std::vector<std::pair<int, int>>> arr; // array of {id, value} pairs

public:
	/**
	 * Constructs a snapshot-able array
	 *
	 * @param length length of array
	 */
	SnapshotArray(int length) {
		snapid = 0;
		arr = std::vector<std::vector<std::pair<int, int>>>(length,
			{ std::make_pair(0, 0) });
	}

	/**
	 * Changes the value of the array at the given index
	 *
	 * @param index index to change value at
	 * @param val value to change to
	 */
	void set(int index, int val) {
		if (arr[index].back().first == snapid)  arr[index].back().second = val;
		else arr[index].push_back(std::make_pair(snapid, val));
	}

	/**
	 * Takes a snapshot of the array
	 *
	 * @return id of the snapshot
	 */
	int snap() {
		return snapid++;
	}

	/**
	 * Gets the value of the array at a given index and snapshot
	 *
	 * @param index index to get value of
	 * @param snap_id snapshot to get value at
	 *
	 * @return value of array at index and snapshot
	 */
	int get(int index, int snap_id) {
		int mid;
		int minn = 0;
		int maxx = arr[index].size() - 1;

		// binary search
		while (maxx - minn > 1) {
			mid = (minn + maxx) / 2;
			if (arr[index][mid].first > snap_id) maxx = mid;
			else minn = mid;
		}

		// last two elements
		if (arr[index][maxx].first <= snap_id) return arr[index][maxx].second;
		else return arr[index][minn].second;
	}
};

/**
 * Test cases
 */
int main(void) {

	// test case 1
	SnapshotArray snapshotArr(3); // set the length to be 3
	snapshotArr.set(0, 5);  // Set array[0] = 5
	// Take a snapshot, return snap_id = 0
	std::cout << "snap(): " << snapshotArr.snap() << std::endl;  
	snapshotArr.set(0, 6);
	// Get the value of array[0] with snap_id = 0, return 5
	std::cout << "get(0,0): " << snapshotArr.get(0, 0) << std::endl;

	return 0;
}