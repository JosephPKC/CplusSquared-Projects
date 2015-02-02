#ifndef GENERICFUNCTIONS_H
#define GENERICFUNCTIONS_H
#include "NodePair.h"

template <typename T>
struct default_t{
    operator T() const{return T();}
};

//Functors
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
private:
    std::ostream& out;
public:
    Print(std::ostream& outs):out(outs){}
    void operator()(const T& obj){
        out << obj << " | ";
    }
};

template <typename T, typename U>
struct Hold{
    U value;
    void operator ()(const T& obj){

    }
};

template <typename T>
struct Equal{
    bool operator()(const T& left, const T& right){
        return left == right;
    }
};

template <typename T>
struct Less{
    bool operator()(const T& left, const T& right){
        return left < right;
    }
};

template <typename T>
struct Greater{
    bool operator()(const T& left, const T& right){
        return left > right;
    }
};

template <typename T>
struct True{
    bool operator()(const T& left, const T& right){
        return true;
    }
};

template <typename T, typename U>
struct GreaterFreq{
    bool operator()(const NodePair<T,U>& left, const NodePair<T,U>& right){
        return greatS(left,right);
    }
};

//Generic Functions
template <typename T,  typename condition, typename action>
void traverse(Node<T>* head, condition cond,  action act, const T& item){
    while(head){
        if(cond(head->item,item)) act(head->item);
        head = head->next;
    }
}

//template <typename T, typename action>
//void traverseBasic(Node<T>* head, action act){
//    Node<T>* walker = head;
//    while(walker){
//        act(walker->item);
//        walker = walker->next;
//    }
//}

template <typename T, typename condition, typename action>
void traverse1R(Node<T>*& head, condition cond, action act, const T& item){
    while(head){
        if(cond(head->item,item)) act(head->item);
        head = head->next;
    } //Maybe return the new walker instead of reference head
}

#endif // GENERICFUNCTIONS_H
