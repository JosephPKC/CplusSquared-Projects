#ifndef SET_H
#define SET_H
#include "BinaryTreeTools.h"
using namespace std; //Remove later
template <typename Item>
class Set{
private:
    static const std::size_t _MINIMUM = 1;
    static const std::size_t _MAXIMUM = 2 * _MINIMUM;
    std::size_t _size; //size of the array
    Item _data[_MAXIMUM + 1]; //the array of items
    std::size_t _subSize; //size of the subset
    Set* _subset[_MAXIMUM + 2]; //array of subsets

    //Checks if the node is a leaf
    bool isLeaf() const{
        return _subSize == 0;
    }

    //Loosely inserts into the BTree (Allows for the root to have one more than MAX elements
    bool looseInsert(const Item& element){
        int index = firstGE(element);
        if((index != _size) && !(element < _data[index]))//If found at root
            return false;
        else if(isLeaf()){ //If not found and root has no children
            bst::shiftRight(_data,_size,index); //Add the new element
            _data[index] = element;
            return true;
        }
        else{ //If not found and root has children
            bool rec = _subset[index]->looseInsert(element); //recursive call on the very last subtree
            if(_subset[index]->_size > _MAXIMUM)
                fixExcess(index); //Fix excess as there is MAX + 1 elements in subtree
            return rec;
        }
    }

    //Loosely erases target (Allows for the root to have one less than MIN elements)
    bool looseErase(const Item& target){
        int index = firstGE(target);
        if((index == _size) && isLeaf()) return false; //If root is a leaf and not found
        else if((index < _size) && (target == _data[index]) && isLeaf()){ //If root is leaf and found
            bst::shiftLeft(_data,_size,index); //remove the element
            return true;
        }
        else if(((index == _size) || (index < _size) &&
                 (target != _data[index])) && !isLeaf()){ //If root is not leaf and not found
            bool rec = _subset[index]->looseErase(target); //recusrive
            if(_subset[index]->_size < _MINIMUM) fixShortage(index); //fix
            return rec;
        }
        else if((index < _size) && (target == _data[index]) && !isLeaf()){ //If found and not leaf
            _subset[index]->removeBiggest(_data[index]); //remove biggest
            if(_subset[index]->_size < _MINIMUM) fixShortage(index); //fix
            return true;
        }
    }

    //removes largest element
    void removeBiggest(Item& largest){
        if(isLeaf()){ //If leaf then largest is in data
            largest = _data[_size - 1];
            _size--;
        }
        else{ //If not keep looking for leaf
            _subset[_subSize - 1]->removeBiggest(largest);
            if(_subset[_subSize - 1]->_size < _MINIMUM) fixShortage(_subSize - 1);
        }
    }

    //Fix excess elements in problem subtree
    void fixExcess(std::size_t i){
        int mid = _subset[i]->_size / 2; //Get middle index

        bst::shiftRight(_subset,_subSize,i + 1); //Create a new subtree
        _subset[i + 1] = new Set;

        //Copy the largest half into new tree
        bst::copy(_subset[i]->_data,_subset[i + 1]->_data,_subset[i]->_size,mid + 1,_subset[i]->_size - 1);
        _subset[i + 1]->_size = _MINIMUM;
        _subset[i]->_size -= _MINIMUM;
        if(!_subset[i]->isLeaf()){ //If the problem tree has any children, move those too
            bst::copy(_subset[i]->_subset,_subset[i + 1]->_subset,
                    _subset[i]->_subSize,_subset[i]->_subSize - (_MINIMUM + 1),
                    _subset[i]->_subSize - 1);
            _subset[i]->_subSize -= (_MINIMUM + 1);
            _subset[i + 1]->_subSize += _MINIMUM + 1;
        }

        int ind = firstGE(_subset[i]->_data[mid]); //Find appropriate spot for mid
        bst::shiftRight(_data,_size,ind); //Send mid to parent
        _data[ind] = _subset[i]->_data[mid];
        _subset[i]->_size--;
    }

    //Fix shortage in problem subtree
    void fixShortage(std::size_t i){
        //CASE 1
        if((i > 0) && (_subset[i - 1]->_size > _MINIMUM)){ //Transfer an extra element from [i-1]
            bst::shiftRight(_subset[i]->_data,_subset[i]->_size,0); //Transfer
            _subset[i]->_data[0] = _data[i - 1];
            _data[i - 1] = _subset[i - 1]->_data[_size - 1];
            _subset[i - 1]->_size--;

            if(!_subset[i - 1]->isLeaf()){ //If that subtree is not a leaf
                Set* fChild = _subset[i - 1]->_subset[_subSize - 1]; //get final child of tree
                bst::shiftRight(_subset[i]->_subset,_subset[i]->_subSize,0);
                _subset[i]->_subset[0] = fChild; //Place in front of subtree
                _subset[i - 1]->_subSize--;
                _subset[i - 1]->_subset[_subSize] = NULL;
            }
        } //CASE 2
        else if((i + 1 < _subSize) && (_subset[i + 1]->_size > _MINIMUM)){
            int dI = i + 1; //Same as Case 1 except inverted
            if(i + 1 <= _size) dI = i; //Make sure its the last element if it goes over
            _subset[i]->_size++;
            _subset[i]->_data[_size] = _data[dI];

            _data[dI] = _subset[i + 1]->_data[0]; //Transfer
            bst::shiftLeft(_subset[i + 1]->_data,_subset[i + 1]->_size,0);

            if(!_subset[i + 1]->isLeaf()){ //If it has children
                Set* fChild = _subset[i + 1]->_subset[0]; //The first child instead
                _subset[i]->_subSize++;
                _subset[i]->_subset[_subSize] = fChild;
                bst::shiftLeft(_subset[i + 1]->_subset,_subset[i + 1]->_subSize,0);
            }
        }//CASE 3
        else if((i > 0) && (_subset[i - 1]->_size == _MINIMUM)){
            _subset[i - 1]->_size++; //Transfer element to subtree
            _subset[i - 1]->_data[_size - 1] = _data[i - 1];
            bst::shiftLeft(_data,_size,i - 1);
            //Merge the subtrees
            bst::merge(_subset[i - 1]->_data,_subset[i]->_data,_subset[i - 1]->_size,_subset[i]->_size);
            bst::merge(_subset[i - 1]->_subset,_subset[i]->_subset,_subset[i - 1]->_subSize,_subset[i]->_subSize);
            for(int k = 0; k < _subset[i]->_subSize; k++) //Disconnect the problem tree
                _subset[i]->_subset[k] = NULL;
            delete  _subset[i]; //Delete it
            bst::shiftLeft(_subset,_subSize,i);
        }//CASE 4
        else if((i + 1 < _subSize) && (_subset[i + 1]->_size == _MINIMUM)){
            int dI = i + 1; //Similar to 3 except inverted
            if( i + 1 <= _size) dI = i;
            bst::shiftRight(_subset[i + 1]->_data,_subset[i + 1]->_size,0);
            _subset[i + 1]->_data[0] = _data[dI];
            bst::shiftLeft(_data,_size,dI);
            //Make room in front for merging
            for(int k = 0; k < _subset[i]->_size; k++)
                bst::shiftRight(_subset[i + 1]->_data,_subset[i + 1]->_size,k);
            for(int k = 0; k < _subset[i]->_subSize; k++)
                bst::shiftRight(_subset[i + 1]->_subset,_subset[i + 1]->_subSize,k);
            bst::copy(_subset[i]->_data,_subset[i + 1]->_data,_subset[i]->_size); //Copy
            if(_subset[i]->_subSize > 0) cout << *_subset[i]->_subset[0] << endl;
            bst::copy(_subset[i]->_subset,_subset[i + 1]->_subset,_subset[i]->_subSize);
            for(int k = 0; k < _subset[i]->_subSize; k++) //Disconnect
                _subset[i]->_subset[k] = NULL;
            delete  _subset[i]; //Delete
            bst::shiftLeft(_subset,_subSize,i);
        }
    }

    //Gets the first element greater than or equal to target
    int firstGE(const Item& target) const{
        for(int i = 0; i < _size; i++)
            if(_data[i] >= target) return i;
        return _size; //If there is no such element
    }

public:
    Set(){ //Default
        _size = 0;
        _subSize = 0;
    }

    Set(const Set& Source):Set(){ //Copy
        _size = Source._size;
        _subSize = Source._subSize;
        bst::copy(Source._data,_data,_size);
        bst::copy(Source._subset,_subset,_subSize);
    }

    ~Set(){ //Destructor
        clear();
    }

    Set<Item>& operator =(const Set& Source){ //Assignment
        clear();
        _size = Source._size;
        _subSize = Source._subSize;
        bst::copy(Source._data,_data,_size);
        bst::copy(Source._subset,_subset,_subSize);
        return *this;
    }

    void clear(){ //Clears the root and its children
        for(int i = 0; i < _subSize; i++)
            delete _subset[i];
        _size = 0;
        _subSize = 0;
    }

    //Inserts an element (Must be valid after)
    bool insert(const Item& element){
        if(!looseInsert(element)){ //Did not insert
            return false;
        }
        if(_size > _MAXIMUM){ //If root has excess, fix
            Set* newRoot = new Set(*this);
            _size = 0; //Push down current root and create new root
            _subSize = 1;
            _subset[0] = newRoot;
            fixExcess(0);
            return true;
        }
    }

    //Erases element
    bool erase(const Item& target){
        if(!looseErase(target)){ //Did not erase
            return false;
        }
        if((_size == 0) && (_subSize == 1)){ //If shortage in root
            Set* onlyChild = _subset[0]; //get child

            bst::copy(onlyChild->_data,_data,onlyChild->_size);
            _size = onlyChild->_size; //Copy child into root

            bst::copy(onlyChild->_subset,_subset,onlyChild->_subSize);
            _subSize = onlyChild->_subSize;

            for(int i = 0; i < onlyChild->_subSize; i++) //disconnect child
                onlyChild->_subset[i] = NULL;
            delete onlyChild; //delete child
            return true;
        }
    }

    //gets the set the target is in
    Set* search(const Item& target) const{
        int index = firstGE(target);
        if((index != _size) && !(target < _data[index]))
            return this; //if in root
        else if((index == _size) && isLeaf())
            return NULL; //If not in root and root is leaf
        else return _subset[index]->search(target); //recusrive
    }

    //gets if empty
    bool empty() const{
        return _size == 0;
    }

    //output
    friend std::ostream& operator <<(std::ostream& out, const Set<Item>& Source){
        bst::traverse(Source._data,Source._size,Printer<Item>());
        out << "(";
        for(int i = 0; i < Source._subSize; i++)
            out << *Source._subset[i] << " | ";
        out << ")";
        return out;
    }
};

#endif // SET_H
