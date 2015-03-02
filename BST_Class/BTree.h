#ifndef BTREE_H
#define BTREE_H
#include "Set.h"
/*
 * Rules of the B Tree
 * -The root may have as few as one entry (or even no entries if it also has no children);
 * every other node has at least MINIMUM entries
 * -The maximum number of entries in a node is twice the value of MINIMUM
 * The entries of each B-tree node are stored in a partially filled array,
 * sorted from the smallest entry (at index 0) to the largest entry (at the final used position of the array)
 * -The number of subtrees below a nonleaf node is always on more than the number of entries in the node
 * -For any nonleaf node:
 * An entry at index i is greater than all the entries in the subtree number i of the node, and
 * An entry at index i is less than all the entires in subtree number i + 1 of the node.
 * -Every leaf in a B tree has the same depth
 */

template <typename Item>
class BTree{
private:
    Set<Item>* _root; //the root
public:
    BTree(){ //Default
        _root = new Set<Item>;
    }

    BTree(const BTree<Item>& Source){ //Copy
        _root = new Set<Item>(Source._root);
    }

    ~BTree(){ //Destructor
        _root->clear();
        _root = NULL;
    }

    BTree<Item>& operator =(const BTree<Item>& Source){ //Assignment
        _root->clear();
        _root =  new Set<Item>(Source._root);
        return *this;
    }

    void insertT(const Item& element){ //insert element
        _root->insert(element);
    }

    void removeT(const Item& target){ //remove target
        _root->erase(target);
    }

    Set<Item>* search(const Item& target) const{ //search for target
        return _root->search(target);
    }

    bool empty() const{ //get empty
        return _root->empty();
    }

    friend std::ostream& operator <<(std::ostream& out, const BTree<Item>& Source){ //output
        out << *Source._root;
        return out;
    }

    void clear(){ //clear
        _root->clear();
    }

};

#endif // BTREE_H
