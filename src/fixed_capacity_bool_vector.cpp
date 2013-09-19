/*
 * fixed_capacity_bool_vector.cpp
 *
 *  Created on: Sep 19, 2013
 *      Author: venkat
 */


#include <stdexcept>
#include "fixed_capacity_bool_vector.h"

FixedCapacityBooleanVector::FixedCapacityBooleanVector(int c)
{
	capacity = c;
	storage = new int[(c / 32) + 1];
	length = 0;
}

FixedCapacityBooleanVector::~FixedCapacityBooleanVector()
{
	delete[] storage;
}

void FixedCapacityBooleanVector::append(bool b)
{
	set(length++, b);
}

/**
 * Sets the boolean value at index to 'b'.
 * Uses bit manipulation to set the bit.
 */
void FixedCapacityBooleanVector::set(int index, bool b)
{
	if(index >= length)
	{
		throw new std::length_error("index exceeded length");
	}
	int i = index / 32;
	int j = index % 32;

	int k = storage[i];
	if(b)
	{
		storage[i] = 1 << (31 - j) | k;
	}
	else
	{
		storage[i] = (~(1 << (31 - j))) & k;
	}
}

bool FixedCapacityBooleanVector::get(int index)
{
	if(index >= length)
	{
		throw new std::length_error("index exceeded length");
	}
	int i = index / 32;
	int j = index % 32;
	int k = storage[i];
	int bitSet = k >> (31 - j) & 1;
	return bitSet == 1;
}

int FixedCapacityBooleanVector::getLength()
{
	return length;
}

