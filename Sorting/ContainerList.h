#ifndef CONTAINERLIST_H
#define CONTAINERLIST_H
#include "List.h"
//Container Class for List
template <typename Item>
class ContainerList{
protected:
    List<Item> _data; //The List of Items
    std::size_t _size; //The Size of the List
public:
    //Default Constructor
    ContainerList(){
        _size = 0; //Just set size to zero
    }

    ContainerList(const List<Item>& L){
        _data = L;
        _size = _data.length();

    }

    List<Item> list(){
        return _data;
    }

    //Insert an Item into the List
    void insert(const Item& entry){
        _data.insertE(entry); //Insert at the end of the list
        _size++; //Increase the size
    }

    //Remove an Item from the list
    void remove(const Item& entry){
        Iterator<Item> f = _data.search(entry); //Search for the item
        _data.remove(f); //Remove the item
        _size--; //Decrease the size
    }

    //output
    friend std::ostream& operator <<(std::ostream& out, const ContainerList<Item> Other){
        out << Other._data; //Print the list
        return out;
    }

    //Return the size
    std::size_t size(){
        return _size;
    }
};

#endif // CONTAINERLIST_H
