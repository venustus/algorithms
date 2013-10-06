/*
 * max_profit_buy_sell.h
 *
 *  Created on: Sep 7, 2013
 *      Author: venkat
 */

#ifndef MAX_PROFIT_BUY_SELL_H_
#define MAX_PROFIT_BUY_SELL_H_

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
 */
int findWhenToBuySellForMaxProfit(std::vector<int>& stockPrices, int& startIndex, int&endIndex);


#endif /* MAX_PROFIT_BUY_SELL_H_ */
