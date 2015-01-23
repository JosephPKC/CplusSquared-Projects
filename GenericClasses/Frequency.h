#ifndef FREQUENCY_H
#define FREQUENCY_H
#include "ListTools.h"
#include "GenericFunctions.h"
#include "NodePair.h"

template <typename T>
class Frequency{
private:
    Node<NodePair<T,size_t> >* head;

    bool isUnique(const T& item){
        return !searchPair(item);
    }

//    FreqPair<T>* searchPair(const T& item){
//        FreqPair<T>* walker = head;
//        while(walker){
//            if(walker->item.second == item)
//                return walker;
//            walker = walker->next;
//        }
//        return NULL;
//    }

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

    void insert(const T& item){
        Node<T>* result = insertSortedUnique(head,item);
        if(result)
            traverseCond(head,Increment<T>(),Equal<T>(),item);
    }

    template <class Q>
    friend std::ostream& operator <<(std::ostream& out, const Frequency<Q>& L){
        traverseCond(L.head,Print<Q>(),True<Q>(),NULL);
        return out;
    }
};

#endif // FREQUENCY_H




