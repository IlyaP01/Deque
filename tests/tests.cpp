#include "gtest/gtest.h"
#include "../src/Deque/deque.hpp"

TEST(DequeConstructorTest, ConstructorWithoutParams) {
  deque<int> deque;
  EXPECT_TRUE(deque.empty());
  EXPECT_EQ(deque.size(), 0);
}

TEST(DequeConstructorTest, ConstructorWithNumParam) {
  int val = 0;
  int count = 5;
  deque<int> deque(count, val);
  EXPECT_FALSE(deque.empty());
  EXPECT_EQ(deque.size(), count);
  EXPECT_EQ(deque.front(), val);
  EXPECT_EQ(deque.back(), val);
}

TEST(DequeCopyConstructorTest, CopyOfEmptyDeque) {
  deque<int> deque1;
  deque<int> deque2 = deque1;
  EXPECT_EQ(deque1.size(), deque2.size());
}

TEST(DequeCopyConstructorTest, CopyOfNoEmptyDeque) {
  int val = 0;
  int count = 5;
  deque<int> deque1(count, val);
  deque<int> deque2 = deque1;
  EXPECT_EQ(deque1.size(), deque2.size());
  EXPECT_EQ(deque1.max_size(), deque2.max_size());
  EXPECT_EQ(deque2.front(), val);
  EXPECT_EQ(deque2.back(), val);
}

TEST(DequeMoveConstructor, MoveNoEmptyDeque) {
  int val = 0;
  int count = 5;
  deque<int> deque1(count, val);
  deque<int> deque2 = std::move(deque1);
  EXPECT_EQ(deque1.size(), 0);
  EXPECT_EQ(deque1.max_size(), 0);
  EXPECT_EQ(deque2.size(), count);
  EXPECT_EQ(deque2.front(), val);
  EXPECT_EQ(deque2.back(), val);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
