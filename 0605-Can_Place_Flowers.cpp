/*******************************************************************************
 * 0605-Can_Place_Flowers.cpp
 * Billy.Ljm
 * 20 Mar 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/can-place-flowers/
 * You have a long flowerbed in which some of the plots are planted, and some
 * are not. However, flowers cannot be planted in adjacent plots. Given an
 * integer array flowerbed containing 0's and 1's, where 0 means empty and 1
 * means not empty, and an integer n, return if n new flowers can be planted in
 * the flowerbed without violating the no-adjacent-flowers rule.
 *
 * ===========
 * My Approach
 * ===========
 * We essentially have to squeeze as many flowers as possible within the
 * pre-existing ones. In code, this involves looking for adjacent 1's, counting
 * the difference in indices, and floor dividing by 2 and minusing 1. We repeat
 * for the entire array to determine the maximum number of flower insertions.
 *
 * This has a time complexity of O(n), where n is the length of the flowerbed,
 * and a space complexity of O(1).
 ******************************************************************************/

#include <iostream>
#include <vector>

class Solution {
public:
	bool canPlaceFlowers(std::vector<int>& flowerbed, int n) {
		int totnum = 0; // total number of insertable flowers
		int count = 1; // 1 for leading flower beds, no left space to leave

		// middle flower beds
		for (int i = 0; i < flowerbed.size(); i++) {
			if (flowerbed[i] == 0) {
				count++;
			}
			else {
				totnum += count > 2 ? (count - 1) / 2 : 0;
				count = 0;
			}
		}

		// trailing flower beds
		count += 1; // no right space to leave
		totnum += count > 2 ? (count - 1) / 2 : 0;

		return (totnum >= n);
	}
};

/**
 * << operator for vectors
 */
template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec) {
	os << "[";
	for (int i = 0; i < vec.size(); i++) {
		os << vec[i] << ",";
	}
	os << "\b]";
	return os;
}

/**
 * Test cases
 */
int main(void) {
	Solution sol;
	std::vector<int> flowerbed;
	int n;

	// test case 1
	flowerbed = { 1, 0, 0, 0, 1 };
	n = 1;
	std::cout << std::boolalpha << "canPlaceFlowers(" << flowerbed << ", " << n
		<< ") = " << sol.canPlaceFlowers(flowerbed, n) << std::endl;

	// test case 2
	flowerbed = { 1,0,0,0,1,0,0 };
	n = 2;
	std::cout << std::boolalpha << "canPlaceFlowers(" << flowerbed << ", " << n
		<< ") = " << sol.canPlaceFlowers(flowerbed, n) << std::endl;
}