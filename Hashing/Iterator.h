#ifndef ITERATOR_H
#define ITERATOR_H
#include "ListTools.h"
template <class T>
class Iterator{
public:
    template <class U>
    friend class List;
    template <class U>
    friend class SortedList;
    template <class U>
    friend class UniqueList;
    template <class U>
    friend class UniqueSortedList;
    template <class U>
    friend class Frequency;

    Iterator() : ptr(NULL){}
    Iterator(Node<T>* newPtr) : ptr(newPtr){}
//    Iterator(const T& item){

//    }

//    template <class Q>
    friend bool operator ==(const Iterator<T>& LS, const Iterator<T>& RS){
        return LS.ptr == RS.ptr ? true : false;
    }

//    template <class Q>
    friend bool operator != (const Iterator<T>& LS, const Iterator<T>& RS){
        return LS.ptr != RS.ptr ? true : false;
    }

    Iterator<T>& operator ++(void){
//        if(!next()) return NULL;
        ptr = next().ptr;
        return *this;
    }

    Iterator<T>& operator ++(int){
        Iterator<T> Temp(ptr);
//        if(next()) return NULL;
        ptr = next().ptr;
        return Temp;
    }

    T& operator *(){
        return ptr->item;
    }

    Iterator<T> next(){
        if(!ptr) return NULL;
        Iterator<T> Temp(ptr->next);
        return Temp;
    }

private:
    Node<T>* ptr;
};


#endif // ITERATOR_H
