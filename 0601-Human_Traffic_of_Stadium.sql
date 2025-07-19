/*******************************************************************************
 * 0601-Human_Traffic_of_Stadium.sql
 * Billy.Ljm
 * 19 July 2025
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/human-traffic-of-stadium/
 *
 * Table: Stadium
 * +---------------+---------+
 * | Column Name   | Type    |
 * +---------------+---------+
 * | id            | int     |
 * | visit_date    | date    |
 * | people        | int     |
 * +---------------+---------+
 * visit_date is the column with unique values for this table.
 * Each row of this table contains the visit date and visit id to the stadium
 * with the number of people during the visit.
 * As the id increases, the date increases as well.
 *
 * Write a solution to display the records with three or more rows with
 * consecutive id's, and the number of people is greater than or equal to 100
 * for each.
 *
 * Return the result table ordered by visit_date in ascending order.
 *
 * ===========
 * My Approach
 * ===========
 * We filter the days with >100 visitors, then use the gap & island method to 
 * group consecutive days together. Then we simply have to filter the groups
 * with more than 3 days in each.
 ******************************************************************************/

WITH Stadium_100 AS (
    SELECT
        id, visit_date, people,
        id-ROW_NUMBER() OVER (ORDER BY id) AS groupp
    FROM Stadium
    WHERE people >= 100
)

SELECT id, visit_date, people
FROM Stadium_100
WHERE groupp in (
    SELECT groupp
    FROM Stadium_100
    GROUP BY groupp
    HAVING COUNT(*) > 3
)