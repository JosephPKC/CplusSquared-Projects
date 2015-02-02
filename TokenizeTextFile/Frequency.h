#ifndef __FREQUENCY_H_INCLUDED__
#define __FREQUENCY_H_INCLUDED__
#include "ListTools.h"
#include "GenericFunctions.h"
//#include "NodePair.h"

template <typename T>
class Frequency{
private:
    Node<NodePair<T,size_t> >* head;

public:
    //Constructors
    Frequency() : head(NULL){}
    //The Big Three
    Frequency(const Frequency<T>& S) : Frequency(){
        copy(S.head,head);
    }

    Frequency<T>& operator =(const Frequency<T> S){
        destroy(head);
        copy(S.head,head);
        return *this;
    }

    ~Frequency(){
        destroy(head);
    }
    //Checks if the list is empty
    bool empty(){
        return isEmpty(head);
    }
    //Gets the size of the list
    int size(){
        return count(head);
    }
    //Inserts an item into the list
    //The List is sorted
    //If the item is not unique, then it will increment the frequency of that item
    void insert(const T& item){
        NodePair<T,size_t> N(item,1); //Create a NodePair of frequency 1
        Node<NodePair<T,size_t> >* result = insertSortedUnique(head,N);
        //Insert Sorted Unique
        if(!result) traverse(head,Equal<NodePair<T,size_t> >(),Increment<NodePair<T,size_t> >(),N);
    }
    //Erases the item from the list
    void erase(const T& item){
        NodePair<T,size_t> N(item,0);
        deleteNode(head,N); //deleteNode will check if the node is in the list
    }
    //Gets the frequency at the key
    int getFreqAt(T key){
        Node<NodePair<T,size_t> >* found = ltf::search(head,NodePair<T,size_t>(key,0));
        if(found){ //If the key is in the list
            NodePair<T,size_t> N = at(head,index(head,found));
            return N.secondary;
        }
        else return -1; //-1 for an invalid frequency, i.e. key is not in the list
    }
    //Gets the key at the index
    T& operator [](int index){
        NodePair<T,size_t> N = at(head,index);
        return N.primary;
    }
    //insertion operator for outputs
    template <typename R>
    friend std::ostream& operator <<(std::ostream& out, const Frequency<R>& F){
        traverse(F.head,True<NodePair<T,size_t> >(),Print<NodePair<R,size_t> >(out),{});
        return out;
    }
    //Sorts the list by frequency
    //TODO use the generic traversal in listtools
    Frequency<T> sortByFreq(){
        Frequency<T> sorted;
        copy(head,sorted.head);
        Node<NodePair<T,size_t> >* walker = sorted.head;
        while(walker){
            Node<NodePair<T,size_t> >* large = max(walker,GreaterFreq<T,size_t>());
            ltf::swap(large->item,walker->item);
            walker = walker->next;
        }
        return sorted;
    }
};
#endif // FREQUENCY_H




