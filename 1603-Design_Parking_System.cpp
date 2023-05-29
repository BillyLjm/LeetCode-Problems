/*******************************************************************************
 * 1603-Design_Parking_System.cpp
 * Billy.Ljm
 * 29 May 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/design-parking-system/
 *
 * Design a parking system for a parking lot. The parking lot has three kinds of
 * parking spaces: big, medium, and small, with a fixed number of slots for each
 * size.
 *
 * Implement the ParkingSystem class:
 * 
 * - `ParkingSystem(int big, int medium, int small)` Initializes object of the
 *   ParkingSystem class. The number of slots for each parking space are given
 *   as part of the constructor.
 * 
 * - `bool addCar(int carType)` Checks whether there is a parking space of 
 *   carType for the car that wants to get into the parking lot. carType can be 
 *   of three kinds: big, medium, or small, which are represented by 1, 2, and 3
 *   respectively. A car can only park in a parking space of its carType. If
 *   there is no space available, return false, else park the car in that size
 *   space and return true.
 *
 * ===========
 * My Approach
 * ===========
 * We just have to remember the number of each type of parking space, and fill
 * them up as cars are parked. I used a vector since the carType will be
 * specified as 1,2,3 and easily used to index a vector.
 *
 * This has a time complexity of O(1) and space complexity of O(1) for all methods.
 ******************************************************************************/

#include <iostream>
#include <vector>

/**
 * Parking system for a lot big, medium, and small parking spaces
 */
class ParkingSystem {
private:
	std::vector<int> slots; // number of [big, med, small] slots left

public:
	/**
	 * Constructs a parking lot, with specified number of each type of space
	 *
	 * @param big number of big parking spaces
	 * @param medium number of medium parking spaces
	 * @param small nubmer of small parking spaces
	 */
	ParkingSystem(int big, int medium, int small) {
		this->slots = { big, medium, small };
	}

	/**
	 * Parks a car into the parking lot
	 *
	 * @param carType {1,2,3} for big, medium, and small cars respectively
	 *
	 * @return true if car successfully parked, false if no suitabel space
	 */
	bool addCar(int carType) {
		// if vacant slots, park and return true
		if (this->slots[carType - 1] > 0) {
			this->slots[carType - 1]--;
			return true;
		}
		// if no vacant slots, return false;
		else {
			return false;
		}
	}
};

 /**
  * Test cases
  */
int main(void) {
	ParkingSystem parkingSystem = ParkingSystem(1, 1, 0);

	// return true because there is 1 available slot for a big car
	std::cout << std::boolalpha << parkingSystem.addCar(1) << std::endl;

	// return true because there is 1 available slot for a medium car
	std::cout << std::boolalpha << parkingSystem.addCar(2) << std::endl;

	// return false because there is no available slot for a small car
	std::cout << std::boolalpha << parkingSystem.addCar(3) << std::endl;

	// return false because there is no available slot for a big car. It is already occupied.
	std::cout << std::boolalpha << parkingSystem.addCar(1) << std::endl; 

	return 0;
}