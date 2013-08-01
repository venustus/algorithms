/*
 * karatsuba_test.cpp
 *
 *  Created on: Jul 28, 2013
 *      Author: venkat
 */

#include "gtest/gtest.h"
#include "int_multiply.h"

namespace {
	class KaratsubaTest : public ::testing::Test {

	};

	TEST(KaratsubaTest, BasicTest) {
		long_int a = 1234;
		long_int b = 5678;
		long_int result = multiply(a, b);
		EXPECT_EQ(result, 7006652);

		a = 39761341;
		b = 13241824;
		result = multiply(a, b);
		EXPECT_EQ(result, 526512679525984);

		a = 13598410;
		b = 32141124;
		result = multiply(a, b);
		EXPECT_EQ(result, 437068182012840);
	}
}
