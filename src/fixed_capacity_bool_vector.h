/*
 * fixed_capacity_bool_vector.h
 *
 *  Created on: Sep 19, 2013
 *      Author: venkat
 */

#ifndef FIXED_CAPACITY_BOOL_VECTOR_H_
#define FIXED_CAPACITY_BOOL_VECTOR_H_

/**
 * A data structure that maintains a fixed capacity boolean vector.
 * Allowed operations:
 * 1) append a boolean value
 * 2) set a value at a given index
 * 3) get a value given an index
 * 4) get the length of the vector
 *
 * Time complexity for all operations: O(1)
 * Space complexity for all operations: O(1)
 */
class FixedCapacityBooleanVector
{
	int capacity;
	int length;
	int * storage;
public:
	FixedCapacityBooleanVector(int capacity);
	~FixedCapacityBooleanVector();

	void append(bool b);
	void set(int index, bool b);
	bool get(int index);
	int getLength();
};



#endif /* FIXED_CAPACITY_BOOL_VECTOR_H_ */
