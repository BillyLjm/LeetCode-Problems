/*******************************************************************************
 * 0373-Find_K_Pairs_with_Smallest_Sum.java
 * Billy.Ljm
 * 27 June 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/find-k-pairs-with-smallest-sums/
 *
 * You are given two integer arrays nums1 and nums2 sorted in ascending order
 * and an integer k.
 *
 * Define a pair (u, v) which consists of one element from the first array and
 * one element from the second array.
 *
 * Return the k pairs (u1, v1), (u2, v2), ..., (uk, vk) with the smallest sums.
 *
 * ===========
 * My Approach
 * ===========
 * Since the arrays are sorted, the pair with the smallest sum will be (u1, v1).
 * The next smallest pair will then be either (u1, v2) or (u2, v1). Similarly,
 * for every subsequent pair, we'll have to increment the index of u and v by 1,
 * checking also that we haven't considered that pair before. To find the next
 * smallest pair efficiently, we will use a priority queue.
 *
 * This would have a time complexity of O(mn * log(mn)) and space complexity of
 * O(mn), where m and n are the lengths of nums1 and nums2 respectively.
 ******************************************************************************/

import java.util.Arrays;
import java.util.List;
import java.util.ArrayList;
import java.util.PriorityQueue;
import java.util.Set;
import java.util.HashSet;

class Solution {
	/**
	 * Finds k pairs of elements in two arrays with the smallest sums
	 * @param nums1 array to pair with nums2
	 * @param nums2 array to pair with nums1
	 * @param k number of pairs to return
	 * @return k pairs with the smallest sums
	 */
	public List<List<Integer>> kSmallestPairs(int[] nums1, int[] nums2, int k) {
		// to not double-count pairs
		Set<String> visited = new HashSet<>();

		// priority queue to select smallest pair
		PriorityQueue<int[]> pq = new PriorityQueue<>((a, b) -> (a[0] - b[0]));
		pq.add(new int[] {nums1[0] + nums2[0], 0, 0}); // first pair
		visited.add(0 + "," + 0); // mark as visited

		// find k smallest pairs
		List<List<Integer>> out = new ArrayList<>();
		while(k-- > 0 && !pq.isEmpty()) {
			int[] curr = pq.poll();
			out.add(Arrays.asList(nums1[curr[1]], nums2[curr[2]]));
			if(curr[1] + 1 < nums1.length &&
					!visited.contains((curr[1] + 1) + "," + (curr[2]))) {
				pq.add(new int[] {nums1[curr[1] + 1] + nums2[curr[2]],
						curr[1] + 1, curr[2]});
				visited.add((curr[1] + 1) + "," + (curr[2]));
			}
			if(curr[2] + 1 < nums2.length &&
					!visited.contains((curr[1]) + "," + (curr[2] + 1))) {
				pq.add(new int[] {nums1[curr[1]] + nums2[curr[2] + 1],
						curr[1], curr[2] + 1});
				visited.add((curr[1]) + "," + (curr[2] + 1));
			}
		}

		return out;
	}
}

class Test {
	/**
	 * Test cases
	 */
	public static void main(String[] args) {
		Solution sol = new Solution();
		int[] nums1, nums2;
		int k;

		// test case 1
		nums1 = new int[] {1,7,11};
		nums2 = new int[] {2,4,6};
		k = 3;
		System.out.println("kSmallestPairs(" + Arrays.toString(nums1) + ", "
				+ Arrays.toString(nums2) + ", " + k + ") = "
				+ sol.kSmallestPairs(nums1, nums2, k));

		// test case 2
		nums1 = new int[] {1,1,2};
		nums2 = new int[] {1,2,3};
		k = 2;
		System.out.println("kSmallestPairs(" + Arrays.toString(nums1) + ", "
				+ Arrays.toString(nums2) + ", " + k + ") = "
				+ sol.kSmallestPairs(nums1, nums2, k));

		// test case 3
		nums1 = new int[] {1,2};
		nums2 = new int[] {3};
		k = 3;
		System.out.println("kSmallestPairs(" + Arrays.toString(nums1) + ", "
				+ Arrays.toString(nums2) + ", " + k + ") = "
				+ sol.kSmallestPairs(nums1, nums2, k));
	}
}