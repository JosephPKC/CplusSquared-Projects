#ifndef LISTTOOLS_H
#define LISTTOOLS_H
#include <iostream>
#include <cstdlib>
#include <ctime>

template <class T>
struct Node{
    Node<T>* next;
    T item;
    Node(){next = NULL;}
    Node(const T& item){this->item = item; next = NULL;}
    Node(const T& item, Node<T>* next){this->item = item; this->next = next;}
    friend std::ostream& operator <<(std::ostream& out, const Node& N){
        out << N.item;
        return out;
    }
};

namespace ltf{
    template <class T>
    void swap(T& a, T& b){
        T temp = a;
        a = b;
        b = temp;
    }

    template <class T>
    Node<T>* end(Node<T>* head){
        return atP(head,count(head) - 1);
    }

    template <class T>
    Node<T>* search(Node<T>* head, const T& item, int start){
        Node<T>* walker = atP(head,start);
        while(walker){
            if(walker->item == item) return walker; //== has to be defined for T
            walker = walker->next;
        }
        return NULL;
    }

    template <class T>
    Node<T>* search(Node<T>* head, const T& item){
        return search(head,item,0);
    }

    template <class T>
    void reverse(Node<T>* head){
        Node<T>* front = head;
        Node<T>* back = ltf::end(head);
        while((front != back->next) && (front != back)){
            ltf::swap(front->item,back->item);
            front = front->next;
            back = previousNode(head,back);
        }
    }

    template <class T>
    Node<T>* reverseNew(Node<T>* head){
        Node<T>* headR = NULL;
        copy(head,headR);
        reverse(headR);
        return headR;
    }

    template <class T>
    void print(Node<T>* head){
    //    if(isEmpty(head)){
    //        std::cout << "" << std::endl;
    //        return;
    //    }
        Node<T>* walker = head;
        while(walker){
            std::cout << walker->item << " | ";
            walker = walker->next;
        }
        std::cout << std::endl;
    }
}

template <class T>
Node<T>* insertHead(Node<T>*& head, const T& item){
    Node<T>* temp = new Node<T>(item,head);
    head = temp;
    return head; //?
}

template <class T>
Node<T>* insertBefore(Node<T>*& head, Node<T>* beforeThis, const T& item){
    if(isEmpty(head)) return NULL; //Most likely unecessary
    if(beforeThis == head) return insertHead(head,item); //Check if head before check previous
    Node<T>* prev = previousNode(head,beforeThis); //Takes care of node not in list
    if(!prev) return NULL; //Takes care of node not in list
    Node<T>* newNode = new Node<T>;
    newNode->item = item;
    newNode->next = beforeThis;
    prev->next = newNode;
    return newNode;
}

template <class T>
Node<T>* insertAfter(Node<T>* head, Node<T>* afterThis, const T& item){
    if(isEmpty(head)) return NULL;//Most likely unecessary
    if(!isNodeInList(head,afterThis)) return NULL;
    Node<T>* newNode = new Node<T>(item,afterThis->next);
    afterThis->next = newNode;
    return newNode; //return a pointer to the newly added node
}

template <class T>
Node<T>* insertSorted(Node<T>*& head, const T& item){
    Node<T>* walker = head;
    while(walker){
        if(item < walker->item) break;
        walker = walker->next;
    }
    if(!walker) insertEnd(head,item);
    insertBefore(head,walker,item);
    return previousNode(head,walker);
}

template <class T>
Node<T>* insertEnd(Node<T>*& head, const T& item){
    if(isEmpty(head)) return insertHead(head,item);
    return insertAfter(head,ltf::end(head),item);
}

template <class T>
Node<T>* removeHead(Node<T>*& head){
    Node<T>* temp = head;
    head = head->next;
    return temp;
}

template <class T>
Node<T>* removeNode(Node<T>*& head, Node<T>* removeThis){
    if(isEmpty(head)) return NULL; //Most likely unecessary
    if(!isNodeInList(head,removeThis)) return NULL;
    if(removeThis == head) return removeHead(head);
    Node<T>* before = previousNode(head,removeThis);
    Node<T>* temp = removeThis;
    before->next = removeThis->next;
    temp->next = NULL;
    return temp;
}

template <class T>
T deleteNode(Node<T>*& head, Node<T>* deleteThis){
    Node<T>* temp = removeNode(head,deleteThis);
    if(temp){
        T hold = temp->item;
        delete temp;
        return hold;
    }
//    return NULL; //return
}

template <class T>
T deleteNode(Node<T>*& head, const T& item){
    Node<T>* found = ltf::search(head,item);
    if(!found) return NULL; //return what
    return deleteNode(head,found);
}



template <class T>
T& at(Node<T>* head, int index){
//    if(!(index >= count(head) && index < 0)) //exception?
    return atP(head,index)->item;
}

template <class T>
Node<T>* atP(Node<T>* head, int index){
    if(index < 0) return NULL;
    if(index >= count(head)) return NULL;
    Node<T>* walker = head;
    for(int i = 0; i < index; i++) walker = walker->next;
    return walker;
}

template <class T>
int count(Node<T>* head){
    int i = 0;
    Node<T>* walker = head;
    while(walker){
        i++;
        walker = walker->next;
    }
    return i;
}



template <class T>
void deleteRepeats(Node<T>* head){
    for(int i = 0; i < count(head); i++)
        deleteRepeatsOf(head,at(head,i));
}

template <class T>
Node<T>* deleteRepeatsNew(Node<T>* head){
    Node<T>* headU = NULL;
    copy(head,headU);
    deleteRepeats(headU);
    return headU;
}

template <class T>
void selectionSort(Node<T>* head){
    Node<T>* walker = head;
    while(walker){
        Node<T>* smallest = min(walker);
        ltf::swap(smallest->item,walker->item);
        walker = walker->next;
    }
}

template <class T>
Node<T>* selectionSortNew(Node<T>* head){
    Node<T>* headS = NULL;
    copy(head,headS);
    selectionSort(headS);
    return headS;
}

template <class T>
void shuffle(Node<T>* head){
    int randMax = count(head) - 1;
    int numLoops = rand() % count(head) + (count(head) / 2) + 1;
    for(int i = 0; i < numLoops; i++){
        Node<T>* randNodeA = atP(head,rand() % randMax);
        Node<T>* randNodeB = atP(head,rand() % randMax);
        ltf::swap(randNodeA->item,randNodeB->item);
    }
}

template <class T>
void copy(Node<T>* headS, Node<T>*& headD){
    destroy(headD);
    for(int i = 0; i < count(headS); i++)
        insertHead(headD,at(headS,i));
    ltf::reverse(headD);
}

template <class T>
Node<T>* merge(Node<T>* headA, Node<T>* headB){
    Node<T>* headM = NULL;
    headM = appendNew(headA,headB);
    selectionSort(headM);
    return headM;
}

template <class T>
Node<T>* mergeUnique(Node<T>* headA, Node<T>* headB){
    Node<T>* headM = merge(headA,headB);
    deleteRepeats(headM);
    return headM;
}

template <class T>
void split(Node<T>*& head, Node<T>*& headA, Node<T>*& headB, int index){
//    Node<T>* splitHere = atP(head,index);
//    if(!splitHere) return;
//    splitNode(head,headA,headB,splitHere);
    splitNode(head,headA,headB,atP(head,index));
}

template <class T>
void splitItem(Node<T>*& head, Node<T>*& headA, Node<T>*& headB, const T& item){
//    Node<T>* splitHere = search(head,item);
//    if(!splitHere) return;
////    headA = head;
////    headB = splitHere->next;
////    splitHere->next = NULL;
////    head = NULL;
//    splitNode(head,headA,headB,splitHere);
    splitNode(head,headA,headB,ltf::search(head,item));
}

template <class T>
void splitNode(Node<T>*& head, Node<T>*& headA, Node<T>*& headB, Node<T>* splitHere){
    if(!isNodeInList(head,splitHere)) return;
    headA = head;
    headB = splitHere->next;
    splitHere->next = NULL;
    head = NULL;
}

template <class T>
Node<T>* append(Node<T>* headS, Node<T>*& headD){
    Node<T>* appendHere = ltf::end(headD);
    Node<T>* copyS = NULL;

    copy(headS,copyS);
    appendHere->next = copyS;
    return appendHere->next;
}

template <class T>
Node<T>* appendNew(Node<T>* headS, Node<T>* headD){
    Node<T>* headA = NULL;
    copy(headD,headA);
    append(headS,headA);
    return headA;
}

template <class T>
Node<T>* subtract(Node<T>* headA, Node<T>* headB){
    //subtract items in B from A
    Node<T>* headBUnique = deleteRepeatsNew(headB);
    Node<T>* walker = headBUnique;
    Node<T>* headS = NULL;
    copy(headA,headS);
    while(walker){
        deleteInstanceOf(headS,at(headBUnique,index(headBUnique,walker)));
        walker = walker->next;
    }
    return headS;
}

template <class T>
void deleteInstanceOf(Node<T>*& head, const T& item){
    Node<T>* find = ltf::search(head,item);
    while(find){
        int i = index(head,find);
        deleteNode(head,find);
        find = ltf::search(head,item, i);
    }
}

template <class T>
void deleteRepeatsOf(Node<T>* head, const T& item){
    Node<T>* uniqueLoc = ltf::search(head,item);
    Node<T>* find = ltf::search(head,item,index(head,uniqueLoc) + 1);
    while(find){
        int i = index(head,find);
        deleteNode(head,find);
        find = ltf::search(head,item, i);
    }
}

template <class T>
Node<T>* deleteRepeatsOfNew(Node<T>* head, const T& item){
    Node<T>* headU = NULL;
    copy(head,headU);
    deleteRepeatsOf(headU,item);
    return headU;
}

template <class T>
int index(Node<T>* head, Node<T>* indexHere){
    for(int i = 0; i < count(head); i++)
        if(indexHere == atP(head,i)) return i;
    return -1;
}

template <class T>
void destroy(Node<T>*& head){
    while(head) deleteNode(head,head);
    head = NULL;
}

template <class T>
Node<T>* min(Node<T>* head){
    Node<T>* walker = head->next;
    Node<T>* min = head;
    while(walker){
        if(walker->item < min->item) min = walker;
        walker = walker->next;
    }
    return min;
}

template <class T>
Node<T>* max(Node<T>* head){
    Node<T>* walker = head;
    Node<T>* max = head;
    while(walker){
        if(walker->item > max->item) max = walker;
        walker = walker->next;
    }
    return max;
}

template <class T>
Node<T>* previousNode(Node<T>* head, Node<T>* beforeThis){
    if(beforeThis == head) return NULL;
    if(!isNodeInList(head,beforeThis)) return NULL;
    Node<T>* walker = head;
    while(walker){
        Node<T>* temp = walker;
        walker = walker->next;
        if(walker == beforeThis) return temp;
    }
}

template <class T>
bool isNodeInList(Node<T>* head, Node<T>* checkThis){
    Node<T>* walker = head;
    while(walker){
        if(walker == checkThis) return true;
        walker = walker->next;
    }
    return false;
}



template <class T>
bool isEmpty(Node<T>* head){
    return head == NULL;
}





#endif // LISTTOOLS_H
