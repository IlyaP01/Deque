#include "gtest/gtest.h"
#include "../src/Deque/deque.hpp"

TEST(sample_test_case, sample_test) {
  EXPECT_EQ(1, 1);
}

TEST(sample_test_case2, sample_test2) {
  EXPECT_EQ(1, 0);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
