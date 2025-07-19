/*******************************************************************************
 * 0175-Combine_Two_Tables.sql
 * Billy.Ljm
 * 19 July 2025
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/combine-two-tables/
 *
 * Table: Person
 * +-------------+---------+
 * | Column Name | Type    |
 * +-------------+---------+
 * | PersonId    | int     |
 * | lastName    | varchar |
 * | firstName   | varchar |
 * +-------------+---------+
 * PersonId is the primary key (column with unique values) for this table.
 * This table contains information about the ID of some Persons and their first
 * and last names.
 *
 *
 * Table: Address
 * +-------------+---------+
 * | Column Name | Type    |
 * +-------------+---------+
 * | AddressId   | int     |
 * | PersonId    | int     |
 * | city        | varchar |
 * | state       | varchar |
 * +-------------+---------+
 * AddressId is the primary key (column with unique values) for this table.
 * Each row of this table contains information about the city and state of one
 * Person with ID = PersonId.
 *
 *
 * Write a solution to report the first name, last name, city, and state of each
 * Person in the Person table. If the Address of a PersonId is not present in the
 * Address table, report null instead.
 *
 * Return the result table in any order.
 *
 * ===========
 * My Approach
 * ===========
 * Simply left join the Address table to the Person table and select the desired
 * columns.
 ******************************************************************************/

SELECT Person.firstname, Person.lastname, Address.city, Address.state
FROM Person
LEFT JOIN Address
ON Person.personId = Address.personId