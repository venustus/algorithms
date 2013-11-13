
#include <functional>
#include "gtest/gtest.h"
#include "hash_table.h"

namespace {
    class HashTableTests : public ::testing::Test {

    };

    TEST(HashTableTests, BasicTests)
    {
        HashTable<int, int> * ht = new CollisionChainingHashTable<int, int>();
        ht->put(1, 1);
        EXPECT_EQ(1, ht->get(1));
        EXPECT_EQ(NULL, ht->get(2));

        ht->put(2, 2);
        EXPECT_EQ(2, ht->get(2));
        EXPECT_TRUE(ht->exists(2));

        EXPECT_EQ(2, ht->put(2, 3));
        EXPECT_EQ(3, ht->get(2));
    }
}