#pragma once
#include <iostream>

constexpr int INSERTION_THRESHOLD = 32;

template <typename T>
void swappy(T& a, T& b)
{
    T tmp = std::move(a);
    a = std::move(b);
    b = std::move(tmp);
}

template<typename T, typename Compare>
T median_of_three(T* first, T* last, Compare comp)
{
    T* mid = first + (last - first) / 2;
    if (comp(*mid, *first)) swappy(*mid, *first);
    if (comp(*last, *first)) swappy(*last, *first);
    if (comp(*last, *mid)) swappy(*last, *mid);
    return *mid;
}

template <typename T, typename Compare>
T* h_partition(T* first, T* last, Compare comp)
{
    T pivot = median_of_three(first, last, comp);

    T* i = first - 1;
    T* j = last + 1;

    while (true)
    {
        do {
            i++;
        } while (comp(*i, pivot));

        do {
            j--;
        } while (comp(pivot, *j));

        if (i >= j)
        {
            return j;
        }
        swappy(*i, *j);
    }
}

template <typename T, typename Compare>
void quick_sort(T* first, T* last, Compare comp)
{
    if (first < last)
    {
        T* pivot = h_partition(first, last, comp);

        quick_sort(first, pivot, comp);
        quick_sort(pivot + 1, last, comp);
    }
}

template<typename T, typename Compare>
void improved_quick_sort(T* first, T* last, Compare comp)
{
    while (first < last - 1)
    {
        if (last - first < INSERTION_THRESHOLD)
        {
            insertion_sort(first, last, comp);
            break;
        }
        else
        {
            T* pivot = h_partition(first, last, comp);
 
            if (pivot - first < last - pivot - 1)
            {
                improved_quick_sort(first, pivot, comp);
                first = pivot + 1;
            }
            else
            {
                improved_quick_sort(pivot + 1, last, comp);
                last = pivot;
            }
        }
    }
}

//template <typename RandomIt>
//void QuickSort(RandomIt* beg, RandomIt* end)
//{
//    if (end - beg < 2) return;
//    RandomIt* lft = beg;
//    RandomIt* rgt = end - 1;
//    RandomIt* pvt = lft + (rgt - lft) / 2;
//
//    if (*lft < *pvt)
//        while (*++lft < *pvt);
//    if (*rgt > *pvt)
//        while (*--rgt > *pvt);
//    while (lft < rgt)
//    {
//        swappy(*lft, *rgt);
//        while (*++lft < *pvt);
//        while (*--rgt > *pvt);
//    }
//    rgt++;
//    QuickSort(beg, rgt);
//    QuickSort(rgt, end);
//}