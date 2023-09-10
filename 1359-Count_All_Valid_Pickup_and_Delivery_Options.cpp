/*******************************************************************************
 * 1359-Count_All_Valid_Pickup_and_Delivery_Options.cpp
 * Billy.Ljm
 * 10 September 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/count-all-valid-pickup-and-delivery-options/
 *
 * Given n orders, each order consist in pickup and delivery services. 
 *
 * Count all valid pickup/delivery possible sequences such that delivery(i) is
 & always after of pickup(i). 
 *
 * Since the answer may be too large, return it modulo 10^9 + 7.
 *
 * ===========
 * My Approach
 * ===========
 * For each additional order, we will have to schedule an additional pickup and
 * an additional delivery among the 2*k other pickup/delivery. We can choose to
 * slot the (k+1)-th pickup at index i, and the (k+1)-th delivery at any of the 
 * (2k + 1 - i) later slots. Thus, there are \sum_{i=0}^{2k+1} (2k + 1 - i) =
 * (k + 1)(2k + 1) ways to schedule the (k+1)-th order. To find the number of
 * ways to schedule all n orders, we have to multiply the number of ways across
 * all orders as \prod_{k=0}^{n} (k + 1)(2k + 1).
 *
 * This has a time complexity of O(n), and a space complexity of O(1), where
 * n is the number of orders.
 ******************************************************************************/

#include <iostream>
#include <vector>

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
private:
	int modval_ = 1000000007;

public:
	int countOrders(int n) {
		long out = 1;
		for (int i = 0; i < n; i++) {
			out = (out * (i + 1) * (2 * i + 1)) % modval_;
		}
		return out;
	}
};

/**
 * Test cases
 */
int main(void) {
	Solution sol;
	int n;

	// test case 1
	n = 1;
	std::cout << "countOrders(" << n << ") = ";
	std::cout << sol.countOrders(n) << std::endl;

	// test case 2
	n = 2;
	std::cout << "countOrders(" << n << ") = ";
	std::cout << sol.countOrders(n) << std::endl;

	// test case 3
	n = 3;
	std::cout << "countOrders(" << n << ") = ";
	std::cout << sol.countOrders(n) << std::endl;

	return 0;
}