//
// Edited by Tamim Nekaien
//
#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

#include <gtest/gtest.h>

#include "index_min_pq.h"

TEST(IndexMinPQ, SimpleScenario) {
  //  Indexed min-priority queue of capacity 100
  IndexMinPQ<double> impq(100);

  // Insert a bunch of key-value
  std::vector<std::pair<double, int>> keyval {
    { 2.2, 99},
    { 51.0, 54},
    { 42.5, 53},
    { 74.32, 93}
  };
  for (auto &i : keyval) {
    impq.Push(i.first, i.second);
  }

  // Key-value at the top should now be (2.2, 99)
  EXPECT_EQ(impq.Top(), 99);
  impq.Pop();

  // Test Contains()
  EXPECT_TRUE(impq.Contains(93));

  // Key-value at the top should now be (42.5, 53)
  EXPECT_EQ(impq.Top(), 53);

  // Test ChangeKey(): change key associated to value 93
  impq.ChangeKey(1.0, 93);
  // Key-value at the top should now be (1.0, 93)
  EXPECT_EQ(impq.Top(), 93);
}

TEST(IndexMinPQ, errorcheck) {
  // Indexed min-priority queue of capacity 100
  IndexMinPQ<double> impq(100);

  EXPECT_THROW(impq.Top(), std::exception);
  EXPECT_THROW(impq.Pop(), std::exception);
  std::vector<std::pair<double, int>> keyval{
    { 2.2, 99},
    { 51.0, 54},
    { 42.5, 53},
    { 74.32, 93}
  };
  for (auto &i : keyval) {
    impq.Push(i.first, i.second);
  }
  EXPECT_THROW(impq.Push(2, 99), std::exception);
  EXPECT_THROW(impq.Push(4, 101), std::exception);
  EXPECT_THROW(impq.ChangeKey(6, 10), std::exception);
  EXPECT_FALSE(impq.Contains(59));
}

TEST(IndexMinPQ, changetype) {
  IndexMinPQ<char> impq(100);
  std::vector<std::pair<char, int>> keyval{
    { 'b', 99},
    { 'c', 54},
    { 'd', 53},
    { 'e', 93}
  };
  for (auto &i : keyval) {
    impq.Push(i.first, i.second);
  }
  EXPECT_EQ(impq.Top(), 99);
  impq.Pop();
  EXPECT_TRUE(impq.Contains(93));
  EXPECT_EQ(impq.Top(), 54);
  impq.ChangeKey('a', 93);
  EXPECT_EQ(impq.Top(), 93);
}

TEST(IndexMinPQ, Extendedcheck) {
  IndexMinPQ<int> impq(100);

  std::vector<std::pair<int, int>> keyval {
    { 99, 99},
    { 54, 54},
    { 42, 53},
    { 74, 93},
    { 2, 18},
    { 51, 22},
    { 33, 33},
    { 78, 78},
    { 92, 92},
    { 32, 32},
    { 76, 76},
    { 55, 55},
    { 21, 21},
    { 14, 14},
    { 88, 88},
    { 13, 13},
    { 36, 36},
    { 91, 91},
    { 67, 67},
    { 5, 5},
    { 10, 10},
    { 20, 20},
    { 30, 30},
    { 40, 40},
    { 50, 50},
    { 60, 60},
    { 69, 69},
    { 70, 70},
    { 80, 80},
    { 90, 90},
    { 61, 61},
    { 62, 62}
  };
  for (auto &i : keyval) {
    impq.Push(i.first, i.second);
  }
  EXPECT_EQ(impq.Size(), 32);
  EXPECT_EQ(impq.Top(), 18);
  impq.Pop();
  EXPECT_TRUE(impq.Contains(93));
  EXPECT_EQ(impq.Top(), 5);
  impq.ChangeKey(3, 93);
  EXPECT_EQ(impq.Top(), 93);
  impq.Pop();
  impq.Pop();
  impq.Pop();
  impq.Pop();
  EXPECT_EQ(impq.Size(), 27);
  EXPECT_TRUE(impq.Contains(93));
  EXPECT_TRUE(impq.Contains(61));
  EXPECT_TRUE(impq.Contains(62));
  EXPECT_FALSE(impq.Contains(63));
  impq.ChangeKey(4, 22);
  EXPECT_TRUE(impq.Contains(22));
  impq.Push(1, 1);
  EXPECT_EQ(impq.Top(), 1);
  impq.ChangeKey(16, 1);
  EXPECT_EQ(impq.Top(), 22);
}

TEST(IndexMinPQ, vecinttype) {
  std::vector<int> vec{1, 2, 3, 4, 5, 6};
  std::vector<int> vec1{4, 6, 6, 7, 8, 9};
  std::vector<int> vec2{10, 1, 3, 8, 10};
  std::vector<int> vec3{5, 5, 5, 5, 5};
  IndexMinPQ<int> impq(100);
  std::vector<std::pair<int, int>> keyval {
    { vec[0], 99},
    { vec1[1], 54},
    { vec2[2], 53},
    { vec3[3], 93}
  };
  for (auto &i : keyval) {
    impq.Push(i.first, i.second);
  }
  EXPECT_EQ(impq.Top(), 99);
  impq.Pop();

  EXPECT_TRUE(impq.Contains(93));
  EXPECT_EQ(impq.Top(), 53);
  impq.ChangeKey(vec2[1], 93);
  EXPECT_EQ(impq.Top(), 93);
}


int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
