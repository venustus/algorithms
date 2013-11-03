
#include <string>

/**
 * TopCoder SRM 558 backup 1 div 1
 * Little Fox Jiro has a rectangular board. On the board there is a row of N unit cells.
 * The cells are numbered 0 through N-1 from the left to the right. Initially, the cells are not colored.
 * Jiro must color each of the cells red, green, or blue.
 *
 * You are given a string desiredColor with N characters. For each i, character i of desiredColor represents the color
 * Jiro must use for cell i. If a character is one of 'R' (as red), 'G' (as green), and 'B' (as blue),
 * it means that Jiro must use that particular color. If a character is '*',
 * Jiro may use any of the three colors for the particular cell.
 *
 * You are also given the ints stampCost and pushCost that describe the cost of the coloring process.
 * The coloring process consists of two phases. In the first phase, Jiro must pick a single stamp he will then
 * use to color all the cells. The length L of the stamp can be any integer between 1 and N, inclusive.
 * A stamp of length L costs L*stampCost.
 *
 * In the second phase, Jiro must repeatedly use the stamp to color the cells. Each use of the stamp works as follows:
 *
 *  1) Jiro picks one of the three colors and pushes the stamp into ink of the chosen color C.
 *  2) Jiro picks a segment of L contiguous cells such that each of them is either uncolored or already has the color C.
 *     The segment must be completely inside the board. That is, the leftmost cell of the segment must be one of the cells 0 through N-L.
 *  3) Jiro pushes the stamp onto the chosen segment of cells. All the cells now have color C.
 * Each use of the stamp costs pushCost.
 * Return the smallest possible total cost of coloring all the cells using the above process.
 */
int findMinimumStampColoringCost(std::string desiredColor, int stampCost, int pushCost);


/**
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
 * You are given a String road containing N elements. For each i, element i of road is the color of part i: 'R' represents red, 'G' green, and 'B' blue. If Ciel can reach part N-1 in the way described above, return the smallest possible total cost of doing so. Otherwise, return -1.
 */
int getMinCostToCrossColorfulRoad(std::string road);