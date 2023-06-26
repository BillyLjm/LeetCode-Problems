/*******************************************************************************
 * 2462-Total_Cost_to_Hire_K_Workers.java
 * Billy.Ljm
 * 26 June 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/total-cost-to-hire-k-workers/
 *
 * You are given a 0-indexed integer array costs where costs[i] is the cost of
 * hiring the ith worker.
 *
 * You are also given two integers k and candidates. We want to hire exactly k
 * workers according to the following rules:
 * - You will run k sessions and hire exactly one worker in each session.
 * - In each hiring session, choose the worker with the lowest cost from either
 *   the first candidates workers or the last candidates workers. Break the tie
 *   by the smallest index.
 *   >  For example, if costs = [3,2,7,7,1,2] and candidates = 2, then in the
 *      first hiring session, we will choose the 4th worker because they have
 *      the lowest cost [3,2,7,7,1,2].
 *   > In the second hiring session, we will choose 1st worker because they have
 *     the same lowest cost as 4th worker but they have the smallest index
 *     [3,2,7,7,2]. Please note that the indexing may be changed in the process.
 * - If there are fewer than candidates workers remaining, choose the worker
 *   with the lowest cost among them. Break the tie by the smallest index.
 * - A worker can only be chosen once.
 *
 * Return the total cost to hire exactly k workers.
 *
 * ===========
 * My Approach
 * ===========
 * We just have to implement the specified hiring process. We can use a priority
 * queue to easily select the cheapest applicant from the head or tail
 *
 * This would have a time complexity of O((k + n) log n) and space complexity of
 * O(n), where n is the number of candidates per round and k is the number of
 * sessions.
 ******************************************************************************/

import java.util.Arrays;
import java.util.PriorityQueue;

class Solution {
	/**
	 * Finds the lowest cost to higher k workers via the specified hiring process
	 * @param costs cost of hiring each worker
	 * @param k number of workers to hire / number of sessions
	 * @param candidates number of candidates from head/tail per session
	 * @return lowest cost to hire k workers
	 */
	public long totalCost(int[] costs, int k, int candidates) {
		// priority queue to select lowest cost
		PriorityQueue<Integer> head = new PriorityQueue<>();
		PriorityQueue<Integer> tail = new PriorityQueue<>();
		int headID = -1, tailID = costs.length;

		// fill up first session
		for(int i = 0; i < candidates; i++) {
			if (headID < tailID - 1) head.add(costs[++headID]);
			if (tailID > headID + 1) tail.add(costs[--tailID]);
		}

		// select k workers
		long cost = 0L;
		Integer headCost = head.poll(), tailCost = tail.poll();
		for (int i = 0; i < k; i++) {
			// no more workers
			if (tailCost == null && headCost == null) {
				break;
			}
			// no more tail workers
			else if (tailCost == null) {
				cost += headCost;
				headCost = head.poll();
			}
			// no more head workers
			else if (headCost == null) {
				cost += tailCost;
				tailCost = tail.poll();
			}
			// compare head & tail workers
			else if (tailCost == null || headCost <= tailCost) {
				cost += headCost;
				if (headID < tailID - 1) head.add(costs[++headID]);
				headCost = head.poll();
			}
			else {
				cost += tailCost;
				if (tailID > headID + 1) tail.add(costs[--tailID]);
				tailCost = tail.poll();
			}
		}

		return cost;
	}
}

class Test {
	/**
	 * Test cases
	 */
	public static void main(String[] args) {
		Solution sol = new Solution();
		int[] costs;
		int k, candidates;

		// test case 1
		costs = new int[] {17,12,10,2,7,2,11,20,8};
		k = 3;
		candidates = 4;
		System.out.println("totalCost(" + Arrays.toString(costs) + ", " + k + ", "
				+ candidates + ") = " + sol.totalCost(costs, k, candidates));

		// test case 2
		costs = new int[] {1,2,4,1};
		k = 3;
		candidates = 3;
		System.out.println("totalCost(" + Arrays.toString(costs) + ", " + k + ", "
				+ candidates + ") = " + sol.totalCost(costs, k, candidates));
	}
}