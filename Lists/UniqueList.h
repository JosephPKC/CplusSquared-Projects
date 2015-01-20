#ifndef UNIQUELIST_H
#define UNIQUELIST_H
#include "Iterator.h"
#include "ListTools.h"
template <class T>
class UniqueList{
public:
    UniqueList() : head(NULL){}

    UniqueList(const UniqueList<T>& S){
        head = NULL;
        copy(S.head,head);
    }

    UniqueList<T>& operator =(const UniqueList<T>& S){
        destroy(head);
        copy(S.head,head);
        return *this;
    }

    ~UniqueList(){
        destroy(head);
    }

    Iterator<T> insertH(const T& item){
        if(!isUnique(item)) return NULL;
        Iterator<T> Temp(insertHead(head,item));
        return Temp;
    }

    Iterator<T> insertA(Iterator<T> Mark, const T& item){
        if(!isUnique(item)) return NULL;
        Iterator<T> Temp(insertAfter(head,Mark.ptr,item));
        return Temp;
    }

    Iterator<T> insertB(Iterator<T> Mark, const T& item){
        if(!isUnique(item)) return NULL;
        Iterator<T> Temp(insertBefore(head,Mark.ptr,item));
        return Temp;
    }

    Iterator<T> insertE(const T& item){
        if(!isUnique(item)) return NULL;
        Iterator<T> Temp(insertEnd(head,item));
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
        if(isUnique(item)) Mark.ptr->item = item;
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

    UniqueList<T>& operator +=(const T& item){
        insertE(item);
        return *this;
    }

    UniqueList<T>& operator +=(const UniqueList<T>& RS){
        Node<T>* temp = NULL;
        copy(RS.head,temp);
        while(temp){
            insertE(temp->item);
            temp = temp->next;
        }
        return *this;
    }

    template <class Q>
    friend std::ostream& operator <<(std::ostream& out, const UniqueList<Q>& L){
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

#endif // UNIQUELIST_H
