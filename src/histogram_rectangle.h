/*
 * histogram_rectangle.h
 *
 *  Created on: Jul 24, 2013
 *      Author: venkat
 */

#include <vector>
#include <stack>

#ifndef HISTOGRAM_RECTANGLE_H_
#define HISTOGRAM_RECTANGLE_H_

class Histogram
{
	std::vector<int> * heights;
public:
	Histogram(std::vector<int> * heightsArr);
	std::pair<int, int> computeMaxAreaRectangle(int &area);
};


#endif /* HISTOGRAM_RECTANGLE_H_ */
