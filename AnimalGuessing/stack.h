#ifndef STACK_H
#define STACK_H
#include "ListTools.h"
#include "Iterator.h"
template <class T>
class Stack{
public:
    Stack() : head(NULL){}
    Stack(const Stack<T>& S){
        destroy(head);
        copy(S.head,head);
    }

    ~Stack(){
        destroy(head);
    }

    Stack<T>& operator =(const Stack<T>& S){
        destroy(head);
        copy(S.head,head);
        return *this;
    }

    bool empty() const{
        return isEmpty(head);
    }

    int size() const{
        return count(head);
    }

    T top() const{
        if(isEmpty(head)) return NULL;
        return head->item;
    }

    Iterator<T> push(const T& item){
        Iterator<T> Temp(insertHead(head,item));
        return Temp;
    }

    T pop(){
//        if(isEmpty(head)) return NULL;
//        Iterator<T> Temp(removeHead(head));
//        return Temp;
        return removeHead(head)->item;
    }
    template <class U>
    friend std::ostream& operator <<(std::ostream& out, const Stack<U>& S){
        Node<U>* walker = S.head;
        while(walker){
            std::cout << walker->item << " | ";
            walker = walker->next;
        }
        return out;
    }

private:
    Node<T>* head;
};

#endif // STACK_H
