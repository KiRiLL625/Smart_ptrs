//
// Created by Admin on 13.10.2024.
//

#include "../Unique_ptr.h"
#include "../Shared_ptr.h"
#include "../MemorySpan.h"
#include "../MsPtr.h"
#include <gtest/gtest.h>

//Тесты для умных указателей и MemorySpan (проверяем создание, перемещение, копирование и т.п.)

TEST(Unique_ptr, creationTest) {
    Unique_ptr<int> ptr(new int(5));
    EXPECT_EQ(*ptr, 5);
}

TEST(Unique_ptr, moveTest) {
    Unique_ptr<int> ptr1(new int(5));
    Unique_ptr<int> ptr2(std::move(ptr1));
    EXPECT_EQ(*ptr2, 5);
}

TEST(Unique_ptr, assignmentTest) {
    Unique_ptr<int> ptr1(new int(5));
    Unique_ptr<int> ptr2(new int(10));
    ptr2 = std::move(ptr1);
    EXPECT_EQ(*ptr2, 5);
}

TEST(Unique_ptr, dereferenceTest) {
    Unique_ptr<int> ptr(new int(5));
    EXPECT_EQ(*ptr, 5);
}

TEST(Unique_ptr, getTest) {
    Unique_ptr<int> ptr(new int(5));
    EXPECT_EQ(ptr.get(), ptr.get());
}

TEST(Unique_ptr, resetTest) {
    Unique_ptr<int> ptr(new int(5));
    int *ptr1 = nullptr;
    ptr.reset(ptr1);
    EXPECT_EQ(ptr.get(), ptr1);
}

TEST(Unique_ptr, releaseTest) {
    Unique_ptr<int> ptr(new int(5));
    int *ptr1 = ptr.release();
    EXPECT_EQ(*ptr1, 5);
    EXPECT_EQ(ptr.get(), nullptr);
    delete ptr1;
}

TEST(Unique_ptr, destructorTest) {
    int *ptr1 = new int(5);
    {
        Unique_ptr<int> ptr(ptr1);
    }
}

TEST(Shared_ptr, creationTest) {
    Shared_ptr<int> ptr(new int(5));
    EXPECT_EQ(*ptr, 5);
}

TEST(Shared_ptr, copyTest) {
    Shared_ptr<int> ptr1(new int(5));
    Shared_ptr<int> ptr2(ptr1);
    EXPECT_EQ(*ptr2, 5);
}

TEST(Shared_ptr, moveTest) {
    Shared_ptr<int> ptr1(new int(5));
    Shared_ptr<int> ptr2(std::move(ptr1));
    EXPECT_EQ(*ptr2, 5);
}

TEST(Shared_ptr, assignmentTest) {
    Shared_ptr<int> ptr1(new int(5));
    Shared_ptr<int> ptr2(new int(10));
    ptr2 = ptr1;
    EXPECT_EQ(*ptr2, 5);
}

TEST(Shared_ptr, getTest) {
    Shared_ptr<int> ptr(new int(5));
    const int *ptr1 = ptr.get();
    EXPECT_EQ(ptr1, ptr.get());
}

TEST(Shared_ptr, ref_countTest) {
    Shared_ptr<int> ptr1(new int(5));
    Shared_ptr<int> ptr2(ptr1);
    EXPECT_EQ(ptr1.use_count(), 2);
    EXPECT_EQ(ptr2.use_count(), 2);
}

TEST(Shared_ptr, releaseTest) {
    Shared_ptr<int> ptr(new int(5));
    int *ptr1 = ptr.release();
    EXPECT_EQ(*ptr1, 5);
    EXPECT_EQ(ptr.get(), nullptr);
    delete ptr1;
}

TEST(Shared_ptr, resetTest) {
    Shared_ptr<int> ptr(new int(5));
    int *ptr1 = new int(10);
    ptr.reset(ptr1);
    EXPECT_EQ(*ptr, 10);
}

TEST(MemorySpan, creationTest) {
    MemorySpan<int, 5> span;
    EXPECT_EQ(span.get_size(), 0);
}

TEST(MemorySpan, addTest) {
    MemorySpan<int, 5> span;
    span.add(5);
    EXPECT_EQ(span.get_size(), 1);
}

TEST(MemorySpan, removeTest) {
    MemorySpan<int, 5> span;
    span.add(5);
    span.remove(0);
    EXPECT_EQ(span.get_size(), 0);
}

TEST(MemorySpan, getPtrTest) {
    MemorySpan<int, 5> span;
    span.add(5);
    MsPtr<int> ptr = span.get_ptr(0);
    EXPECT_EQ(*ptr, 5);
}

TEST(MemorySpan, capacityTest) {
    MemorySpan<int, 5> span;
    for (int i = 0; i < 5; ++i) {
        span.add(i);
    }
    EXPECT_THROW(span.add(5), std::out_of_range);
}

TEST(MemorySpan, indexTest) {
    MemorySpan<int, 5> span;
    span.add(5);
    EXPECT_THROW(span.get_ptr(1), std::out_of_range);
}