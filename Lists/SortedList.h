#ifndef SORTEDLIST_H
#define SORTEDLIST_H
#include "Iterator.h"
#include "ListTools.h"
template <class T>
class SortedList{
public:
    SortedList() : head(NULL){}

    SortedList(const SortedList<T>& S){
        head = NULL;
        copy(S.head,head);
    }

    SortedList<T>& operator =(const SortedList<T>& S){
        destroy(head);
        copy(S.head,head);
        return *this;
    }

    ~SortedList(){
        destroy(head);
    }

    Iterator<T> insert(const T& item){
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

    void modify(Iterator<T> Mark, const T& item){
        if(!isNodeInList(head,Mark.ptr)) return;
        Mark.ptr->item = item;
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

    SortedList<T>& operator +=(const T& item){
        insert(item);
        return *this;
    }

    SortedList<T>& operator +=(const SortedList<T>& RS){
        Node<T>* temp = NULL;
        copy(RS.head,temp);
        while(temp){
            insert(temp->item);
            temp = temp->next;
        }
        return *this;
    }

    template <class Q>
    friend std::ostream& operator <<(std::ostream& out, const SortedList<Q>& L){
        Node<Q>* walker = L.head;
        while(walker){
            out << walker->item << " | ";
            walker = walker->next;
        }
        return out;
    }
private:
    Node<T>* head;
};

#endif // SORTEDLIST_H
