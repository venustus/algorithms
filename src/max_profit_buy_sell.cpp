/*
 * max_profit_buy_sell.cpp
 *
 *  Created on: Sep 7, 2013
 *      Author: venkat
 */

#include <limits>
#include <vector>


/**
 * Problem:
 * Given a list of projected stock prices, one stock price for each day,
 * find out on which day to buy the stock and on which day to sell, to
 * make maximum profit.
 *
 * Alternative statement:
 * Given an integer array A, find out indexes i and j such that A[i] - A[j]
 * is maximum while i > j.
 *
 * Algorithm:
 * 1) Iterate once through the array.
 * 2) At each iteration, keep a running minimum seen so far.
 * 3) At each iteration, take the difference of the current element and
 *    the minimum stock price seen so far. Keep a running max profit
 *    and if the current profit is greater than max profit, update max profit.
 *    Also update start and end indexes.
 * 4) Return max profit and start and end endexs.
 *
 * Time complexity: O(n)
 * Space complexity: O(1)
 */
int findWhenToBuySellForMaxProfit(std::vector<int>& stockPrices, int& startIndex, int&endIndex)
{
	int minimumSoFar = std::numeric_limits<int>::max();
	int minIndex = 0;
	int maxProfit = -1;
	startIndex = -1, endIndex = -1;
	if(stockPrices.size() < 2)
	{
		return -1;
	}
	if(stockPrices[1] > stockPrices[0])
	{
		minimumSoFar = stockPrices[0];
		minIndex = 0;
		maxProfit = stockPrices[1] - stockPrices[0];
		startIndex = 0; endIndex = 1;
	}
	else
	{
		minimumSoFar = stockPrices[1];
		minIndex = 1;
	}
	for(int i = 2;i < stockPrices.size();i++)
	{
		if(stockPrices[i] - minimumSoFar > maxProfit)
		{
			maxProfit = stockPrices[i] - minimumSoFar;
			startIndex = minIndex;
			endIndex = i;
		}
		if(stockPrices[i] < minimumSoFar)
		{
			minimumSoFar = stockPrices[i];
			minIndex = i;
		}
	}
	return maxProfit;
}

