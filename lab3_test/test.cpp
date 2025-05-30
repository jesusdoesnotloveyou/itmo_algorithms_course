#include "pch.h"
#include "../lab3_quick_sort/quick_sort.h"
#include "../lab3_quick_sort/insertion_sort.h"

constexpr int N = 10000;

TEST(QuickSortTest, IsSortedTest)
{
	bool bIsSorted = true;
  
    int arr[N];

    for (int i = 0; i < N; i++)
    {
        arr[i] = rand() % 100;
    }

    quick_sort(arr, arr + N - 1, [](int a, int b) { return a < b; });

    for (int i = 0; i < N - 1; i++)
    {
        if (arr[i] > arr[i + 1])
        {
            bIsSorted = false;
            break;
        }
    }
    EXPECT_TRUE(bIsSorted);
}

TEST(QuickSortTest, IsSortedReversedTest)
{
    bool bIsSorted = true;

    int arr[N];

    for (int i = 0; i < N; i++)
    {
        arr[i] = rand() % 100;
    }

    quick_sort(arr, arr + N - 1, [](int a, int b) { return a > b; });

    for (int i = 0; i < N - 1; i++)
    {
        if (arr[i] < arr[i + 1])
        {
            bIsSorted = false;
            break;
        }
    }
    EXPECT_TRUE(bIsSorted);
}

TEST(InsertionSortTest, IsSortedTest)
{
    bool bIsSorted = true;

    int arr[N];

    for (int i = 0; i < N; i++)
    {
        arr[i] = rand() % 100;
    }

    insertion_sort(arr, arr + N - 1, [](int a, int b) { return a < b; });

    for (int i = 0; i < N - 1; i++)
    {
        if (arr[i] > arr[i + 1])
        {
            bIsSorted = false;
            break;
        }
    }
    EXPECT_TRUE(bIsSorted);
}

TEST(InsertionSortTest, IsSortedReversedTest)
{
    bool bIsSorted = true;

    int arr[N];

    for (int i = 0; i < N; i++)
    {
        arr[i] = rand() % 100;
    }

    insertion_sort(arr, arr + N - 1, [](int a, int b) { return a > b; });

    for (int i = 0; i < N - 1; i++)
    {
        if (arr[i] < arr[i + 1])
        {
            bIsSorted = false;
            break;
        }
    }
    EXPECT_TRUE(bIsSorted);
}

TEST(ImprovedQuickSortTest, IsSortedTest)
{
    bool bIsSorted = true;

    int arr[N];

    for (int i = 0; i < N; i++)
    {
        arr[i] = rand() % 100;
    }

    improved_quick_sort(arr, arr + N - 1, [](int a, int b) { return a < b; });

    for (int i = 0; i < N - 1; i++)
    {
        if (arr[i] > arr[i + 1])
        {
            bIsSorted = false;
            break;
        }
    }
    EXPECT_TRUE(bIsSorted);
}

TEST(ImprovedQuickSortTest, IsSortedReversedTest)
{
    bool bIsSorted = true;

    int arr[N];

    for (int i = 0; i < N; i++)
    {
        arr[i] = rand() % 100;
    }

    improved_quick_sort(arr, arr + N - 1, [](int a, int b) { return a > b; });

    for (int i = 0; i < N - 1; i++)
    {
        if (arr[i] < arr[i + 1])
        {
            bIsSorted = false;
            break;
        }
    }
    EXPECT_TRUE(bIsSorted);
}