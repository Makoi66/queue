#include "tqueue.h"

#include <gtest.h>

TEST(QueueTest, PushAndPop) {
    Queue<int> q;
    q.push(1);
    q.push(2);
    q.push(3);

    EXPECT_EQ(q.front(), 1);
    q.pop();
    EXPECT_EQ(q.front(), 2);
    q.pop();
    EXPECT_EQ(q.front(), 3);
    q.pop();
    EXPECT_TRUE(q.empty());
}



TEST(QueueTest, EmptyQueue) {
    Queue<int> q;
    EXPECT_TRUE(q.empty());
    EXPECT_EQ(q.size(), 0);

    EXPECT_THROW(q.front(), std::out_of_range);
    EXPECT_THROW(q.back(), std::out_of_range);
    EXPECT_THROW(q.pop(), std::out_of_range);
}


TEST(QueueTest, FrontAndBack) {
    Queue<int> q;
    q.push(10);
    EXPECT_EQ(q.front(), 10);
    EXPECT_EQ(q.back(), 10);

    q.push(20);
    EXPECT_EQ(q.front(), 10);
    EXPECT_EQ(q.back(), 20);

    q.push(30);
    EXPECT_EQ(q.front(), 10);
    EXPECT_EQ(q.back(), 30);
}



TEST(QueueTest, Size) {
    Queue<int> q;
    EXPECT_EQ(q.size(), 0);

    q.push(1);
    EXPECT_EQ(q.size(), 1);

    q.push(2);
    EXPECT_EQ(q.size(), 2);

    q.pop();
    EXPECT_EQ(q.size(), 1);

    q.pop();
    EXPECT_EQ(q.size(), 0);
}


TEST(QueueTest, Repack) {
    Queue<int> q;
    for (int i = 0; i < 10; ++i) {
        q.push(i);
    }
    EXPECT_EQ(q.size(), 10);
    for (int i = 0; i < 10; ++i) {
        EXPECT_EQ(q.front(), i);
        q.pop();
    }
}

TEST(QueueTest, Move) {
    Queue<int> q;
    for (int i = 0; i < 5; ++i) {
        q.push(i);
    }
    for (int i = 0; i < 2; ++i) {
        q.pop();
    }
    for (int i = 5; i < 8; ++i) {
        q.push(i);
    }


    EXPECT_EQ(q.size(), 6);

    EXPECT_EQ(q.front(), 2);
    q.pop();
    EXPECT_EQ(q.front(), 3);
    q.pop();
    EXPECT_EQ(q.front(), 4);
    q.pop();
    EXPECT_EQ(q.front(), 5);
    q.pop();

}

TEST(QueueTest, PushPopWithResizing) {
    Queue<int> q;
    for (int i = 0; i < 20; ++i) { // Push more elements than initial capacity
        q.push(i);
        ASSERT_EQ(q.back(), i);  // Check if element is correctly placed after repack
        ASSERT_EQ(q.size(), i + 1);
    }

    for (int i = 0; i < 15; ++i) { // Pop some elements to test shrinking
        ASSERT_EQ(q.front(), i);
        q.pop();
        ASSERT_EQ(q.size(), 20 - i - 1);
    }

    ASSERT_EQ(q.size(), 5);

    for (int i = 15; i < 20; ++i) { // Check if the right values are after pops
        ASSERT_EQ(q.front(), i);
        q.pop();
    }

    ASSERT_EQ(q.size(), 0);
}


TEST(QueueTest, MoveHeadTail) {
    Queue<int> q;

    for (int i = 0; i < 4; ++i) {
        q.push(i);
    }
    ASSERT_EQ(q.size(), 4);
    ASSERT_EQ(q.front(), 0);
    ASSERT_EQ(q.back(), 3);

    for (int i = 0; i < 2; ++i) {
        q.pop();
    }

    ASSERT_EQ(q.size(), 2);
    ASSERT_EQ(q.front(), 2);
    ASSERT_EQ(q.back(), 3);

    for (int i = 0; i < 3; ++i) {
        q.push(i + 4);
    }


    ASSERT_EQ(q.size(), 5);
    ASSERT_EQ(q.front(), 2);
    ASSERT_EQ(q.back(), 6);

}


TEST(QueueTest, EdgeCases) {
    Queue<int> q;
    q.push(1);
    q.pop();
    q.push(2); // Test push after pop when queue was full and became empty
    ASSERT_EQ(q.front(), 2);
    ASSERT_EQ(q.back(), 2);
    ASSERT_EQ(q.size(), 1);


    q.push(3);
    q.push(4);
    q.push(5);


}
