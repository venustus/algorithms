/*
 * animal.h
 *
 *  Created on: Jun 8, 2013
 *      Author: venkat
 */


#include <string>

using namespace std;

#ifndef ANIMAL_H_
#define ANIMAL_H_

class Animal
{
	string name;

public:
	Animal(string name);

	string getName();
};


class Dog: public Animal
{
	int weight;

public:
	Dog(string name, int weight);

	int getWeight();
};

class Cat: public Animal
{
	int cutenessIndex;

public:
	Cat(string name, int cutenessIndex);

	int getCutenessIndex();
};

#endif /* ANIMAL_H_ */
