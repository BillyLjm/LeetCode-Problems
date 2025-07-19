/*******************************************************************************
 * 0262-Trips_and_Users.sql
 * Billy.Ljm
 * 19 July 2025
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/trips-and-users/
 *
 * Table: Trips
 * +-------------+----------+
 * | Column Name | Type     |
 * +-------------+----------+
 * | id          | int      |
 * | client_id   | int      |
 * | driver_id   | int      |
 * | city_id     | int      |
 * | status      | enum     |
 * | request_at  | varchar  |
 * +-------------+----------+
 * id is the primary key (column with unique values) for this table.
 * The table holds all taxi trips. Each trip has a unique id, while client_id
 * and driver_id are foreign keys to the users_id at the Users table.
 * Status is an ENUM (category) type of ('completed', 'cancelled_by_driver',
 * 'cancelled_by_client').
 *
 * Table: Users
 * +-------------+----------+
 * | Column Name | Type     |
 * +-------------+----------+
 * | users_id    | int      |
 * | banned      | enum     |
 * | role        | enum     |
 * +-------------+----------+
 * users_id is the primary key (column with unique values) for this table.
 * The table holds all users. Each user has a unique users_id, and role is an
 * ENUM type of ('client', 'driver', 'partner').
 * banned is an ENUM (category) type of ('Yes', 'No').
 *
 * The cancellation rate is computed by dividing the number of cancelled (by
 * client or driver) requests with unbanned users by the total number of
 * requests with unbanned users on that day.
 *
 * Write a solution to find the cancellation rate of requests with unbanned
 * users (both client and driver must not be banned) each day between
 * "2013-10-01" and "2013-10-03" with at least one trip. Round Cancellation Rate
 * to two decimal points.
 *
 * ===========
 * My Approach
 * ===========
 * We filter the trips between unbanned users in the subquery, then we group by
 * the day and calculate the average cancellation rate.
 ******************************************************************************/

SELECT
    request_at AS 'Day',
    ROUND(AVG(CASE WHEN status = 'completed' THEN 0 ELSE 1 END), 2) AS 'Cancellation Rate'
FROM (
    SELECT Trips.request_at, Trips.status
    FROM Trips
    LEFT JOIN Users AS Client
    ON Trips.client_id = Client.users_id
    LEFT JOIN Users as Driver
    ON Trips.driver_id = Driver.users_id
    WHERE Client.banned = 'NO'
    AND Driver.banned = 'NO'
    AND Trips.request_at BETWEEN '2013-10-01' and '2013-10-03'
) AS Trips_Unbanned
GROUP BY request_at