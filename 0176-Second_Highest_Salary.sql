/*******************************************************************************
 * 0176-Second_Highest_Salary.sql
 * Billy.Ljm
 * 19 July 2025
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/second-highest-salary/
 *
 * Table: Employee
 * +-------------+------+
 * | Column Name | Type |
 * +-------------+------+
 * | id          | int  |
 * | salary      | int  |
 * +-------------+------+
 * id is the primary key (column with unique values) for this table.
 * Each row of this table contains information about the salary of an employee.
 *  
 * 
 * Write a solution to find the second highest distinct salary from the Employee 
 * table. If there is no second highest salary, return null.
 *
 * ===========
 * My Approach
 * ===========
 * We use MAX since it is faster than sorting (and selecting the 2nd highest 
 * salary afterwards)
 ******************************************************************************/

SELECT MAX(salary) AS SecondHighestSalary
FROM Employee
WHERE salary != (SELECT MAX(salary) FROM Employee)