#ifndef HEAP_H
#define HEAP_H
#include "BinaryTreeTools.h"
#include <cmath>

template <typename Item, typename Order = Lesser<Item> >
class Heap{
private:
    Item* _hArray; //dynamic array //Change to TreeNode<Item>
    Order _Ord; //Whether it is a min heap or a max heap
    std::size_t _size;
    std::size_t _capacity;

    //gets max depth
    int depth(){
        if(_capacity <= 1) return 0; //if only root
        int i = 1;
        while(_capacity == pow(2,i) * 2 + 1) i++; //count depth
        return i;
    }

    //gets start index of last row
    int lastRowIndexStart(){
        return pow(2,depth()) - 1;
    }

    //gets max
    int max(int* a, int size, int pos){
        int max = a[pos];
        for(int i = pos + 1; i < size; i++)
            if(a[i] > max) max = a[i];
        return max;
    }

    //gets min (Move to utilities)
    int min(int* a, int size, int pos){
        int min = a[pos];
        for(int i = pos + 1; i < size; i++)
            if(a[i] < min) min = a[i];
        return min;
    }

    //ompares to items according to Order (Move)
    Item compare(const Item& a, const Item& b, Order Ord){
        return Order(a,b);
    }

    //Create new depth AKA allocate new memory to complete tree
    void createDepth(){
        if(_capacity == 0){ //If empty root
            _capacity++; //create the root
            Item* holder = new Item[_capacity];
            bst::copy(_hArray,holder,_size);
            delete[] _hArray;
            _hArray = holder;
            return;
        }
        int d = depth() + 1; //get depth
        _capacity += pow(2,d);
        Item* holder = new Item[_capacity];
        bst::copy(_hArray,holder,_size);
        delete[] _hArray;
        _hArray = holder;
    }

    //get parent of child
    int parent(int child){
        return ((child % 2 == 0) ?
                    ((child - 2) / 2) :
                    ((child - 1) / 2));
    }

    //get left child of parent
    int leftChild(int parent){
        return parent * 2 + 1;
    }

    //get right child of parent
    int rightChild(int parent){
        return parent * 2 + 2;
    }

    //recusrively fixes (called by fix)
    void recursiveFix(int i){
        int left = leftChild(i);
        int right = rightChild(i);
        int ex; //get the extrema (larger or smaller)
        if(left < _size && right < _size) //In case of no children
            ex = _Ord(_hArray[left],_hArray[right]) ? left : right;
        else if(left < _size && right >= _size)
            ex = left;
        else if(left >= _size && right < _size)
            ex = right;
        else return; //no children
        if(!_Ord(_hArray[i],_hArray[ex])){ //swap if necessary
            bst::swap(_hArray[i],_hArray[ex]);
            recursiveFix(ex); //keep going until we get to a leaf
        }
    }

    //fixes the heap (sorts it)
    void fix(){
        for(int i = _size - 1; i > 0; i -= 2){ //the root should be sorted by the time this done
            int ex;
            if(i % 2 == 0)
                ex = _Ord(_hArray[i],_hArray[i - 1]) ? i : i - 1;
            else ex = i;
            if(_Ord(_hArray[ex],_hArray[parent(ex)])) bst::swap(_hArray[ex],_hArray[parent(ex)]);
            recursiveFix(ex);
        }
    }



public:
    //Constructors
    Heap(std::size_t s = 0, std::size_t c = 0){
        _size = s;
        _capacity = c;
        _hArray = new Item[_capacity];
    }

    Heap(const Heap<Item,Order>& Other):Heap(Other._size,Other._capacity){
        copy(Other._hArray,_hArray,_size);
    }

    Heap<Item,Order>& operator =(const Heap<Item,Order>& Other){
        if(_hArray) delete _hArray;
        _size = Other._size;
        _capacity = Other._capacity;
        _hArray = new Item[_capacity];
        copy(Other._hArray,_hArray,_size);
    }

    ~Heap(){
        if(_hArray) delete _hArray;
    }

    //inserts an element (to the end and then fixes it)
    void insert(const Item& element){
        if(!hasRoom()){
            createDepth();
        }
        _hArray[_size] = element;
        _size++;
        fix();
    }

    //removes an element (swaps with last and then deletes, then fixes)
    void remove(const Item& element){
        int del = searchIndex(element);
        if(del == -1) return;
        bst::swap(_hArray[del],_hArray[_size - 1]);
        _size--;
        fix();
    }

    //searches for an element //gets pointer
    Item* search(const Item& element){
        Item* walker = _hArray;
        for(int i = 0; i < _size; walker++, i++)
            if(*walker == element) return walker;
        return NULL;
    }

    //search for the index
    int searchIndex(const Item& element){
        for(int i = 0; i < _size; i++)
            if(_hArray[i] == element) return i;
        return -1;
    }

    //gets smallest
    Item getMin(){
        return min(_hArray,_size,0);
    }

    //gets largest
    Item getMax(){
        return max(_hArray,_size,0);
    }

    //gets size
    std::size_t size(){
        return _size;
    }

    //gets capacity
    std::size_t capacity(){
        return _capacity;
    }

    //checks if there is room
    bool hasRoom(){
        return _size < _capacity;
    }

    //prints
    void print(){
        for(int i = 0; i < _size; i++)
            std::cout << _hArray[i] << " | ";
        for(int i = _size; i < _capacity; i++)
            std::cout << "EMPTY" << " | ";
        std::cout << std::endl;
    }
};

#endif // HEAP_H
