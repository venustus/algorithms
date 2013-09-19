/*
 * boolean_vector_tests.cpp
 *
 *  Created on: Sep 19, 2013
 *      Author: venkat
 */


#include "gtest/gtest.h"
#include "fixed_capacity_bool_vector.h"

namespace {
	class BooleanVectorTests : public ::testing::Test {

	};

	TEST(BooleanVectorTests, BasicTests)
	{
		FixedCapacityBooleanVector bv(100);
		bv.append(true);
		bv.append(true);
		bv.append(false);
		bv.append(true);
		bv.append(false);

		ASSERT_TRUE(bv.get(0));
		ASSERT_FALSE(bv.get(2));
		ASSERT_TRUE(bv.get(3));
		ASSERT_FALSE(bv.get(4));

		bv.set(4, true);

		ASSERT_TRUE(bv.get(4));
	}
}

