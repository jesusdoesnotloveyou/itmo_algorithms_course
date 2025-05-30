#include <iostream>
#include <vector>
#include "Array.h"

int main()
{
    Array<std::string> arr1(16);
    for (int i = 0; i < 5; i++)
    {
        arr1.push_back(std::string("ups"));
    }
    
    arr1.insert(5, std::string("privet"));
    std::cout << arr1.size() << "\n";

    for (auto it = arr1.iterator(); it.hasNext(); it.next())
    {
        std::cout << it.get() << "\n";
    }
    Array<std::string> arr2;
    arr2 = std::move(arr1);

    std::cout << arr2.size() << "\n";

    for (auto it = arr2.iterator(); it.hasNext(); it.next())
    {
        std::cout << it.get() << "\n";
    }

    return 0;
}