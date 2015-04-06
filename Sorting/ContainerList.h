#ifndef CONTAINERLIST_H
#define CONTAINERLIST_H
#include "List.h"

template <typename Item>
class ContainerList{
protected:
    List<Item> _data;
    std::size_t _size;
public:
    ContainerList(){
        _size = 0;
    }

    void insert(const Item& entry){
        _data.insertE(entry);
        _size++;
    }

    void remove(const Item& entry){
        Iterator<Item> f = _data.search(entry);
        _data.remove(f);
        _size--;
    }

    friend std::ostream& operator <<(std::ostream& out, const ContainerList<Item> Other){
        out << Other._data;
        return out;
    }

    std::size_t size(){
        return _size;
    }
};

#endif // CONTAINERLIST_H
