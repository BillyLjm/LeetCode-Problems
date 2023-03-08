/*******************************************************************************
 * 0875-Koko_Eating_Bananas.cpp
 * Billy.Ljm
 * 08 Mar 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/koko-eating-bananas/
 * Koko loves to eat bananas. There are n piles of bananas, the ith pile has
 * piles[i] bananas. The guards have gone and will come back in h hours. Koko
 * can decide her bananas-per-hour eating speed of k. Each hour, she chooses
 * some pile of bananas and eats k bananas from that pile. If the pile has less
 * than k bananas, she eats all of them instead and will not eat any more
 * bananas during this hour. Koko likes to eat slowly but still wants to finish
 * eating all the bananas before the guards return. Return the minimum integer k
 * such that she can eat all the bananas within h hours.
 *
 * ===========
 * My Approach
 * ===========
 * For a given eating speed k, we can easily calculate the number of hours taken
 * to eat all the bananas, using \sum_i ceil(piles[i] / k). We can then do a
 * binary search to find the minimum k to eat all the banana within h hours.
 * Note that if two k yield the same number of hours, we must return the lower k.
 *
 * This would have a time complexity of O(piles.size() * log(max(piles) * h)),
 * and a space complexity of O(1).
 ******************************************************************************/

#include <iostream>
#include <vector>

class Solution {
public:
	/**
	 * Find the minimum eating speed to eat all the bananas arranged in
	 * (multiple) piles with a specified time
	 *
	 * @param piles number of bananas in each pile
	 * @param h number of hours to eat all the banana within
	 *
	 * @return minimum eating speed, in bananas per hour
	 */
	int minEatingSpeed(std::vector<int>& piles, int h) {
		// initial binary search range
		int mink, maxk = piles[0], midk, midh;
		long tmp = 0;
		for (int i : piles) {
			if (i > maxk) { // maxk: all piles eaten in one step
				maxk = i;
			}
			tmp += i; // mink: one big pile which must be eaten in h hours
		}
		mink = ceil(double(tmp) / h);

		// binary search loop
		while (mink != maxk) {
			midk = (mink + maxk) / 2;

			// break if infinite loop
			if (midk == mink or midk == maxk) {
				break;
			}

			// check how many hours to eat all piles
			midh = 0;
			for (int i = 0; i < piles.size(); i++) {
				midh += ceil(double(piles[i]) / midk);
			}

			// update binary search range
			if (midh > h) { // k too low
				mink = midk;
			}
			else { // k can be minimised
				maxk = midk;
			}
		}

		// check in mink satisifes the condition
		midh = 0;
		for (int i = 0; i < piles.size(); i++) {
			midh += ceil(double(piles[i]) / mink);
		}

		if (midh <= h) {
			return mink;
		}
		else {
			return maxk;
		}
	}
};

/**
 * Print function for vectors
 */
template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& v) {
	os << "[";
	for (int i = 0; i < v.size(); i++) {
		os << v[i] << ",";
	}
	os << "\b]";
	return os;
}

/**
 * Test cases
 */
int main(void) {
	Solution sol;
	std::vector<int> piles;
	int h;

	// test case 1
	piles = {3, 6, 7, 11};
	h = 8;
	std::cout << piles << ", " << h << ": " << sol.minEatingSpeed(piles, h)
		<< std::endl;

	// test case 2
	piles = { 30, 11, 23, 4, 20 };
	h = 5;
	std::cout << piles << ", " << h << ": " << sol.minEatingSpeed(piles, h)
		<< std::endl;

	// test case 3
	piles = { 30, 11, 23, 4, 20 };
	h = 6;
	std::cout << piles << ", " << h << ": " << sol.minEatingSpeed(piles, h)
		<< std::endl;
}