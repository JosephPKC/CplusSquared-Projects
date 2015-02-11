#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H
#include "Queue.h"
template <typename T>
class PriorityQueue : public Queue<T>{
private:
public:
    PriorityQueue() : Queue<T>::Queue(){}
    PriorityQueue(const PriorityQueue<T>& S) : Queue<T>::Queue(S){

    }

    PriorityQueue<T>& operator =(const PriorityQueue<T>& S){
        destroy(this->head);
        copy(S.head,this->head);
        return *this;
    }

    ~PriorityQueue(){
        destroy(this->head);
    }
    Iterator<T> push(const T& item){
        Iterator<T> Temp(insertSorted(this->head,item));
        return Temp;
    }
};
#endif // PRIORITYQUEUE_H
