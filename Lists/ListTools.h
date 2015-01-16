#ifndef LISTTOOLS_H
#define LISTTOOLS_H
#include <iostream>
template <class T>
struct Node{
    Node* next;
    T item;
    Node(const T& item){this->item = item;}
    Node(const T& item, Node* next){this->item = item; this->next = next;}
    friend std::ostream& operator <<(std::ostream& out, const Node& N){
        out << N.item;
        return out;
    }
};

template <class T>
Node<T>* insertHead(Node<T>*& head, const T& item){
    Node<T>* temp = new Node<T>(item,head);
    head = temp;
    return head; //?
}

template <class T>
Node<T>* insertBefore(Node<T>*& head, Node<T>* beforeThis, const T& item){

}

template <class T>
Node<T>* insertAfter(Node<T>* head, Node<T>* afterThis, const T& item){

}

template <class T>
Node<T>* insertSorted(Node<T>*& head, const T& item){

}

#endif // LISTTOOLS_H
