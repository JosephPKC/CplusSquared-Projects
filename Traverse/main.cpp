#include <iostream>

using namespace std;

template <typename T>
struct Node{
    T item;
    Node<T>* next;
    Node(const T& item, Node<T>* next){this->item = item; this->next = next;}
    friend ostream& operator <<(ostream& out, const Node<T> right){
        out << right.item;
        return out;
    }
    Node<T>& operator ++(void){
        item++;
        return *this;
    }
    Node<T> operator ++(int){
        Node<T> temp = *this;
        item++;
        return temp;
    }

};

template <typename T, typename action>
void traverseNR(Node<T>* head, action act){

    while(head){
        act(*head);
        head = head->next;
    }
}

template <typename T>
struct Printer{
    void operator()(const T& item){
        cout << item << " ";
    }
};

template <typename T>
struct Incrementer{
    void operator()(T& item){
        item++;
    }
};

template <typename T>
struct Adder{
    T e;
    Add(T e){this->e = e;}
    void operator ()(T& e) const {e += this.e;}

template <int val>
void setValue(int& e){

}

template <typename T>
struct True{
    bool operator()(const T& left, const T& right){
        return true;
    }
};

//template <typename T, typename action, typename compare, typename R>
//R traverseR(Node<T>* head, action act, compare cmp){
//    Node<T>* walker = head;
//    R data;
//    while(walker){
//        if(cmp) data = act(*walker);
//        walker = walker->next;
//    }
//    return data;
//}

int main()
{

    Node<int>* head = new Node<int>(1,NULL);
    head->next = new Node<int>(2,new Node<int>(3,new Node<int>(4,new Node<int>(5,NULL))));
    traverseNR(head,Printer<Node<int> >()); cout << endl;
    traverseNR(head,Incrementer<Node<int> >());
    traverseNR(head,Printer<Node<int> >()); cout << endl;
    return 0;
}
