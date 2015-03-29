#ifndef HTABLE_H_INCLUDED
#define HTABLE_H_INCLUDED
#include <iostream>
#include "List.h"

//Attempt at turning an object to an integer
template <typename Item>
struct Encode{ //Find a way to turn objects into integers
    int operator ()(const Item& I){
        return I % 7 << 2; //Define modulus for the item
    }
};
//General Hashing Function
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
class HTable{
private:
    List<Item>* _data = nullptr; //Change to SortedList?
    int _size; //size of the list
    int _capacity; //Capacity

    //Copy the source to destination
    template <typename Type>
    void copy(Type* source, Type* dest, std::size_t sourceLen){
        for(std::size_t i = 0; i < sourceLen; i++){
            dest[i] = source[i];
        }
    }
    //Turns the item entry into an integer code
    template <typename Encode>
    int code(const Item& entry, Encode E) const{
        //Turn the item into an integer key
        return E(entry);
    }
    //Hashes the integer key to an index
    template <typename Hash>
    std::size_t hash(int key, Hash H) const{
        //Turn the integer key into an index
        return H(key);
    }
    //Checks for collision at the index
    bool collision(std::size_t index) const{
        //If index is not vacant //Other reasons for collision?
        return !isVacant(index);
    }
    //Checks if the index is vacant
    bool isVacant(std::size_t index) const{
        if(_data[index].Empty()) return true;
        return false;
    }
    //Handles the collision at the index with the item entry
    std::size_t handleCollision(const Item& entry, std::size_t index){
        //handle the collision in the index
        _data[index].insertE(entry); //This is just chained hashing //Originally it was double hash
        return index;
    }
    //Gets the linked list that is connected to the key
    List<Item>* getList(int key) const{
        std::size_t index = hash(key,Hash(_capacity));
        if(isVacant(index)) return nullptr;
        return &_data[index];
    }

public:
    HTable(std::size_t capacity = 0){
        //Create the Array of Capacity Size
        //Set the Values of the Array to NOTUSED???
        //Set size to zero
        //set capacity to capacity
        _data = new List<Item>[capacity];
        //Initialize array to UNUSED
        _size = 0;
        _capacity = capacity;
    }
    HTable(const HTable<Item>& Other){
        //Create Array
        //Copy Other's Array to This Array
        //Copy Values of size and capacity
        _data = new List<Item>[Other._capacity];
        copy(Other._data,_data,Other._capacity);
        _size = Other._size;
        _capacity = Other._capacity;
    }
    HTable<Item>& operator =(const HTable<Item>& Other){
        //Same as copy constructor
        _data = new List<Item>[Other._capacity];
        copy(Other._data,_data,Other._capacity);
        _size = Other._size;
        _capacity = Other._capacity;
        return *this;
    }
    ~HTable(){
        delete[] _data;
    }
    //Insert an entry to the list
    bool insert(const Item& entry){
        //If there is enough room
        //Convert entry to a key
        //Hash the key
        //Check for Collision
        //Handle Collisions
        //Insert into Array
        if(_size >= _capacity) return false;
        //Return false if not unique?
        int key = code(entry,Encode<Item>());
        std::size_t index = hash(key,Hash(_capacity));
        if(collision(index)){
            handleCollision(entry,index);
        }
        else{
            _data[index].insertH(entry);
            _size++;
        }
        return true;
    }
    //Remove an item from the list using the key
    bool remove(int key){
        using namespace std;
        //Hash the key
        //Check index for vacancy
        //remove the item
        //Set vacancy
        List<Item>* result = getList(key);
        if(!result) return false;

        Iterator<Item> walker = result->begin();
        Iterator<Item> end = result->end();
        end++;
        while(walker != end){
           if(code(*walker,Encode<Item>()) == key){
               result->deleteAt(walker);
               return true;
           }
           walker++;
        }
        return false; //Did not find the item with the key
    }
    //Searches the key in the list
    Item* search(int key) const{
        //Hash the key
        //Check index for vacancy
        //return pointer
        //or return nullptr
        List<Item>* result = getList(key);
        for(int i = 0; result[i] != *result->end(); i++){
           if(code(result[i],Encode<Item>()) == key)
               return &result[i];
        }
        return nullptr;
    }
    //Gets the size
    std::size_t size() const{
        return _size; //This is the number of items in the array
    }
    //Gets the capacity
    std::size_t cap() const{
        return _capacity; //This is the amount of items that can fit in the table
    }
    //CHecks if the key is present
    bool isPresent(int key) const{
        return !isVacant(hash(key,Hash(_capacity)));
    }
    //Prints the table
    template <typename Item2>
    friend std::ostream& operator <<(std::ostream& out, const HTable<Item2>& Other){
        for(int i = 0; i < Other._capacity; i++){
            out << "{ ";
            if(Other.isVacant(i)) out << "VACANT";
            else out << Other._data[i];
            out << " }|";
        }
        return out;
    }
    //The Encoder that the table uses
    int key(const Item& entry) const{
        return code(entry,Encode<Item>());
    }

};
#endif // HTABLE_H

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
