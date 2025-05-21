/*    @file MyHash_test.cpp   
      @author < Fill Me In >
      @date < Fill Me In >

			@description Tests for the MyHash class
*/

#include "gtest/gtest.h"
#include "MyHash.h"


TEST(size, empty) {
  MyHash a;
  EXPECT_EQ(a.size(), 0);
}

TEST(size, few) {
  srand(0);
  MyHash a;
  for(unsigned i = 0; i < 5; i++){
    a.insert(rand() % 10);
    EXPECT_EQ(a.size(), i + 1);
  }
}

TEST(size, lots) {
  srand(0);
  MyHash a;
  for(unsigned i = 0; i < 50; i++){
    a.insert(rand() % 10);
  }
  EXPECT_EQ(a.size(), 50);
  for(unsigned i = 0; i < 200; i++){
    a.insert(rand() % 10);
  }
  EXPECT_EQ(a.size(), 250);
}

TEST(contains, few) {
  srand(0);
  MyHash a;
  EXPECT_EQ(a.contains(5), false);
  a.insert(5);
  EXPECT_EQ(a.contains(5), true);
  for(unsigned i = 0; i < 5; i++){
    int value = rand() % 100;
    a.insert(value);
    EXPECT_EQ(a.contains(value), true);
  }
}

TEST(contains, lots) {
  srand(0);
  MyHash a;
  for(unsigned i = 0; i < 500; i++){
    int value = rand();
    EXPECT_EQ(a.contains(value), false); // Hopefully we can rely on rand!
    a.insert(value);
    EXPECT_EQ(a.contains(value), true);
  }
}

TEST(count, few) {
  srand(0);
  MyHash a;
  EXPECT_EQ(a.count(5), 0);
  a.insert(5);
  EXPECT_EQ(a.count(5), 1);
  a.insert(5);
  EXPECT_EQ(a.count(5), 2);
  a.insert(3);
  EXPECT_EQ(a.count(3), 1);
  a.insert(3);
  EXPECT_EQ(a.count(3), 2);
}

TEST(count, lots) {
  srand(0);
  MyHash a;
  EXPECT_EQ(a.count(5), 0);
  EXPECT_EQ(a.count(3), 0);
  a.insert(5);
  a.insert(5);
  a.insert(3);
  a.insert(3);
  a.insert(3);
  EXPECT_EQ(a.count(5), 2);
  EXPECT_EQ(a.count(3), 3);
  for(unsigned i = 0; i < 200; i++){
    a.insert(rand() % 100 + 6);
  }
  EXPECT_EQ(a.count(5), 2);
  EXPECT_EQ(a.count(3), 3);
}

TEST(erase, few) {
  srand(0);
  MyHash a;
  EXPECT_EQ(a.count(5), 0);
  EXPECT_EQ(a.contains(5), false);
  for(unsigned i = 0; i < 5; i++){
    a.insert(i);
  }
  for(unsigned i = 0; i < 5; i++){
    EXPECT_EQ(a.contains(i), true);
    EXPECT_EQ(a.count(i), 1);
  }
  a.erase(3);
  EXPECT_EQ(a.count(3), 0);
  EXPECT_EQ(a.contains(3), false);
}

TEST(erase, multiple) {
  srand(0);
  MyHash a;
  EXPECT_EQ(a.count(5), 0);
  EXPECT_EQ(a.contains(5), false);
  for(unsigned i = 0; i < 5; i++){
    a.insert(i);
  }
  for(unsigned i = 0; i < 5; i++){
    EXPECT_EQ(a.contains(i), true);
    EXPECT_EQ(a.count(i), 1);
  }
  for(unsigned i = 0; i < 5; i++){
    a.insert(i);
  }
  for(unsigned i = 0; i < 5; i++){
    EXPECT_EQ(a.contains(i), true);
    EXPECT_EQ(a.count(i), 2);
  }
  a.erase(4);
  EXPECT_EQ(a.count(4), 1);
  EXPECT_EQ(a.contains(4), true);
  for(unsigned i = 0; i < 4; i++){
    a.erase(i);
  }
  for(unsigned i = 0; i < 5; i++){
    EXPECT_EQ(a.contains(i), true);
    EXPECT_EQ(a.count(i), 1);
  }
  for(unsigned i = 0; i < 4; i++){
    a.erase(i);
  }
  for(unsigned i = 0; i < 4; i++){
    EXPECT_EQ(a.contains(i), false);
    EXPECT_EQ(a.count(i), 0);
  }
  EXPECT_EQ(a.contains(4), true);
    EXPECT_EQ(a.count(4), 1);
}

TEST(copy, simple) {
  srand(0);
  MyHash a;
  for(unsigned i = 0; i < 5; i++){
    a.insert(i);
  }
  EXPECT_EQ(a.size(), 5);
  MyHash b(a);
  EXPECT_EQ(b.size(), 5);
  for(unsigned i = 0; i < 5; i++){
    EXPECT_EQ(a.contains(i), true);
  }
  for(unsigned i = 0; i < 5; i++){
    EXPECT_EQ(b.contains(i), true);
  }
}

TEST(copy, complex_large) {
  srand(0);
  MyHash a;
  for(unsigned i = 0; i < 50; i++){
    a.insert(i * 45 % 27);
  }
  EXPECT_EQ(a.size(), 50);
  MyHash b(a);
  EXPECT_EQ(b.size(), 50);
  a.erase(0);
  EXPECT_EQ(a.size(), 49);
  EXPECT_EQ(b.size(), 50);
  for(unsigned i = 1; i < 25; i++){
    a.erase(i * 45 % 27);
  }
  EXPECT_EQ(a.size(), 25);
  EXPECT_EQ(b.size(), 50);
}

TEST(assign, simple) {
  srand(0);
  MyHash a;
  for(unsigned i = 0; i < 5; i++){
    a.insert(i);
  }
  EXPECT_EQ(a.size(), 5);
  MyHash b;
  b.insert(100);
  b = a;
  EXPECT_EQ(b.size(), 5);
  for(unsigned i = 0; i < 5; i++){
    EXPECT_EQ(a.contains(i), true);
  }
  for(unsigned i = 0; i < 5; i++){
    EXPECT_EQ(b.contains(i), true);
  }
  EXPECT_EQ(b.contains(100), false);
}

TEST(assign, complex) {
  srand(0);
  MyHash a;
  for(unsigned i = 0; i < 5; i++){
    a.insert(i);
  }
  EXPECT_EQ(a.size(), 5);
  MyHash b;
  b.insert(100);
  b = a;
  EXPECT_EQ(b.size(), 5);
  for(unsigned i = 0; i < 5; i++){
    EXPECT_EQ(a.contains(i), true);
  }
  for(unsigned i = 0; i < 5; i++){
    EXPECT_EQ(b.contains(i), true);
  }
  a.insert(54);
  b.insert(55);
  EXPECT_EQ(a.contains(54), true);
  EXPECT_EQ(b.contains(54), false);
  EXPECT_EQ(a.contains(55), false);
  EXPECT_EQ(b.contains(55), true);
}


// Double hashing tests **************************************
TEST(size_double, empty) {
  MyHash a(true, 3, double_hash);
  EXPECT_EQ(a.size(), 0);
}

TEST(size_double, few) {
  srand(0);
  MyHash a(true, 3, double_hash);
  for(unsigned i = 0; i < 5; i++){
    a.insert(rand() % 10);
    EXPECT_EQ(a.size(), i + 1);
  }
}

TEST(size_double, lots) {
  srand(0);
  MyHash a(true, 3, double_hash);
  for(unsigned i = 0; i < 50; i++){
    a.insert(rand() % 10);
  }
  EXPECT_EQ(a.size(), 50);
  for(unsigned i = 0; i < 200; i++){
    a.insert(rand() % 10);
  }
  EXPECT_EQ(a.size(), 250);
}

TEST(contains_double, few) {
  srand(0);
  MyHash a(true, 3, double_hash);
  EXPECT_EQ(a.contains(5), false);
  a.insert(5);
  EXPECT_EQ(a.contains(5), true);
  for(unsigned i = 0; i < 5; i++){
    int value = rand() % 100;
    a.insert(value);
    EXPECT_EQ(a.contains(value), true);
  }
}

TEST(contains_double, lots) {
  srand(0);
  MyHash a(true, 3, double_hash);
  for(unsigned i = 0; i < 500; i++){
    int value = rand();
    EXPECT_EQ(a.contains(value), false); // Hopefully we can rely on rand!
    a.insert(value);
    EXPECT_EQ(a.contains(value), true);
  }
}

TEST(count_double, few) {
  srand(0);
  MyHash a(true, 51, double_hash);
  EXPECT_EQ(a.count(5), 0);
  a.insert(5);
  EXPECT_EQ(a.count(5), 1);
  a.insert(5);
  EXPECT_EQ(a.count(5), 2);
  a.insert(3);
  EXPECT_EQ(a.count(3), 1);
  a.insert(3);
  EXPECT_EQ(a.count(3), 2);
}

TEST(count_double, lots) {
  srand(0);
  MyHash a(true, 51, double_hash);
  EXPECT_EQ(a.count(5), 0);
  EXPECT_EQ(a.count(3), 0);
  a.insert(5);
  a.insert(5);
  a.insert(3);
  a.insert(3);
  a.insert(3);
  EXPECT_EQ(a.count(5), 2);
  EXPECT_EQ(a.count(3), 3);
  for(unsigned i = 0; i < 200; i++){
    a.insert(rand() % 100 + 6);
  }
  EXPECT_EQ(a.count(5), 2);
  EXPECT_EQ(a.count(3), 3);
}

TEST(erase_double, few) {
  srand(0);
  MyHash a(true, 3, double_hash);
  EXPECT_EQ(a.count(5), 0);
  EXPECT_EQ(a.contains(5), false);
  for(unsigned i = 0; i < 5; i++){
    a.insert(i);
  }
  for(unsigned i = 0; i < 5; i++){
    EXPECT_EQ(a.contains(i), true);
    EXPECT_EQ(a.count(i), 1);
  }
  a.erase(3);
  EXPECT_EQ(a.count(3), 0);
  EXPECT_EQ(a.contains(3), false);
}

TEST(erase_double, multiple) {
  srand(0);
  MyHash a(true, 3, double_hash);
  EXPECT_EQ(a.count(5), 0);
  EXPECT_EQ(a.contains(5), false);
  for(unsigned i = 0; i < 5; i++){
    a.insert(i);
  }
  for(unsigned i = 0; i < 5; i++){
    EXPECT_EQ(a.contains(i), true);
    EXPECT_EQ(a.count(i), 1);
  }
  for(unsigned i = 0; i < 5; i++){
    a.insert(i);
  }
  for(unsigned i = 0; i < 5; i++){
    EXPECT_EQ(a.contains(i), true);
    EXPECT_EQ(a.count(i), 2);
  }
  a.erase(4);
  EXPECT_EQ(a.count(4), 1);
  EXPECT_EQ(a.contains(4), true);
  for(unsigned i = 0; i < 4; i++){
    a.erase(i);
  }
  for(unsigned i = 0; i < 5; i++){
    EXPECT_EQ(a.contains(i), true);
    EXPECT_EQ(a.count(i), 1);
  }
  for(unsigned i = 0; i < 4; i++){
    a.erase(i);
  }
  for(unsigned i = 0; i < 4; i++){
    EXPECT_EQ(a.contains(i), false);
    EXPECT_EQ(a.count(i), 0);
  }
  EXPECT_EQ(a.contains(4), true);
    EXPECT_EQ(a.count(4), 1);
}

TEST(copy_double, simple) {
  srand(0);
  MyHash a(true, 3, double_hash);
  for(unsigned i = 0; i < 5; i++){
    a.insert(i);
  }
  EXPECT_EQ(a.size(), 5);
  MyHash b(a);
  EXPECT_EQ(b.size(), 5);
  for(unsigned i = 0; i < 5; i++){
    EXPECT_EQ(a.contains(i), true);
  }
  for(unsigned i = 0; i < 5; i++){
    EXPECT_EQ(b.contains(i), true);
  }
}

TEST(copy_double, complex_large) {
  srand(0);
  MyHash a(true, 101, double_hash);
  for(unsigned i = 0; i < 50; i++){
    a.insert(i * 45 % 27);
  }
  EXPECT_EQ(a.size(), 50);
  MyHash b(a);
  EXPECT_EQ(b.size(), 50);
  a.erase(0);
  EXPECT_EQ(a.size(), 49);
  EXPECT_EQ(b.size(), 50);
  for(unsigned i = 1; i < 25; i++){
    a.erase(i * 45 % 27);
  }
  EXPECT_EQ(a.size(), 25);
  EXPECT_EQ(b.size(), 50);
}

TEST(assign_double, simple) {
  srand(0);
  MyHash a(true, 3, double_hash);
  for(unsigned i = 0; i < 5; i++){
    a.insert(i);
  }
  EXPECT_EQ(a.size(), 5);
  MyHash b;
  b.insert(100);
  b = a;
  EXPECT_EQ(b.size(), 5);
  for(unsigned i = 0; i < 5; i++){
    EXPECT_EQ(a.contains(i), true);
  }
  for(unsigned i = 0; i < 5; i++){
    EXPECT_EQ(b.contains(i), true);
  }
  EXPECT_EQ(b.contains(100), false);
}

TEST(assign_double, complex) {
  srand(0);
  MyHash a(true, 3, double_hash);
  for(unsigned i = 0; i < 5; i++){
    a.insert(i);
  }
  EXPECT_EQ(a.size(), 5);
  MyHash b;
  b.insert(100);
  b = a;
  EXPECT_EQ(b.size(), 5);
  for(unsigned i = 0; i < 5; i++){
    EXPECT_EQ(a.contains(i), true);
  }
  for(unsigned i = 0; i < 5; i++){
    EXPECT_EQ(b.contains(i), true);
  }
  a.insert(54);
  b.insert(55);
  EXPECT_EQ(a.contains(54), true);
  EXPECT_EQ(b.contains(54), false);
  EXPECT_EQ(a.contains(55), false);
  EXPECT_EQ(b.contains(55), true);
}
