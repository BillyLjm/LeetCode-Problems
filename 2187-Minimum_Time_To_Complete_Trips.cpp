/*******************************************************************************
 * 2187-Minimum_Time_To_Complete_Trips.cpp
 * Billy.Ljm
 * 07 Mar 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/minimum-time-to-complete-trips/
 * You are given an array time where time[i] denotes the time taken by the ith
 * bus to complete one trip. Each bus can make multiple trips successively; that
 * is, the next trip can start immediately after completing the current trip.
 * Also, each bus operates independently; that is, the trips of one bus do not
 * influence the trips of any other bus. You are also given an integer
 * totalTrips, which denotes the number of trips all buses should make in total.
 * Return the minimum time required for all buses to complete at least
 * totalTrips trips.
 *
 * ===========
 * My Approach
 * ===========
 * We can do a binary search to find the minimum time. This minimum time would
 * be bounded by 1 and the time taken for any of the bus to do it by itself.
 *
 * The minimum time would also be acheived by constantly sending all buses out
 * on trips. Thus, the number of trips taken at each timestep using this method
 * is simply the sum of int(time/bus speed) for each bus. Thus, we can calculate
 * the number of trips directly, to inform our binary search.
 *
 * The binary search would take O(log(fastest bus * total trips)) time, and the
 * calculation of the trips taken at each timestep would take O(number of buses)
 * time. Thus, the time complexity is O(len(time) * log(max(time) * totalTrips)).
 * And the space complexity is O(1), with just min, max, mid for binary search.
 ******************************************************************************/

#include <iostream>
#include <vector>
#include <algorithm>

class Solution {
public:
	/**
	 * Finds the minimum time to complete a specified number of total trips
	 * with a bus fleet of specified speeds
	 *
	 * @param time speed of each bus in the fleet, as hours per trip
	 * @param totalTrips total number of trips to complete across the fleet
	 *
	 * @return minimum time to complete the required trips
	 */
	long long minimumTime(std::vector<int>& time, int totalTrips) {
		// find fastest bus to define maxtime
		int fastest = time[0];
		for (int i = 0; i < time.size(); i++) {
			if (time[i] < fastest) {
				fastest = time[i];
			}
		}
		long long maxtime = 1LL * totalTrips * fastest;

		// binary search
		long long mintime = 1, midtime, midtrips;
		std::cout << maxtime << std::endl;
		while (maxtime - mintime > 1) {
			midtime = (mintime + maxtime) / 2;

			// check if reached end of loop
			if (midtime == mintime or midtime == maxtime) {
				break;
			}

			// calculate number of trips made
			midtrips = 0;
			for (int i = 0; i < time.size(); i++) {
				midtrips += midtime / time[i];
			}

			// update interval
			if (midtrips >= totalTrips) {
				maxtime = midtime;
			}
			else {
				mintime = midtime;
			}
		}

		// check which interval is correct
		midtrips = 0; // this time used for trips at mintime
		for (int i = 0; i < time.size(); i++) {
			midtrips += mintime / time[i];
		}
		if (midtrips == totalTrips) {
			return mintime;
		}
		else {
			return maxtime;
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
	Solution s;
	std::vector<int> time;
	int totalTrips;

	// test case 1
	time = { 1, 2, 3 };
	totalTrips = 5;
	std::cout << "s.minimumTime(" << time << ", " << totalTrips << ") = " <<
		s.minimumTime(time, totalTrips) << std::endl;

	// test case 2
	time = { 2 };
	totalTrips = 1;
	std::cout << "s.minimumTime(" << time << ", " << totalTrips << ") = " <<
		s.minimumTime(time, totalTrips) << std::endl;

	// test case 3
	time = { 1, 1, 1, 1, 1 };
	totalTrips = 5;
	std::cout << "s.minimumTime(" << time << ", " << totalTrips << ") = " <<
		s.minimumTime(time, totalTrips) << std::endl;

	return 0;
}