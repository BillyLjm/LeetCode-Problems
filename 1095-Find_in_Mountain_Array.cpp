/*******************************************************************************
 * 1095-Find_in_Mountain_Array.cpp
 * Billy.Ljm
 * 12 October 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/find-in-mountain-array/
 *
 * (This problem is an interactive problem.)
 *
 * You may recall that an array arr is a mountain array if and only if:
 * - arr.length >= 3
 * - There exists some i with 0 < i < arr.length - 1 such that:
 *    > arr[0] < arr[1] < ... < arr[i - 1] < arr[i]
 *    > arr[i] > arr[i + 1] > ... > arr[arr.length - 1]
 *
 * Given a mountain array mountainArr, return the minimum index such that
 * mountainArr.get(index) == target. If such an index does not exist, return -1.
 *
 * You cannot access the mountain array directly. You may only access the array
 * using a MountainArray interface:
 * - MountainArray.get(k) returns the element of the array at index k (0-indexed).
 * - MountainArray.length() returns the length of the array.
 *
 * Submissions making more than 100 calls to MountainArray.get will be judged
 * Wrong Answer. Also, any solutions that attempt to circumvent the judge will
 * result in disqualification.
 *
 * ===========
 * My Approach
 * ===========
 * We will use binary search 3 times; first to find the peak of the mountain
 * array, and then to find the target in the two slopes. To find the peak, we
 * have to find the gradient by querying two adjacent elements; and to find the
 * target we just have to query one element as usual. Additionally, we can cache
 * the queries to avoid querying the same index multiple times across the
 * independent binary searches.
 *
 * This has a time complexity of O(log n), and space complexity of O(n), where n
 * is the length of the mountain array.
 ******************************************************************************/

#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>

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
 * MountainArray's API interface
 */
class MountainArray {
private:
	vector<int> array;

public:
	// default constructor
	MountainArray() {
		this->array = vector<int>();
	}

	// constructor for mountain array
	MountainArray(vector<int> vals) {
		srand(time(NULL));
		vector<int> tmp;

		// sort values
		sort(vals.begin(), vals.end());

		// init both slopes
		this->array.push_back(vals[0]);
		tmp.push_back(vals[1]);

		// populate rest of slopes randomly
		for (int i = 2; i < vals.size(); i++) {
			if (rand() % 2 == 0) {
				if (this->array.back() != vals[i]) this->array.push_back(vals[i]);
				else tmp.push_back(vals[i]);
			}
			else {
				if (tmp.back() != vals[i]) tmp.push_back(vals[i]);
				else this->array.push_back(vals[i]);
			}
		}

		// concatenate into mountain
		reverse(tmp.begin(), tmp.end());
		this->array.insert(this->array.end(), tmp.begin(), tmp.end());
	}

	// get element of array
	int get(int index) {
		return this->array[index];
	}

	// get lenght of array
	int length() {
		return array.size();
	}

	// get whole vector (for printing)
	vector<int> vec() {
		return this->array;
	}
};

/**
 * Solution
 */
class Solution {
private:
	vector<int> cache;
	MountainArray* mountainArr;

public:
	// default constructor
	Solution() {
		this->cache = vector<int>();
		this->mountainArr = nullptr;
	}

	// cache get calls
	int getElem(int idx) {
		if (this->cache[idx] < 0) this->cache[idx] = this->mountainArr->get(idx);
		return this->cache[idx];
	}

	// main function
	int findInMountainArray(int target, MountainArray& mountainArr) {
		int lenn = mountainArr.length();
		int start, end, mid; // binary search
		int peak; // index of peak of mountain array

		// fill atrributes
		this->cache = vector<int>(lenn, -1);
		this->mountainArr = &mountainArr;

		// find peak of mountain array
		start = 0;
		end = lenn - 1;
		while (end > start + 1) {
			mid = (end + start) / 2;
			if (getElem(mid + 1) > getElem(mid)) start = mid;
			else end = mid;
		}
		peak = getElem(start) > getElem(end) ? start : end;

		// search slope with smaller indices first
		start = 0;
		end = peak;
		while (end > start + 1) {
			mid = (end + start) / 2;
			if (target > getElem(mid)) start = mid;
			else end = mid;
		}
		if (getElem(start) == target) return start;
		else if (getElem(end) == target) return end;

		// search other slope
		start = peak;
		end = lenn - 1;
		while (end > start + 1) {
			mid = (end + start) / 2;
			if (target > getElem(mid)) end = mid;
			else start = mid;
		}
		if (getElem(start) == target) return start;
		else if (getElem(end) == target) return end;

		// target not found
		return -1;
	}
};

/**
 * Test cases
 */
int main(void) {
	Solution sol;
	int target;
	vector<int> array;
	MountainArray mountainArr;

	// test case 1
	target = 3;
	array = { 1,2,3,4,5,3,1 };
	mountainArr = MountainArray(array);
	std::cout << "findInMountainArray(" << target << "," << mountainArr.vec() << ") = ";
	std::cout << sol.findInMountainArray(target, mountainArr) << std::endl;

	// test case 2
	target = 3;
	array = { 0,1,2,4,2,1 };
	mountainArr = MountainArray(array);
	std::cout << "findInMountainArray(" << target << "," << mountainArr.vec() << ") = ";
	std::cout << sol.findInMountainArray(target, mountainArr) << std::endl;

	return 0;
}