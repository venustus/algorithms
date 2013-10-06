/*
 * job_scheduling.h
 *
 *  Created on: Oct 6, 2013
 *      Author: venkat
 */

#ifndef JOB_SCHEDULING_H_
#define JOB_SCHEDULING_H_

#include <vector>

class Job
{
	double weight;
	int length;
public:
	Job(double w, int l);
	~Job();
	double getWeight();
	int getLength();
};

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
 */
void retrieveOptimalScheduling(std::vector<Job>& jobs);

#endif /* JOB_SCHEDULING_H_ */
