/*
 * animal.cpp
 *
 *  Created on: Jun 8, 2013
 *      Author: venkat
 */

#include <string>
#include "animal.h"

using namespace std;


Animal::Animal(string n)
{
	name = n;
}

string Animal::getName()
{
	return name;
}


Dog::Dog(string name, int w): Animal(name)
{
	weight = w;
}

int Dog::getWeight()
{
	return weight;
}

Cat::Cat(string name, int cuteIndex): Animal(name)
{
	cutenessIndex = cuteIndex;
}

int Cat::getCutenessIndex()
{
	return cutenessIndex;
}


