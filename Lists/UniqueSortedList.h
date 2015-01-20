#ifndef UNIQUESORTEDLIST_H
#define UNIQUESORTEDLIST_H
#include "ListTools.h"
#include "Iterator.h"

template <class T>
class UniqueSortedList{
public:
    UniqueSortedList() : head(NULL){}

    UniqueSortedList(const UniqueSortedList<T>& S){
        head = NULL;
        copy(S.head,head);
    }

    UniqueSortedList<T>& operator =(const UniqueSortedList<T>& S){
        destroy(head);
        copy(S.head,head);
        return *this;
    }

    ~UniqueSortedList(){
        destroy(head);
    }

    Iterator<T> insert(const T& item){
        if(!isUnique(item)) return NULL;
        Iterator<T> Temp(insertSorted(head,item));
        return Temp;
    }

    Iterator<T> search(const T& item){
        Iterator<T> Temp(ltf::search(head,item));
        return Temp;
    }

    T deleteAt(Iterator<T> Mark){
        return deleteNode(head,Mark.ptr);
    }

    Iterator<T> remove(Iterator<T> Mark){
        Iterator<T> Temp(removeNode(head,Mark.ptr));
        return Temp;
    }

    Iterator<T> begin() const{
        Iterator<T> Beginning(head);
        return Beginning;
    }

    Iterator<T> end() const{
        Iterator<T> Ending(ltf::end(head));
        return Ending;
    }
    T& operator [](int index){
        return at(head,index);
    }

    UniqueSortedList<T>& operator +=(const T& item){
        insert(item);
        return *this;
    }

    UniqueSortedList<T>& operator +=(const UniqueSortedList<T>& RS){
        Node<T>* temp = NULL;
        copy(RS.head,temp);
        while(temp){
            insert(temp->item);
            temp = temp->next;
        }
        return *this;
    }

    template <class Q>
    friend std::ostream& operator <<(std::ostream& out, const UniqueSortedList<Q>& L){
        Node<Q>* walker = L.head;
        while(walker){
            out << walker->item << " | ";
            walker = walker->next;
        }
        return out;
    }
private:
    Node<T>* head;

    bool isUnique(const T& item){
        return (ltf::search(head,item) ? false : true);
    }
};

#endif // UNIQUESORTEDLIST_H
