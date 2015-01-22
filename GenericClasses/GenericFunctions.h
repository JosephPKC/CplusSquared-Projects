#ifndef GENERICFUNCTIONS_H
#define GENERICFUNCTIONS_H
#include "ListTools.h"
template <typename T>
struct DoNothing{
    void operator ()(const T& obj){
        //do nothing
    }
};

template <typename T>
struct Increment{
    void operator ()(T& obj){
        obj++; //Needs to be defined for type T
    }
};

template <typename T>
struct Print{
    void operator()(const T& obj){
        std::cout << obj;
    }
};

template <typename T>
struct Equal{
    bool operator()(const T& left, const T& right){
        return left == right;
    }
};

template <typename T>
struct True{
    bool operator()(const T& left, const T& right){
        return true;
    }
};

template <typename T, typename action, typename condition>
void traverseCond(Node<T>* head, action act, condition cond, const T& item){
    while(head){
        if(cond(head->item,item)) act(head->item);
        head = head->next;
    }
}

#endif // GENERICFUNCTIONS_H
