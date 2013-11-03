
#include <string>
#include <vector>
#include <limits>
#include <iostream>
#include "top_coder_tests.h"

/**
 * Approach; Dynamic Programming
 * Algorithm:
 * 1) There can be several stamp lengths possible. To simplify, fix one
 *    stamp length and compute minimum cost to color using that stamp.
 * 2) Loop over all possible stamp lengths and take minimum of all minimums.
 * 3) For a fixed stamp length, we follow dynamic programming approach.
 *    3.1) Consider a string of arbitrary length i.
 *    3.2) The minimum cost to color this string can be obtained
 *         by using minimum cost for coloring smaller sub-strings
 *         and then using it to compute cost for the current string.
 *         Then we can take minimum of all of possible breaks in string of length i
 *         to compute minimum cost for string of length i.
 *    3.3) While computing costs for all possible breaks, we've to ignore breaks
 *         which do not leave enough room for the stamp and also we can stop looking
 *         back once we encounter a different color because we cannot use one stamp
 *         to push two colors.
 *    3.4) In general the recurrence is: f(i) = min(f(j) + pushCost) over all 0 <= j < i
 *         such that i - j <= len and all characters between desiredColor[i - 1] and
 *         desiredColor[j] are the same or matching.
 *
 * Time complexity: O(n^3)
 * Space complexity: O(n)
 */
int findMinimumStampColoringCost(std::string desiredColor, int stampCost, int pushCost)
{
    int n = desiredColor.size();
    int result = std::numeric_limits<int>::max();
    for(int len = 1; len <= n; len++)
    {
        // we use an array of one element larger for storing costs
        int cost[n + 1];
        cost[0] = 0;
        for(int i = 1; i <= n; i++) cost[i] = std::numeric_limits<int>::max();

        for(int i = 1; i <= n; i++)
        {
            // need to compute cost[i] here
            // we are looking at desiredColor[0:i - 1]
            char currentChar = desiredColor[i - 1];
            for(int j = i - 1; j >= 0; j--)
            {
                // number of pushes required to stamp the segment
                int numPushes = (i - j) / len;
                if((i - j) % len != 0) numPushes++;
                if(i -j >= len && cost[j] != std::numeric_limits<int>::max())
                {
                    cost[i] = std::min(cost[i], cost[j] + numPushes * pushCost);
                }
                if(j > 0)
                {
                    char newChar = desiredColor[j - 1];
                    if(currentChar == '*') currentChar = newChar;
                    if(!(currentChar == '*' || newChar == '*' || currentChar == newChar))
                    {
                        break;
                    }
                }
            }
        }

        if(cost[n] != std::numeric_limits<int>::max())
        {
            if(cost[n] + stampCost * len < result)
            {
                result = cost[n] + stampCost * len;
            }
        }
    }
    return result;
}