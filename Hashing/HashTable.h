#ifndef HASHTABLE_H
#define HASHTABLE_H
#include <iostream>
template <typename Item>
struct Encode{
    int operator ()(const Item& I){
        return ;
    }
};
struct Hash{
    int _modulus;
    int _multiplier;
    int _base;
    std::size_t operator ()(int key){
        return _multiplier * key % _modulus + _base;
    }
    Hash(int modulus = 1, int multiplier = 1, int base = 0){
        _modulus = modulus;
        _multiplier = multiplier;
        _base = base;
    }
};

template <typename Item>
class HashTable{
private:
    Item* _data = nullptr; //For chained hashing, it will be an array of linked lists of items
                            //CollisionHash will just add the item to the appropriate linked list
    int _size;
    int _capacity;

    template <typename Encode>
    int code(const Item& entry, Encode E){
        //Turn the item into an integer key
        return E(entry);
    }

    template <typename Hash>
    std::size_t hash(int key, Hash H){
        //Turn the integer key into an index
        return H(key);
    }

    bool collision(std::size_t index){
        //If index is not vacant
        return !isVacant(index);
    }

    bool isVacant(std::size_t index){
        //vacancy of the index

    }

    void handleCollision(const Item& entry, std::size_t index){
        //handle the collision in the index
        bool empty = false;
        for(int j = 0; j < _capacity; j++){
            if(isVacant(j)) empty = true;
        }
        if(!empty) return;
        std::size_t i = index;
        while(collision(i)){
//            i = hash(code(entry),Hash(,-1,));
        }
    }

public:
    HashTable(std::size_t capacity = 0){
        //Create the Array of Capacity Size
        //Set the Values of the Array to NOTUSED???
        //Set size to zero
        //set capacity to capacity
        _data = new Item[capacity];
        //Initialize array to UNUSED
        _size = 0;
        _capacity = capacity;
    }
    HashTable(const HashTable<Item>& Other){
        //Create Array
        //Copy Other's Array to This Array
        //Copy Values of size and capacity
        _data = new Item[Other._capacity];
        //copy array from Other to _data
        _size = Other._size;
        _capacity = Other._capacity;
    }
    HashTable<Item>& operator =(const HashTable<Item>& Other){
        //Same as copy constructor
        _data = new Item[Other._capacity];
        //copy array
        _size = Other._size;
        _capacity = Other._capacity;
        return *this;
    }
    ~HashTable(){
        delete[] _data;
    }

    void insert(const Item& entry){
        //If there is enough room
        //Convert entry to a key
        //Hash the key
        //Check for Collision
        //Handle Collisions
        //Insert into Array
        if(_size >= _capacity) return;
        int key = code(entry,Encode());
        std::size_t index = hash(key,Hash(_capacity));
        index = handleCollision(entry,index);
        _data[index] = entry;
    }

    void remove(int key){
        //Hash the key
        //Check index for vacancy
        //remove the item
        //Set vacancy
    }

    Item* search(int key){
        //Hash the key
        //Check index for vacancy
        //return pointer
        //or return nullptr
    }

    std::size_t size() const{
        return _size; //This is the number of items in the array
    }

    std::size_t cap() const{
        return _capacity; //This is the amount of items that can fit in the table
    }

    bool isPresent(int key){
        //is vacant?
    }


#endif // HASHTABLE_H

    /*
     * Constructor
     * Insert
     * Remove
     * Search
     * Size
     * Check Index
     * Capacity
     *
     * Hash
     * Double Hash
     * Check Collision
     * Handle Collision
     */

//private:
//    static const int _NEVER_USED = -1; //Value for never used
//    static const int _PREVIOUSLY_USED = -2; //Value for previously used
//    Item _data[_capacity]; //the array of items
//    std::size_t _used; //how much space is used
//    std::size_t _capacity; //Space allocated


//    std::size_t hash(int key) const{ //Convert the item into some integer
//        return key % capacity;
//    }
//    int getCode(const Item& entry);
////    std::size_t nextIndex(std::size_t index) const; //gets the next index (linear probe collision)
//    std::size_t collisionHash(int key) const{
//        //do collision hash
//    }
//    void findIndex(int key, bool& found, std::size_t& index) const{

//    }
//    bool neverUsed(std::size_t index) const{

//    }
//    bool isVacant(std::size_t index) const; //check if an index is vacant
//public:
//    HashTable(std::size_t capacity = 0);

//    void insert(const Item& entry){
//        if(_used >= _capacity) return;
//        std::size_t index = hash(getCode(entry));
//        while(!isVacant(index)){
//            //collisionHash
//        }
//        _data[index] = entry;
//        //set index to not vacant
//    }

//    void remove(int key){
//        std::size_t index = hash(key);
//        //delete the item
//        //set index to vacant
//    }

//    bool isPresent(int key) const{
//        bool found;
//        Item result;
//        find(key,found,result);
//        return found;
//    }
//    void find(int key, bool& found, Item& result) const{
//        std::size_t index = hash(key);
//        if(!isVacant(index)){
//            result = _data[index];
//            found = true;
//        }
//        else
//            found = false;

//    }
//    std::size_t size() const{
//        return _used;
//    }
//    std::size_t cap() const{
//        return _capacity;
//    }
