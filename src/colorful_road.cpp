
#include <limits>
#include "top_coder_tests.h"

/**
 * SRM 596 Div 1
 * There is a one-dimensional road. The road is separated into N consecutive parts.
 * The parts are numbered 0 through N-1, in order. Ciel is going to walk from part 0 to part N-1.
 * Ciel also noticed that each part of the road has a color: either red, green, or blue. Part 0 is red.
 * Ciel is going to perform a sequence of steps. Each step must lead in the positive direction.
 * That is, if her current part is i, the next step will take her to one of the parts i+1 through N-1, inclusive.
 * Her steps can be arbitrarily long. However, longer steps are harder: a step of length j costs j*j energy.
 * Additionally, Ciel wants to step on colors in a specific order: red, green, blue, red, green, blue, ...
 * That is, she starts on the red part 0, makes a step to a green part, from there to a blue part, and so on,
 * always repeating red, green, and blue in a cycle. Note that the final part N-1 also has some color and thus
 * Ciel must reach it in a corresponding step.
 * You are given a String road containing N elements. For each i, element i of road is the color of part i: 'R'
 * represents red, 'G' green, and 'B' blue. If Ciel can reach part N-1 in the way described above,
 * return the smallest possible total cost of doing so. Otherwise, return -1.
 *
 * Approach: Dynamic Programming
 * Algorithm:
 * 1) For any arbitrary road of length i, compute the minimum cost
 *    by adding cost to cross road of length j for all j < i where road[j] is the previous desired character and then
 *    adding the cost for jump from j to i: (i - j)^2.
 * 2) Recurrence: f(i) = min(f(j) + (i - j)^2) for all j < i and road[j] is a compatible previous character of road[i].
 * 3) Base case: f(0) = 0.
 * 4) Compute minimum values bottom up, starting from 1.
 *
 * Time complexity: O(n^2)
 * Space complexity: O(n)
 */
int getMinCostToCrossColorfulRoad(std::string road)
{
    int min[road.size()];
    min[0] = 0;
    for(int i = 1; i < road.size(); i++)
    {
        char charToLookFor = 'R';
        switch(road[i])
        {
            case 'R':
                charToLookFor = 'B';
                break;
            case 'G':
                charToLookFor = 'R';
                break;
            case 'B':
                charToLookFor = 'G';
                break;
        }
        int j = i - 1;
        int localMin = std::numeric_limits<int>::max();
        while(j >= 0)
        {
            if(road[j] == charToLookFor)
            {
                if(min[j] != -1)
                {
                    int newMin = min[j] + (i - j) * (i - j);
                    if(localMin > newMin) localMin = newMin;
                }
            }
            j--;
        }
        if(localMin < std::numeric_limits<int>::max()) min[i] = localMin;
        else min[i] = -1;
    }
    return min[road.size() - 1];
}