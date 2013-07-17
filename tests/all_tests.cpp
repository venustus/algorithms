/*
 * all_tests.cpp
 *
 *  Created on: Jul 9, 2013
 *      Author: venkat
 */


#include "gtest/gtest.h"

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
