#ifndef FREQUENCY_H
#define FREQUENCY_H
#include"ListTools.h"
#include "Iterator.h"
//#include <cstddef>
template <class T>
using FreqPair = Node<std::pair<size_t,T>>;

template <class T>
bool operator ==(const std::pair<size_t,T>& LS, const std::pair<size_t,T>& RS){
    return LS.second == RS.second;
}

template <class T>
bool operator <(const std::pair<size_t,T>& LS, const std::pair<size_t,T>& RS){
    return LS.second < RS.second;
}

template <class T>
bool operator >(const std::pair<size_t,T>& LS, const std::pair<size_t,T>& RS){
    return LS.second > RS.second;
}

template <class T>
class Frequency{
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
        if(!isUnique(item)){
            FreqPair<T>* here = searchPair(item);
            here->item.first++;
        }
        else{
            const size_t& size = 1;
            insertSorted(head,std::make_pair(size,item));
        }
    }

//    Iterator<T> search(const T& item){
//        Iterator<T> Temp;
//        Temp.ptr = searchPair(item);
//        return Temp;
//    }

//    T deleteAt(Iterator<T> Mark){
//        FreqPair<T> F = deleteNode(head,Mark.ptr);
//        return F.item.second;
//    }

//    Iterator<T> remove(Iterator<T> Mark){
//        Iterator<T> Temp(removeNode(head,Mark.ptr));
//        return Temp;
//    }

//    Iterator<T> begin() const{
//        Iterator<T> Beginning(head);
//        return Beginning;
//    }

//    Iterator<T> end() const{
//        Iterator<T> Ending(ltf::end(head));
//        return Ending;
//    }

    T& operator [](int index){
        FreqPair<T> F = at(head,index);
        return F.item.second;
    }

    Frequency<T>& operator +=(const T& item){
        insert(item);
        return *this;
    }

    Frequency<T>& operator +=(const Frequency<T>& RS){
        FreqPair<T>* temp = NULL;
        copy(RS.head,temp);
        while(temp){
            insert(temp->item.second);
            temp = temp->next;
        }
        return *this;
    }

    template <class Q>
    friend std::ostream& operator <<(std::ostream& out, const Frequency<Q>& L){
        FreqPair<Q>* walker = L.head;
        while(walker){
            out << walker->item.second << "(" << walker->item.first << ") | ";
            walker = walker->next;
        }
        return out;
    }

private:
    FreqPair<T>* head;

    bool isUnique(const T& item){
        return !searchPair(item);
    }

    FreqPair<T>* searchPair(const T& item){
        FreqPair<T>* walker = head;
        while(walker){
            if(walker->item.second == item)
                return walker;
            walker = walker->next;
        }
        return NULL;
    }
};

#endif // FREQUENCY_H
