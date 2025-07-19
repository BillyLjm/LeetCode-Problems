/*******************************************************************************
 * 0185-Department_Top_Three_Salaries.sql
 * Billy.Ljm
 * 19 July 2025
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/department-top-three-salaries/
 *
 * Table: Employee
 * +--------------+---------+
 * | Column Name  | Type    |
 * +--------------+---------+
 * | id           | int     |
 * | name         | varchar |
 * | salary       | int     |
 * | departmentId | int     |
 * +--------------+---------+
 * id is the primary key (column with unique values) for this table.
 * departmentId  is a foreign key (reference column) of the ID from the 
 * Department table. 
 * Each row of this table indicates the ID, name, and salary of an employee. It 
 * also contains the ID of their department.
 * 
 * Table: Department
 * +-------------+---------+
 * | Column Name | Type    |
 * +-------------+---------+
 * | id          | int     |
 * | name        | varchar |
 * +-------------+---------+
 * id is the primary key (column with unique values) for this table.
 * Each row of this table indicates the ID of a department and its name.
 * 
 * A company's executives are interested in seeing who earns the most money in 
 * each of the company's departments. A high earner in a department is an 
 * employee who has a salary in the top three unique salaries for that 
 * department.
 * 
 * Write a solution to find the employees who are high earners in each of the 
 * departments.
 * 
 * Return the result table in any order.
 * 
 * ===========
 * My Approach
 * ===========
 * We use `DENSE RANK` and `PARTITION BY` to pick out the employees with the 
 * highest salaries in each department.
 ******************************************************************************/

SELECT 
    Department.name AS Department, 
    Employee.name AS Employee,
    Employee.salary AS Salary
FROM (
    SELECT *, DENSE_RANK() OVER (
        PARTITION BY departmentId 
        ORDER BY salary DESC
    ) AS rankk
    FROM Employee
) AS Employee
LEFT JOIN Department
ON Employee.departmentID = Department.id
WHERE Employee.rankk <= 3