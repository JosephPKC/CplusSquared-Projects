#ifndef LIST_H
#define LIST_H
#include "ListTools.h"
#include "Iterator.h"
template <class T>
class List{
public:
    List() : head(NULL){}
    List(const List<T>& S){
        head = NULL;
        copy(S.head,head);
    }

    List<T>& operator =(const List<T>& S){
        destroy(head);
        copy(S.head,head);
        return *this;
    }

    ~List(){
        destroy(head);
    }

    T& operator [](int index){
        return at(head,index);
    }

    List<T>& operator +=(const T& item){
        insertEnd(head,item);
        return *this;
    }

    List<T>& operator +=(const List<T>& RS){
        Node<T>* temp = NULL;
        copy(RS.head,temp);
        append(temp,head);
        return *this;
    }

//    template <class Q>
    friend std::ostream& operator <<(std::ostream& out, const List<T>& L){
        Node<T>* walker = L.head;
        while(walker){
            out << walker->item << " | ";
            walker = walker->next;
        }
        return out;
    }
    std::size_t length(){
        int i = 0;
        if(Empty()) return i; //If empty, return 0
        Iterator<T> walker = begin(); //Beginning
        Iterator<T> e = end(); //End
        e++; //Go to NULL
        while(walker != e){
            i++;
            walker++;
        }
        return i;
    }

    Iterator<T> insertH(const T& item){
        Iterator<T> Temp(insertHead(head,item));
        return Temp;
    }

    Iterator<T> insertA(Iterator<T> Mark, const T& item){
        Iterator<T> Temp(insertAfter(head,Mark.ptr,item));
        return Temp;
    }

    Iterator<T> insertB(Iterator<T> Mark, const T& item){
        return insertA(previous(Mark),item);
    }

    Iterator<T> insertE(const T& item){
//        return insertA(end(),item);
        return insertEnd(head,item);
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

    void print() const{
        std::cout << *this << std::endl;
    }

    Iterator<T> search(const T& item){
        Iterator<T> Temp(ltf::search(head,item));
        return Temp;
    }

    void reverse(){
        ltf::reverse(head);
    }

    List<T> reverseNew(){
        List<T> ListR = *this;
        ListR.reverse();
        return ListR;
    }

    bool Empty() const{
        return isEmpty(head);
    }

private:
    Node<T>* head;

    Iterator<T> previous(Iterator<T> Mark){
        Iterator<T> Prev(previousNode(head,Mark.ptr));
        return Prev;
    }
};
#endif // LIST_H
