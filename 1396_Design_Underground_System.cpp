/*******************************************************************************
 * 1396_Design_Underground_System.cpp
 * Billy.Ljm
 * 31 May 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/design-underground-system/
 *
 * An underground railway system is keeping track of customer travel times
 * between different stations. They are using this data to calculate the average
 * time it takes to travel from one station to another.
 *
 * Implement the UndergroundSystem class:
 * 
 * - `void checkIn(int id, string stationName, int t)`
 *    > A customer with a card ID equal to id, checks in at the station
 *      stationName at time t.
 *    > A customer can only be checked into one place at a time.
 * 
 * - `void checkOut(int id, string stationName, int t)`
 *    > A customer with a card ID equal to id, checks out from the station
 *      stationName at time t.
 * 
 * - `double getAverageTime(string startStation, string endStation)`
 *    > Returns the average time it takes to travel from startStation to
 *      endStation.
 *    > The average time is computed from all the previous travelling times from
 *      startStation to endStation that happened directly, meaning a check in at
 *      startStation followed by a check out from endStation.
 *    > The time it takes to travel from startStation to endStation may be
 *      different from the time it takes to travel from endStation to startStation.
 *    > There will be at least one customer that has travelled from startStation
 *      to endStation before getAverageTime is called.
 *
 * You may assume all calls to the checkIn and checkOut methods are consistent.
 * If a customer checks in at time t1 then checks out at time t2, then t1 < t2.
 * All events happen in chronological order.
 *
 * ===========
 * My Approach
 * ===========
 * We'll use two unordered maps; one to remember the active commuters and
 * another to remember completed trips. The first will be indexed by the
 * commuter's id, and the second by the start & stop station.
 *
 * This has a time complexity of O(1) for checking in and checking out, and O(k)
 * for getAverageTime where k is the number of trips made from the start to end
 * station. It has space complexity of O(n), where n is number of trips started.
 ******************************************************************************/

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <utility>
#include <numeric>

using namespace std;

/**
 * System for tracking length of trips taken in an underground metro system
 */
class UndergroundSystem {
private:
	unordered_map<int, pair<string, int>> commuters; // active commuters
	unordered_map<string, unordered_map<string, vector<int>>> trips; // completed trips

public:
	/**
	 * Constructor
	 */
	UndergroundSystem() {
		commuters.clear();
		trips.clear();
	}

	/**
	 * Check a commuter into the underground metro
	 *
	 * @param id unique id of commuter
	 * @param stationName station where the commuter boarded at
	 * @param t time of boarding
	 */
	void checkIn(int id, string stationName, int t) {
		commuters[id] = pair<string, int>(stationName, t);
	}

	/**
	 * Check a commuter out of the underground metro
	 *
	 * @param id unique id of commuter
	 * @param stationName station where the commuter alighted at
	 * @param t time of alighting
	 */
	void checkOut(int id, std::string stationName, int t) {
		pair<string, int> board = commuters[id];
		trips[board.first][stationName].push_back(t - board.second);
		commuters.erase(id);
	}

	/**
	 * Gets the average time of a trip between two specified stations
	 *
	 * @param startStation starting station
	 * @param endStation ending station
	 *
	 * @return average time of trip between the two stations
	 */
	double getAverageTime(std::string startStation, std::string endStation) {\
		return accumulate(trips[startStation][endStation].begin(),
			trips[startStation][endStation].end(), 0.0)
		/ trips[startStation][endStation].size();
	}
};

/**
 * Test cases
 */
int main(void) {
	UndergroundSystem undergroundSystem;

	// test case 1
	std::cout << "-----------\ntest case 1\n-----------" << std::endl;
	undergroundSystem = UndergroundSystem();
	undergroundSystem.checkIn(45, "Leyton", 3);
	undergroundSystem.checkIn(32, "Paradise", 8);
	undergroundSystem.checkIn(27, "Leyton", 10);
	undergroundSystem.checkOut(45, "Waterloo", 15);  // Customer 45 "Leyton" -> "Waterloo" in 15-3 = 12
	undergroundSystem.checkOut(27, "Waterloo", 20);  // Customer 27 "Leyton" -> "Waterloo" in 20-10 = 10
	undergroundSystem.checkOut(32, "Cambridge", 22); // Customer 32 "Paradise" -> "Cambridge" in 22-8 = 14
	// return 14.00000. One trip "Paradise" -> "Cambridge", (14) / 1 = 14
	std::cout << undergroundSystem.getAverageTime("Paradise", "Cambridge") << std::endl;
	// return 11.00000. Two trips "Leyton" -> "Waterloo", (10 + 12) / 2 = 11
	std::cout << undergroundSystem.getAverageTime("Leyton", "Waterloo") << std::endl;   
	undergroundSystem.checkIn(10, "Leyton", 24);
	// return 11.00000
	std::cout << undergroundSystem.getAverageTime("Leyton", "Waterloo") << std::endl;    
	undergroundSystem.checkOut(10, "Waterloo", 38);  // Customer 10 "Leyton" -> "Waterloo" in 38-24 = 14
	// return 12.00000. Three trips "Leyton" -> "Waterloo", (10 + 12 + 14) / 3 = 12
	std::cout << undergroundSystem.getAverageTime("Leyton", "Waterloo") << std::endl;

	// test case 2
	std::cout << "-----------\ntest case 2\n-----------" << std::endl;
	undergroundSystem = UndergroundSystem();
	undergroundSystem.checkIn(10, "Leyton", 3);
	undergroundSystem.checkOut(10, "Paradise", 8); // Customer 10 "Leyton" -> "Paradise" in 8-3 = 5
	// return 5.00000, (5) / 1 = 5
	std::cout << undergroundSystem.getAverageTime("Leyton", "Paradise") << std::endl; 
	undergroundSystem.checkIn(5, "Leyton", 10);
	undergroundSystem.checkOut(5, "Paradise", 16); // Customer 5 "Leyton" -> "Paradise" in 16-10 = 6
	// return 5.50000, (5 + 6) / 2 = 5.5
	std::cout << undergroundSystem.getAverageTime("Leyton", "Paradise") << std::endl; 
	undergroundSystem.checkIn(2, "Leyton", 21);
	undergroundSystem.checkOut(2, "Paradise", 30); // Customer 2 "Leyton" -> "Paradise" in 30-21 = 9
	// return 6.66667, (5 + 6 + 9) / 3 = 6.66667
	std::cout << undergroundSystem.getAverageTime("Leyton", "Paradise") << std::endl; 

	return 0;
}
