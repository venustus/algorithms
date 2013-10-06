/*
 * job_scheduling.cpp
 *
 *  Created on: Oct 6, 2013
 *      Author: venkat
 */

#include <vector>
#include <algorithm>
#include "job_scheduling.h"

Job::Job(double w, int l)
{
	weight = w;
	length = l;
}

Job::~Job()
{

}

double Job::getWeight()
{
	return weight;
}

int Job::getLength()
{
	return length;
}

bool job_compare(Job i, Job j)
{
	return (i.getWeight() / i.getLength()) > (j.getWeight() / j.getLength());
}


/**
 * Problem:
 *
 * Given a list of jobs where each job has a weight/priority,
 * and a length, sort the jobs in such a way that the sum of
 * weighted completion jobs is minimized.
 *
 * That is if jobs j0, j1 ... jn have weights w0, w1, .. wn and
 * lengths l0, l1, l2 .. ln then sequence jobs in such a way that
 * SIGMA (wi*ci) for all i, is minimum - where ci stands for
 * completion time of job i. Completion time of job i is the time
 * elapsed from the moment a first job is scheduled to the moment
 * the job i completes (or equivalently the sum of lengths of all
 * the jobs scheduled prior to the ith job).
 *
 * Paradigm: Greedy
 * Algorithm:
 * 1) Just sort the jobs according to the value (wi/li).
 */
void retrieveOptimalScheduling(std::vector<Job>& jobs)
{
	std::sort(jobs.begin(), jobs.end(), job_compare);
}

