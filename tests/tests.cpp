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

TEST(DequeMoveConstructorTest, MoveNoEmptyDeque) {
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

TEST(DequeCopyAssigmentTest, CopyAssigmentOfEmptyDeque) {
  deque<int> deque1;
  deque<int> deque2;
  deque2 = deque1;
  EXPECT_EQ(deque1.size(), deque2.size());
}

TEST(DequeCopyAssigmentTest, CopyAssigmentOfNoEmptyDeque) {
  int val = 0;
  int count = 5;
  deque<int> deque1(count, val);
  deque<int> deque2;
  deque2 = deque1;
  EXPECT_EQ(deque1.size(), deque2.size());
  EXPECT_EQ(deque1.max_size(), deque2.max_size());
  EXPECT_EQ(deque2.front(), val);
  EXPECT_EQ(deque2.back(), val);
}

TEST(DequeMoveAssigmentTest, MoveNoEmptyDeque) {
  int val = 0;
  int count = 5;
  deque<int> deque1(count, val);
  deque<int> deque2; 
  deque2 = std::move(deque1);
  EXPECT_EQ(deque1.size(), 0);
  EXPECT_EQ(deque1.max_size(), 0);
  EXPECT_EQ(deque2.size(), count);
  EXPECT_EQ(deque2.front(), val);
  EXPECT_EQ(deque2.back(), val);
}

TEST(DequeOperatorIndexTest, IndexInRange) {
  int val = 1;
  int count = 5;
  deque<int> deque(count, val);
  EXPECT_EQ(deque[0], val);
  EXPECT_EQ(deque[1], val);
  EXPECT_EQ(deque[2], val);
  EXPECT_EQ(deque[3], val);
  EXPECT_EQ(deque[4], val);
}

TEST(DequeOperatorIndexTest, ChangeValueByIndex) {
  int val = 1;
  int count = 5;
  int index = 3;
  int newVal = 2;
  deque<int> deque(count, val);
  deque[index] = newVal;
  EXPECT_EQ(deque[index], newVal);
}

TEST(DequeAtIndexTest, IndexInRange) {
  int val = 1;
  int count = 5;
  deque<int> deque(count, val);
  EXPECT_EQ(deque.at(0), val);
  EXPECT_EQ(deque.at(1), val);
  EXPECT_EQ(deque.at(2), val);
  EXPECT_EQ(deque.at(3), val);
  EXPECT_EQ(deque.at(4), val);
}

TEST(DequeAtIndexTest, IndexOutOfRange) {
  int val = 1;
  int count = 5;
  deque<int> deque(count, val);
  EXPECT_THROW(deque.at(count), std::out_of_range);
}

TEST(DequeAtIndexTest, ChangeValueByIndex) {
  int val = 1;
  int count = 5;
  int index = 3;
  int newVal = 2;
  deque<int> deque(count, val);
  deque.at(index) = newVal;
  EXPECT_EQ(deque[index], newVal);
}

TEST(DequeFrontTest, ValidIndex) {
  int val = 1;
  int count = 5;
  deque<int> deque(count, val);
  EXPECT_EQ(deque.front(), val);
}

TEST(DequeBackTest, ValidIndex) {
  int val = 1;
  int count = 5;
  deque<int> deque(count, val);
  EXPECT_EQ(deque.back(), val);
}

TEST(DequePushBackTest, EmptyDeque) {
  deque<int> deque;
  int val;
  deque.push_back(val);
  EXPECT_EQ(deque[0], val);
  EXPECT_EQ(deque.size(), 1);
}

TEST(DequePushBackTest, NoEmptyDeque) {
  int val = 1;
  int count = 5;
  deque<int> deque(count, val);
  int valToPush = 2;
  deque.push_back(val);
  EXPECT_EQ(deque[count], val);
  EXPECT_EQ(deque.size(), count + 1);
}

TEST(DequePushBack, PushWithRealocate) {
  int numOfPushCalls = 100;
  int val = 5;
  deque<int> deque;
  for (int i = 0; i < numOfPushCalls; ++i) {
    deque.push_back(val);
  }
  EXPECT_EQ(deque[0], val);
  EXPECT_EQ(deque[numOfPushCalls - 1], val);
  EXPECT_EQ(deque[numOfPushCalls / 2], val);
  EXPECT_EQ(deque.size(), numOfPushCalls);
}


TEST(DequePushFrontTest, EmptyDeque) {
  deque<int> deque;
  int val;
  deque.push_front(val);
  EXPECT_EQ(deque[0], val);
  EXPECT_EQ(deque.size(), 1);
}

TEST(DequePushFrontTest, NoEmptyDeque) {
  int val = 1;
  int count = 5;
  deque<int> deque(count, val);
  int valToPush = 2;
  deque.push_front(val);
  EXPECT_EQ(deque[0], val);
  EXPECT_EQ(deque.size(), count + 1);
}

TEST(DequePushFrontTest, PushWithRealocate) {
  int numOfPushCalls = 100;
  int val = 5;
  deque<int> deque;
  for (int i = 0; i < numOfPushCalls; ++i) {
    deque.push_front(val);
  }
  EXPECT_EQ(deque[0], val);
  EXPECT_EQ(deque[numOfPushCalls - 1], val);
  EXPECT_EQ(deque[numOfPushCalls / 2], val);
  EXPECT_EQ(deque.size(), numOfPushCalls);
}

TEST(DequeEmplaceBackTest, EmplaceString) {
  deque<std::string> deque;
  std::string testStr = "Test string";
  deque.emplace_back(testStr);
  EXPECT_EQ(deque[0], testStr);
  EXPECT_EQ(deque.size(), 1);
}

TEST(DequeEmplaceFrontTest, EmplaceString) {
  deque<std::string> deque;
  std::string testStr = "Test string";
  deque.emplace_front(testStr);
  EXPECT_EQ(deque[0], testStr);
  EXPECT_EQ(deque.size(), 1);
}

TEST(DequePopBackTest, BecomesNoEmpty) {
  int count = 5;
  int val = 1;
  deque<int> deque(count, val);
  deque.pop_back();
  EXPECT_EQ(deque.size(), count - 1);
  EXPECT_EQ(deque.back(), val);
  EXPECT_EQ(deque.front(), val);
}

TEST(DequePopBackTest, BecomesEmpty) {
  deque<int> deque(1, 1);
  deque.pop_back();
  EXPECT_TRUE(deque.empty());
}

TEST(DequePopFrontTest, BecomesNoEmpty) {
  int count = 5;
  int val = 1;
  deque<int> deque(count, val);
  deque.pop_front();
  EXPECT_EQ(deque.size(), count - 1);
  EXPECT_EQ(deque.back(), val);
  EXPECT_EQ(deque.front(), val);
}

TEST(DequePopFrontTest, BecomesEmpty) {
  deque<int> deque(1, 1);
  deque.pop_front();
  EXPECT_TRUE(deque.empty());
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
