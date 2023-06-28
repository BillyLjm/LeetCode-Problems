/*******************************************************************************
 * 1514-Path_with_Maximum_Probability.java
 * Billy.Ljm
 * 28 June 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/path-with-maximum-probability/
 *
 * You are given an undirected weighted graph of n nodes (0-indexed),
 * represented by an edge list where edges[i] = [a, b] is an undirected edge
 * connecting the nodes a and b with a probability of success of traversing that
 * edge succProb[i].
 *
 * Given two nodes start and end, find the path with the maximum probability of
 * success to go from start to end and return its success probability.
 *
 * If there is no path from start to end, return 0. Your answer will be accepted
 * if it differs from the correct answer by at most 1e-5.
 *
 * ===========
 * My Approach
 * ===========
 * We'll use Dijkstra's algorithm, calculating the probability from the start
 * node to every other node, in decreasing order of probability. We'll use a
 * priority queue to select the highest probability node, and a hashset to
 * remember the visited nodes.
 *
 * This would have a time complexity of O(e + n log n) and space complexity of
 * O(e + n), where e and n are the number of edges and nodes respectively.
 ******************************************************************************/

import java.util.Arrays;
import java.util.PriorityQueue;
import java.util.Set;
import java.util.HashSet;
import java.util.Map;
import java.util.HashMap;
import java.util.List;
import java.util.ArrayList;

class Solution {
	/**
	 * Finds the path of maximum probability from start to end
	 * @param n number of nodes
	 * @param edges list of undirected edges as [from, to]
	 * @param succProb success probability of each undirected edge
	 * @param start node to start at
	 * @param end node to end at
	 * @return maximum probability of success of travelling from start to end
	 */
	public double maxProbability(int n, int[][] edges, double[] succProb,
								 int start, int end) {
		// create adjacency matrix
		Map<Integer, List<double[]>> adj = new HashMap<>(n);
		for (int i = 0; i < edges.length; i++) {
			adj.putIfAbsent(edges[i][0], new ArrayList<>());
			adj.putIfAbsent(edges[i][1], new ArrayList<>());
			adj.get(edges[i][0]).add(new double[] {edges[i][1], succProb[i]});
			adj.get(edges[i][1]).add(new double[] {edges[i][0], succProb[i]});
		}

		// create priority queue and hashset
		Set<Integer> visited = new HashSet<>();
		PriorityQueue<double[]> pq = new PriorityQueue<>((a, b) -> {
			return Double.compare(b[1], a[1]);
		});
		pq.offer(new double[] {start, 1.0});

		// explore nodes in decreasing order of probability
		while (!pq.isEmpty()) {
			// get node with highest probability
			double[] ele = pq.poll();
			int node = (int) ele[0];
			double prob = ele[1];
			// ignore visited nodes
			if (visited.contains(node)) continue;
			// if end node reached, return
			else if (node == end) return prob;
			// else add all neighbours
			else {
				visited.add(node);
				if (adj.get(node) == null) continue;
				for (double[] neighbour : adj.get(node)) {
					if (!visited.contains((int) neighbour[0])) {
						pq.offer(new double[] {neighbour[0],
								prob * neighbour[1]});
					}
				}
			}
		}

		// no path found
		return 0.0;
	}
}

class Test {
	/**
	 * Test cases
	 */
	public static void main(String[] args) {
		Solution sol = new Solution();
		int[][] edges;
		double[] succProb;
		int n, start, end;

		// test case 1
		edges = new int[][] {{0,1},{1,2},{0,2}};
		succProb = new double[] {0.5,0.5,0.2};
		n = 3;
		start = 0;
		end = 2;
		System.out.println("maxProbability(" + n + ", "
				+ Arrays.deepToString(edges) + ", " + Arrays.toString(succProb)
				+ ", " + start + ", " + end + ") = "
				+ sol.maxProbability(n, edges, succProb, start, end));

		// test case 2
		edges = new int[][] {{0,1},{1,2},{0,2}};
		succProb = new double[] {0.5,0.5,0.3};
		n = 3;
		start = 0;
		end = 2;
		System.out.println("maxProbability(" + n + ", "
				+ Arrays.deepToString(edges) + ", " + Arrays.toString(succProb)
				+ ", " + start + ", " + end + ") = "
				+ sol.maxProbability(n, edges, succProb, start, end));

		// test case 3
		edges = new int[][] {{0,1}};
		succProb = new double[] {0.5};
		n = 3;
		start = 0;
		end = 2;
		System.out.println("maxProbability(" + n + ", "
				+ Arrays.deepToString(edges) + ", " + Arrays.toString(succProb)
				+ ", " + start + ", " + end + ") = "
				+ sol.maxProbability(n, edges, succProb, start, end));
	}
}