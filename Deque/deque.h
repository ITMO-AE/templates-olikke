#ifndef DEQUE_H
#define DEQUE_H
#include <iostream>
#include <stdexcept>
#include <memory>

/*
 1.  вроде б шаблонный класс д.б. описан и реализован в h, или придется подключать cpp ?????
 */

template <typename T>
class Node
{
public:
    T Data;
    Node<T>* Prev;
    Node<T>* Next;
    Node(const T&val): Data(val), Prev(nullptr), Next(nullptr) {}
};

template <typename T>
class Deque
{
private:
    size_t Count;
    Node<T>* Head;
    Node<T>* Tail;
    T& at(size_t index)
    {
        if (index<0 || index>=Count)
        throw std::out_of_range("Ёжкин кот!");
        Node<T>* temp=Head;
        for  (size_t i=0; i<index; i++,temp=temp->Next) {};
        return temp->Data;
    }
public:
    Deque(): Count(0), Head(nullptr), Tail(nullptr) {}
    bool Empty() const  {return Count==0;}
    int Size() const {return Count;}
    void PushFront(const T&  val )
    {
        Node<T>* node=new Node<T>(val);
        if (Count!=0 && Head)
        {
            node->Next=Head;
            Head->Prev=node;
            Head=node;
        }
        else
        {
            Head=node;
            Tail=node;
        }
        Count++;
    }
    void PushBack(T const &  val )
    {
        Node<T>* node=new Node<T>(val);
        if (Count!=0 && Tail)
        {
            node->Prev=Tail;
            Tail->Next=node;
            Tail=node;
        }
        else
        {
            Head=node;
            Tail=node;
        }
        Count++;
    }

    T& At(size_t index)
    {
        std::cout<<"It's NO const At"<<std::endl;
        return at(index);
    }
    const T& At(size_t index) const
    {
        std::cout<<"It's const At"<<std::endl;
        return  const_cast<Deque*>(this)->at(index);
    }
    T& Front()
    {
        std::cout<<"It's NO const Front"<<std::endl;
        return Head->Data;
    }
    const T& Front() const
    {
        std::cout<<"It's const Front"<<std::endl;
        return  Head->Data;
    }
    T& Back()
    {
        std::cout<<"It's NO const Back"<<std::endl;
        return Tail->Data;
    }
    const T& Back() const
    {
        std::cout<<"It's const Back"<<std::endl;
        return Tail->Data;
    }
    T& operator[](size_t index)
    {
        std::cout<<"It's no const []"<<std::endl;
        return at(index);
    }
    const T& operator[](size_t index) const
    {
        std::cout<<"It's const []"<<std::endl;
        return  const_cast<Deque*>(this)->at(index);
    }
};

#endif // DEQUE_H
