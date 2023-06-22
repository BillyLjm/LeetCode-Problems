/*******************************************************************************
 * 0714-Best_Time_to_Buy_and_Sell_Stock_with_Transaction_Fee.java
 * Billy.Ljm
 * 22 June 2023
 *
 * =======
 * Problem
 * =======
 * https://leetcode.com/problems/best-time-to-buy-and-sell-stock-with-transaction-fee/
 *
 * You are given an array prices where prices[i] is the price of a given stock
 * on the ith day, and an integer fee representing a transaction fee.
 *
 * Find the maximum profit you can achieve. You may complete as many
 * transactions as you like, but you need to pay the transaction fee for each
 * transaction.
 *
 * Note: You may not engage in multiple transactions simultaneously (i.e., you
 * must sell the stock before you buy again).
 *
 * ===========
 * My Approach
 * ===========
 * Since there is only one of the stock, on each day we are either holding the
 * stock or not. Thus, we can simulate both possibilities on each day, and
 * take every chunk of profit we can get as we step through each day.
 *
 * This would have a time complexity of O(n) and space complexity of O(1), where
 * n is the number of days.
 ******************************************************************************/

import java.util.Arrays;

class Solution {
	/**
	 * Finds the maximum profit from trading a stock with a given time-series of
	 * prices and transaction fees
	 * @param prices price of the stock on each day
	 * @param fee transaction fee when selling the stock
	 * @return maximum profit from trading the stock
	 */
	public int maxProfit(int[] prices, int fee) {
		// day 0
		int holdProfit = -prices[0], sellProfit = 0;

		// simulate each day
		int tmp;
		for (int i = 0; i < prices.length; i++) {
			tmp = Math.max(holdProfit, sellProfit - prices[i]); // buy/hold the stock
			sellProfit = Math.max(sellProfit, holdProfit + prices[i] - fee); // sell the stock
			holdProfit = tmp;
		}

		return sellProfit;
	}
}

class Test {
	/**
	 * Test cases
	 */
	public static void main(String[] args) {
		Solution sol = new Solution();
		int[] prices;
		int fee;

		// test case 1
		prices = new int[] {1,3,2,8,4,9};
		fee = 2;
		System.out.println("maxProfit(" + Arrays.toString(prices) + ", " + fee
				+ ") = " + sol.maxProfit(prices, fee));

		// test case 2
		prices = new int[] {1,3,7,5,10,3};
		fee = 3;
		System.out.println("maxProfit(" + Arrays.toString(prices) + ", " + fee
				+ ") = " + sol.maxProfit(prices, fee));
	}
}