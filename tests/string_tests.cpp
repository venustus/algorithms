/*
 * string_tests.cpp
 *
 *  Created on: Jul 9, 2013
 *      Author: venkat
 */

#include <string>
#include "gtest/gtest.h"
#include "string_reverse.h"
#include "string_permute.h"
#include "stringcompress.h"
#include "string_normalize.h"
#include "anagram.h"
#include "wildcard_expansion.h"

namespace {
  class StringTests : public ::testing::Test {

  };

  TEST(StringTests, StringReverseTest)
  {
	  std::string evenInput("even");
	  char * reversedString = reverse((char *) evenInput.c_str());
	  EXPECT_STREQ("neve", reversedString);

	  // odd number of characters
	  std::string oddInput("odd");
	  reversedString = reverse((char *) oddInput.c_str());
	  EXPECT_STREQ("ddo", reversedString);

	  // single character
	  std::string singleChar("c");
	  reversedString = reverse((char *) singleChar.c_str());
	  EXPECT_STREQ("c", reversedString);

	  // empty string
	  std::string emptyStr("");
	  reversedString = reverse((char *) emptyStr.c_str());
	  EXPECT_STREQ("", reversedString);
  }

  TEST(StringTests, StringPermuteTest)
  {
	  std::string input("permute");
	  std::string inputPermuted("mutpeer");
	  EXPECT_EQ(true, isPermutation((char *) input.c_str(), (char *) inputPermuted.c_str()));

	  std::string inputNotPermuted("mutp0er");
	  EXPECT_EQ(false, isPermutation((char *) input.c_str(),
			  	  	  	  	  	  	  (char *) inputNotPermuted.c_str()));

	  // single character
	  std::string singleChar("c");
	  std::string singleChar2("c");
	  EXPECT_EQ(true, isPermutation((char *) singleChar.c_str(),
			  	  	  	  	  	  	 (char *) singleChar2.c_str()));
  }

  TEST(StringTests, StringCompressTest)
  {
	  std::string input("aaaabbbccdddde");
	  char * compressedStr = compress((char *)input.c_str(), 14);
	  EXPECT_STREQ(compressedStr, "a4b3c2d4e1");

	  // uncompressable string
	  std::string input2("aabbccdd");
	  compressedStr = compress((char *)input2.c_str(), 8);
	  EXPECT_STREQ(compressedStr, "aabbccdd");

	  // single character
	  std::string input3("a");
	  compressedStr = compress((char *)input3.c_str(), 1);
	  EXPECT_STREQ(compressedStr, "a");
  }

  TEST(StringTests, StringNormalizeTest)
  {
	  std::string input("this string with spaces      ");
	  char *normalizedStr = normalize((char *)input.c_str(), 23);
	  EXPECT_STREQ(normalizedStr, "this%20string%20with%20spaces");

	  std::string input2("inputwithnospaces");
	  normalizedStr = normalize((char *)input2.c_str(), 17);
	  EXPECT_STREQ(normalizedStr, "inputwithnospaces");
  }

  TEST(StringTests, AnagramTest)
  {
	  std::string input1("secure");
	  std::string input2("rescue");
	  bool value = areAnagrams(input1, input2);
	  EXPECT_EQ(true, value);
	  std::string input3("something");
	  std::string input4("else");
	  value = areAnagrams(input3, input4);
	  EXPECT_EQ(false, value);
  }

  TEST(StringTests, WildcardTest)
  {
	  std::string input("1?00?101");
	  std::vector<std::string> * results = expandWildcards(input);
	  EXPECT_EQ(4, results->size());
	  for(std::vector<std::string>::iterator it = results->begin(); it != results->end(); ++it)
	  {
		  std::cout << *it << " ";
	  }
	  std::cout << std::endl;
  }
}


