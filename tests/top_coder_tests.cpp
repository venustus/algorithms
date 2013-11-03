#include "gtest/gtest.h"
#include "top_coder_tests.h"

namespace {
    class TopCoderTests : public ::testing::Test {

    };

    TEST(TopCoderTests, StampColoringTest) {
        int minimumCost = findMinimumStampColoringCost("RRGGBB", 1, 1);
        EXPECT_EQ(5, minimumCost);

        minimumCost = findMinimumStampColoringCost("R**GB*", 1, 1);
        EXPECT_EQ(5, minimumCost);

        minimumCost = findMinimumStampColoringCost("BRRB", 2, 7);
        EXPECT_EQ(30, minimumCost);

        minimumCost = findMinimumStampColoringCost("R*RR*GG", 10, 58);
        EXPECT_EQ(204, minimumCost);

        minimumCost = findMinimumStampColoringCost("*B**B**B*BB*G*BBB**B**B*", 5, 2);
        EXPECT_EQ(33, minimumCost);

        minimumCost = findMinimumStampColoringCost("*R*RG*G*GR*RGG*G*GGR***RR*GG", 7, 1);
        EXPECT_EQ(30, minimumCost);
    }

    TEST(TopCoderTests, ColorfulRoadTest) {
        int minimumCost = getMinCostToCrossColorfulRoad("RGGGB");
        EXPECT_EQ(8, minimumCost);

        minimumCost = getMinCostToCrossColorfulRoad("RGBRGBRGB");
        EXPECT_EQ(8, minimumCost);

        minimumCost = getMinCostToCrossColorfulRoad("RBBGGGRR");
        EXPECT_EQ(-1, minimumCost);

        minimumCost = getMinCostToCrossColorfulRoad("RBRRBGGGBBBBR");
        EXPECT_EQ(50, minimumCost);

        minimumCost = getMinCostToCrossColorfulRoad("RG");
        EXPECT_EQ(1, minimumCost);

        minimumCost = getMinCostToCrossColorfulRoad("RBRGBGBGGBGRGGG");
        EXPECT_EQ(52, minimumCost);
    }
}