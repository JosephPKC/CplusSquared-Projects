#ifndef QUEUE_H
#define QUEUE_H
#include "Iterator.h"
//#include "ListTools.h"
template <class T>
class Queue{
public:
    Queue(): head(NULL){}

    Queue(const Queue<T>& S){
//        destroy(head);
        head = NULL;
        copy(S.head,head);
    }

    Queue<T>& operator =(const Queue<T>& S){
        destroy(head);
        copy(S.head,head);
        return *this;
    }

    ~Queue(){
        destroy(head);
    }

    bool empty() const{
        return isEmpty(head);
    }

    int size() const{
        return count(head);
    }

    T front() const{
//        if(empty()) return NULL;
        return head->item;
    }

    T back() const{
//        if(empty()) return NULL;
        return ltf::end(head)->item;
    }

    Iterator<T> push(const T& item){
        Iterator<T> Temp(insertEnd(head,item));
        return Temp;
    }

    T pop(){
//        if(empty()) return NULL;
        return deleteNode(head,head);
    }

//    template <class U>
//    friend std::ostream& operator <<(std::ostream& out, const Queue<U>& S){
//        Node<U>* walker = S.head;
//        while(walker){
//            std::cout << walker->item << " | ";
//            walker = walker->next;
//        }
//        return out;
//    }

private:
    Node<T>* head;
};

#endif // QUEUE_H
