#ifndef HEAP_H
#define HEAP_H
#include "BinaryTreeTools.h"

template <typename Item, typename Order = Lesser<Item> >
class Heap{
private:
    Item* _hArray; //dynamic array //Change to TreeNode<Item>
    bool* _aArray; //??? do we need this?
    Order _Ord; //Whether it is a min heap or a max heap

    std::size_t _size;
    std::size_t _capacity;
    void createDepth();
    template <typename Type>
    void copy(Type* source, Type* dest, std::size_t size){ //Does not check for size//Make sure it is valid and theres room beforehand
        for(int i = 0; i < size; i++)
            dest[i] = source[i];
    }

    int parent(int child){
        return ((child % 2 == 0) ?
                    ((child - 2) / 2) :
                    ((child - 1) / 2));
    }

    int leftChild(int parent){
        return parent * 2 + 1;
    }

    int rightChild(int parent){
        return parent * 2 + 2;
    }
    void fix();//Array arg, Order arg

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

    void insert(const Item& element){
        //Add to the end
        if(!hasRoom()) //create More Room
        _hArray[_size] = //create element here
        //fix the array

    }

    void remove(const Item& element){
        //search the element
        //swap element with the last element
        //delete last element
        //fix the array
    }

    Item* search(const Item& element){
        //search the array for element
    }

    Item getMin(){
        //Depends on the order
    }

    Item getMax();

    std::size_t size(){
        return _size;
    }

    std::size_t capacity(){
        return _capacity;
    }

    bool hasRoom();
};

#endif // HEAP_H
