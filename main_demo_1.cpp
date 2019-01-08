#include <iostream>
#include <string>
#include "Person.h"

template <typename T>
class Accum
{
public:
    Accum(T start):
    total(start) {}
    T operator+=(T const& t)
    {
        return total = total + t;
    }

    T getTotal() const
    {
        return total;
    }

private:
    T total;
};

template <>
class Accum<Person>
{
public:
    Accum(int start):
            total(start) {}
    int operator+=(Person const& t)
    {
        return total = total + t.getId();
    }

    int getTotal() const
    {
        return total;
    }

private:
    int total;
};

int main()
{
    Accum<int> integers(0);
    integers += 3;
    integers += 7;
    std::cout << integers.getTotal() << std::endl;

    Accum<std::string> strings(std::string(""));
    strings += "Hello ";
    strings += "world";
    std::cout << strings.getTotal() << std::endl;

    Accum<Person> people(0);
    Person p1("f1", "s1", 17);
    Person p2("f2", "s2", 19);

    people += p1;
    people += p2;

    std::cout << people.getTotal() << std::endl;
    return 0;
}