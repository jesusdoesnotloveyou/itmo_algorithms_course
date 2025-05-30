#include "quick_sort.h"
#include "insertion_sort.h"
#include "time.h"
#include "nanobench.h"

#include <vector>

void generateRandomArray(int* arr, int N)
{
    for (int i = 0; i < N; i++)
    {
        arr[i] = rand() % 100;
    }
}

void printArray(int* arr, int N)
{
    for (int i = 0; i < N; i++)
    {
        std::cout << arr[i] << " ";
    }
    std::cout << "\n";
}

int main()
{
    const std::vector<int> sizes = { 10000, 20000, 30000, 40000, 50000, 60000, 70000, 80000, 90000, 100000, 150000, 200000, 250000, 300000/*, 350000, 400000, 450000, 500000, 550000, 600000, 650000, 700000, 750000, 800000, 850000, 900000, 950000, 1000000 */};
    
    srand((unsigned)time(0));

    for (int i = 0; i < sizes.size(); i++)
    {
        const int N = sizes[i];
        int* arr = new int[N];
        generateRandomArray(arr, N);

        ankerl::nanobench::Bench().run("insertion_sort", [&] {
            insertion_sort(arr, arr + N - 1, [](int a, int b) { return a > b; });
            ankerl::nanobench::doNotOptimizeAway(arr);
            }).minEpochIterations(10);
        delete[] arr;
    }

    /*for (int i = 0; i < sizes.size(); i++)
    {
        const int N = sizes[i];
        int* arr = new int[N];
        generateRandomArray(arr, N);

        ankerl::nanobench::Bench().run("quick_sort", [&] {
            quick_sort(arr, arr + N - 1, [](int a, int b) { return a > b; });
            ankerl::nanobench::doNotOptimizeAway(arr);
            }).minEpochIterations(10);
        delete[] arr;
    }*/

    for (int i = 0; i < sizes.size(); i++)
    {
        const int N = sizes[i];
        int* arr = new int[N];
        generateRandomArray(arr, N);

        ankerl::nanobench::Bench().run("improved_quick_sort", [&] {
            improved_quick_sort(arr, arr + N - 1, [](int a, int b) { return a > b; });
            ankerl::nanobench::doNotOptimizeAway(arr);
            }).minEpochIterations(10);
        delete[] arr;
    }
    return 0;
}