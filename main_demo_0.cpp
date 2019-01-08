#include <iostream>
#include <string>
#include "Person.h"

template <typename T>
T max(T const& t1, T const &t2)
{
    return t1 < t2 ? t2 : t1;
}

int main()
{
    std::cout << max(5, 10) << std::endl;
    std::cout << max<std::string>("abz", "abk") << std::endl;

    Person p1("f1", "s1", 17);
    Person p2("f2", "s2", 19);
    std::cout << max(p1, p2);

    return 0;
}