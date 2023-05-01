/*******************************************************************************
 * 1491-Average_Salary_Excluding_the_Minimum_and_Maximum_Salary.cpp
 * Billy.Ljm
 * 01 May 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/average-salary-excluding-the-minimum-and-maximum-salary/
 * You are given an array of unique integers salary where salary[i] is the
 * salary of the ith employee.
 *
 * Return the average salary of employees excluding the minimum and maximum
 * salary. Answers within 10-5 of the actual answer will be accepted.
 *
 * ===========
 * My Approach
 * ===========
 * We can loop through the array, remembering the min, max and sum of all the
 * salaries. Then, we just have to calculate the desired output.
 *
 * This has a time complexity of O(n) and space complexity of O(1), where n is
 * the length of the array.
 ******************************************************************************/

#include <iostream>
#include <vector>

/**
 * Solution
 */
class Solution {
public:
	/**
	 * Returns the average of an array of salary, excluding the min and max
	 *
	 * @param salary array of to average over
	 *
	 * @return average of salary excluding min and max
	 */
	double average(std::vector<int>& salary) {
		int min = salary[0];
		int max, sum = 0;

		// iterate through array
		for (int sal : salary) {
			min = std::min(min, sal);
			max = std::max(max, sal);
			sum = sum + sal;
		}

		// caclulate average w/o min and max
		return double(sum - min - max) / (salary.size() - 2);
	}
};

/**
 * << operator for vectors
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
	std::vector<int> salary;

	// test case 1
	salary = { 4000, 3000, 1000, 2000 };
	std::cout << "average(" << salary << ") = " << sol.average(salary) << std::endl;

	// test case 2
	salary = { 1000, 2000, 3000 };
	std::cout << "average(" << salary << ") = " << sol.average(salary) << std::endl;

	// test case 2
	salary = { 48000,59000,99000,13000,78000,45000,31000,17000,39000,37000,93000,77000,33000,28000,4000,54000,67000,6000,1000,11000 };
	std::cout << "average(" << salary << ") = " << sol.average(salary) << std::endl;

	return 0;
}