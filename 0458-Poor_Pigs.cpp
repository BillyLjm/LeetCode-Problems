/*******************************************************************************
 * 0458-Poor_Pigs.cpp
 * Billy.Ljm
 * 29 October 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/poor-pigs/
 *
 * There are buckets buckets of liquid, where exactly one of the buckets is
 * poisonous. To figure out which one is poisonous, you feed some number of
 * (poor) pigs the liquid to see whether they will die or not. Unfortunately,
 * you only have minutesToTest minutes to determine which bucket is poisonous.
 *
 * You can feed the pigs according to these steps:
 * 1. Choose some live pigs to feed.
 * 2. For each pig, choose which buckets to feed it. The pig will consume all
 *    the chosen buckets simultaneously and will take no time. Each pig can feed
 *    from any number of buckets, and each bucket can be fed from by any number
 *    of pigs.
 * 3. Wait for minutesToDie minutes. You may not feed any other pigs during this
 *    time.
 * 4. After minutesToDie minutes have passed, any pigs that have been fed the
 *    poisonous bucket will die, and all others will survive.
 * 6. Repeat this process until you run out of time.
 *
 * Given buckets, minutesToDie, and minutesToTest, return the minimum number of
 * pigs needed to figure out which bucket is poisonous within the allotted time.
 *
 * ===========
 * My Approach
 * ===========
 * The optimal strategy is to arrange the buckets into a matrix (or tensor).
 * At each timestep, one pig will feed on one of the rows, another will feed on
 * one of the columns, and so on. So, it will be a numpigs-dimensional tensor
 * with minutesToTest/minutesToDie rows in each dimension. When a pig dies, it
 * identifies a specific row which contains the poison. And in the end, when all
 * the pigs die, they would collectively identify the specific poisonous element.
 * This strategy works if (minutesToTest/minutesToDie)^n >= buckets.
 *
 * Additionally, we can add one more row to each dimension of the tensor, for
 * when the pigs don't die by the end. Also, look out for floating point errors.
 * 
 * This has a time complexity of O(1) and space complexity of O(1).
 ******************************************************************************/

#include <iostream>
#include <vector>
#include <cmath>

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
class Solution {
public:
	int poorPigs(int buckets, int minutesToDie, int minutesToTest) {
		return ceil(log(buckets) / (log(minutesToTest / minutesToDie + 1)) - 1e-6);
	}
};

/**
 * Test cases
 */
int main(void) {
	Solution sol;
	int buckets, minutesToDie, minutesToTest;

	// test case 1
	buckets = 4;
	minutesToDie = 15;
	minutesToTest = 15;
	std::cout << "poorPigs(" << buckets << "," << minutesToDie << "," << minutesToTest << ") = ";
	std::cout << sol.poorPigs(buckets, minutesToDie, minutesToTest) << std::endl;

	// test case 2
	buckets = 4;
	minutesToDie = 15;
	minutesToTest = 30;
	std::cout << "poorPigs(" << buckets << "," << minutesToDie << "," << minutesToTest << ") = ";
	std::cout << sol.poorPigs(buckets, minutesToDie, minutesToTest) << std::endl;

	return 0;
}