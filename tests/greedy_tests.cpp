/*
 * greedy_tests.cpp
 *
 *  Created on: Oct 6, 2013
 *      Author: venkat
 */

#include "gtest/gtest.h"
#include "job_scheduling.h"

namespace {
	class GreedyTests : public ::testing::Test {
	};

	TEST(GreedyTests, SchedulingJobTest)
	{
		std::vector<Job> jobs;
		jobs.push_back(Job(98, 61));
		jobs.push_back(Job(75, 10));
		jobs.push_back(Job(63, 25));
		jobs.push_back(Job(55, 1));
		jobs.push_back(Job(42, 100));

		retrieveOptimalScheduling(jobs);
		EXPECT_EQ(55, jobs.at(0).getWeight());
		EXPECT_EQ(75, jobs.at(1).getWeight());
		EXPECT_EQ(63, jobs.at(2).getWeight());
		EXPECT_EQ(98, jobs.at(3).getWeight());
		EXPECT_EQ(42, jobs.at(4).getWeight());
	}
}

