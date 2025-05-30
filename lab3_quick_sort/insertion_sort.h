#pragma once
#include <iostream>

template<typename T, typename Compare>
void insertion_sort(T* first, T* last, Compare comp)
{
    for (T* i = first + 1; i < last + 1; i++)
    {
        T val = std::move(*i);
        T* j = i;
        while (j > first && comp(val, *(j - 1)))
        {
            *j = std::move(*(j - 1));
            j--;
        }
        *j = std::move(val);
    }
}