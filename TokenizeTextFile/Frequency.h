#ifndef __FREQUENCY_H_INCLUDED__
#define __FREQUENCY_H_INCLUDED__
#include "ListTools.h"
#include "GenericFunctions.h"
//#include "NodePair.h"

template <typename T>
class Frequency{
private:
    Node<NodePair<T,size_t> >* head;
public:
    Frequency() : head(NULL){}

    Frequency(const Frequency<T>& S) : Frequency(){
        copy(S.head,head);
    }

    Frequency<T>& operator =(const Frequency<T> S){
        destroy(head);
        copy(S.head,head);
        return *this;
    }

    ~Frequency(){
        destroy(head);
    }

    bool empty(){
        return isEmpty(head);
    }

    int size(){
        return count(head);
    }

    void insert(const T& item){
        NodePair<T,size_t> N(item,1);
        Node<NodePair<T,size_t> >* result = insertSortedUnique(head,N);
        if(!result) traverse(head,Equal<NodePair<T,size_t> >(),Increment<NodePair<T,size_t> >(),N);
    }

    void erase(const T& item){
        NodePair<T,size_t> N(item,0);
        deleteNode(head,N);
    }

    unsigned int& operator [](int index){
        NodePair<T,size_t> N = at(head,index);
        return N.secondary;
    }

    template <typename R>
    friend std::ostream& operator <<(std::ostream& out, const Frequency<R>& F){
        traverse(F.head,True<NodePair<T,size_t> >(),Print<NodePair<R,size_t> >(out),{});
        return out;
    }
};
#endif // FREQUENCY_H




