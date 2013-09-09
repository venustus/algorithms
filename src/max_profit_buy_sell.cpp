/*
 * max_profit_buy_sell.cpp
 *
 *  Created on: Sep 7, 2013
 *      Author: venkat
 */

#include <limits>
#include <vector>

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

