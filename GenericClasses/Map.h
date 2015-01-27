#ifndef MAP_H
#define MAP_H
#include "ListTools.h"
#include "NodePair.h"
#include "GenericFunctions.h"

template <typename Key, typename V> //typename compare = Less<Key> for when the listtools are made generic
class Map{
private:
    Node<NodePair<Key,V> >* head;
public:
    Map():head(NULL){}
    Map(const Map<Key,V>& M):Map(){
        copy(M.head,head);
    }

    Map<Key,V>& operator =(const Map<Key,V>& M){
        destroy(head);
        copy(M.head,head);
        return *this;
    }

    ~Map(){
        destroy(head);
    }

    bool empty(){
        return isEmpty(head);
    }

    int size(){
        return count(head);
    }

    void insert(const Key& key, const V& value){
        NodePair<Key,V> N(key,value);
        insertSortedUnique(head,N);
    }

    void erase(const Key& key){
        NodePair<Key,V> N(key,NULL);
        deleteNode(head,N);
    }

    V& operator [](const Key& key){
        NodePair<Key,V> N(key,NULL);
        Node<NodePair<Key,V> >* result = ltf::search(head,N);
        if(result) return result->item.secondary;
    }

    template <typename K, typename I>
    friend std::ostream& operator <<(std::ostream& out, const Map<K,I>& M){
        traverse(M.head,True<NodePair<Key,V> >(),Print<NodePair<K,I> >(out),{});
        return out;
    }

};

#endif // MAP_H
