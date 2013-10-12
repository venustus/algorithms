/*
 * lrucache_test.cpp
 *
 *  Created on: Sep 9, 2013
 *      Author: venkat
 */

#include "gtest/gtest.h"
#include "lrucache.h"

namespace {
  class LRUCacheTest : public ::testing::Test {

  };

  class TestCacheBackend: public CacheBackend<int, int>
  {
	  std::unordered_map<int, int> * testMap;
  public:
	  TestCacheBackend()
	  {
		  testMap = new std::unordered_map<int, int>;
		  (*testMap)[0] = 0;
		  (*testMap)[1] = 1;
		  (*testMap)[2] = 4;
		  (*testMap)[3] = 9;
		  (*testMap)[4] = 16;
		  (*testMap)[5] = 25;
		  (*testMap)[6] = 36;
		  (*testMap)[7] = 49;
		  (*testMap)[8] = 64;
		  (*testMap)[9] = 81;
	  }
	  ~TestCacheBackend()
	  {
		  delete testMap;
	  }
	  int fetchFromBackend(int key)
	  {
		  std::unordered_map<int, int>::const_iterator it = testMap->find(key);
		  return it->second;
	  }
  };

  TEST(LRUCacheTest, BasicTest)
  {
	  TestCacheBackend * tb = new TestCacheBackend;
	  LRUCache<int, int> * cache = new LRUCache<int, int>(5, tb);
	  EXPECT_EQ(0, cache->find(0));
	  EXPECT_EQ(1, cache->find(1));
	  EXPECT_EQ(4, cache->find(2));
	  EXPECT_EQ(9, cache->find(3));
	  EXPECT_EQ(16, cache->find(4));
	  EXPECT_EQ(25, cache->find(5));
	  EXPECT_EQ(9, cache->find(3));
	  EXPECT_EQ(36, cache->find(6));
	  EXPECT_EQ(49, cache->find(7));
	  EXPECT_EQ(64, cache->find(8));
	  EXPECT_EQ(81, cache->find(9));
  }
}


