//
// Created by nadya on 05.01.2019.
//

#ifndef L8_TEMPLATES_PERSON_H
#define L8_TEMPLATES_PERSON_H

#include <string>
#include <iostream>
class Person
{
public:
    Person(std::string const &f_name, std::string const &l_name, int u_id):
    first_name(f_name),
    last_name(l_name),
    u_id(u_id)
    {
        std::cout << "Person ctor \n";
    }
    ~Person()
    {
        std::cout << "Person dtor \n";
    }

    int getId() const
    {
        return u_id;
    }

    friend bool operator<(Person const &p1, Person const &p2);
    friend bool operator>(Person const &p1, Person const &p2);
    friend std::ostream& operator<<(std::ostream &os, Person const &person);

private:
    std::string first_name;
    std::string last_name;
    int u_id;

};

bool operator<(Person const &p1, Person const &p2)
{
    return p1.u_id < p1.u_id;
}

bool operator>(Person const &p1, Person const &p2)
{
    return p1.u_id > p1.u_id;
}

std::ostream& operator<<(std::ostream &os, Person const &person)
{
    os << person.first_name << " " << person.last_name << " " << person.u_id << std::endl;
}
#endif //L8_TEMPLATES_PERSON_H
