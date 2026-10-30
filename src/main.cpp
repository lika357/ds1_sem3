#include <iostream>

#include "DynamicArray.hpp"
#include "SharedPtr.hpp"
#include "UniquePtr.hpp"

int main()
{
    UniquePtr<int> u(new int(42));
    std::cout << "UniquePtr: " << *u << "\n";

    SharedPtr<int> s1(new int(10));
    SharedPtr<int> s2 = s1;
    std::cout << "SharedPtr use_count: " << s1.use_count() << "\n";

    DynamicArray<int> a(3);
    a[0] = 1;
    a[1] = 2;
    a[2] = 3;
    std::cout << "DynamicArray: " << a[0] << " " << a[1] << " " << a[2] << "\n";

    return 0;
}