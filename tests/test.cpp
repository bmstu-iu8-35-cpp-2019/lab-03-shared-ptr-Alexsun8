// Copyright 2018 Your Name <your_email>

#include <gtest/gtest.h>

#include "header.hpp"

TEST(SharedPtr, test) {
  SharedPtr<int> ptr;
  EXPECT_FALSE(ptr);
  EXPECT_EQ(ptr.use_count(), 0);
  int* temp1 = new int(24);
  int* temp2 = new int(28);
  SharedPtr<int> t(temp1);  // - mem
  EXPECT_EQ(*temp1, *t);
  EXPECT_TRUE(t);
  EXPECT_EQ(t.use_count(), 1);

  SharedPtr<int> t2(t);
  EXPECT_EQ(t2.use_count(), 2);
  EXPECT_EQ(*t2, *temp1);
  t2.reset(temp2);  // - mem
  EXPECT_EQ(t2.use_count(), 1);
  EXPECT_EQ(t.use_count(), 1);
  EXPECT_EQ(*t2, 28);
  SharedPtr<int> t3(t2);
  t3.swap(t);
  EXPECT_EQ(*t, *temp2);
  EXPECT_EQ(t.use_count(), 2);
  EXPECT_EQ(*t3, *temp1);
  EXPECT_EQ(t3.use_count(), 1);

  t2.reset();

  EXPECT_EQ(t.use_count(), 1);

  t2 = t3;
  EXPECT_EQ(t2.use_count(), 2);
  EXPECT_EQ(t3.use_count(), 2);
  EXPECT_EQ(t.use_count(), 1);
  EXPECT_EQ(*t2, *temp1);
  // delete temp1;
  // delete temp2;
}
