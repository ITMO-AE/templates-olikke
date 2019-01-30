#include <iostream>
#include "deque.h"

using namespace std;

int main()
{
    Deque<int> D;
    D.PushFront(15);
    D.PushFront(10);
    D.PushBack(5);
    D.PushBack(12);
    try {
        std::cout<<D.At(0)<<std::endl;
        std::cout<<D.At(1)<<std::endl;
        std::cout<<D.At(2)<<std::endl;
        std::cout<<D.At(3)<<std::endl;
        int& k=D.Front();
        k=65;
        std::cout<<D.At(0)<<std::endl;
        std::cout<<D[2]<<std::endl;
        std::cout<<D.At(4)<<std::endl;
    } catch (std::out_of_range e) {
        std::cout<<e.what()<<std::endl;
    }


    return 0;
}
