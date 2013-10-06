/*
 * stable_partition.h
 *
 *  Created on: Aug 27, 2013
 *      Author: venkat
 */

#ifndef STABLE_PARTITION_H_
#define STABLE_PARTITION_H_

void swap(int a[], int i, int j);

void merge(int a[], int startIndex, int middleIndex, int endIndex);

/**
 * Partitions array a into negative integers and positive integers
 * such that all negative integers precede all positive integers.
 * The relative ordering among negative integers and among positive
 * integers is retained.
 */
void stablePartition(int a[], int startIndex, int endIndex);


#endif /* STABLE_PARTITION_H_ */
