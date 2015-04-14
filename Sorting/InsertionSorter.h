#ifndef INSERTIONSORTER_H
#define INSERTIONSORTER_H
#include "ContainerList.h"
//Sorts the List via Insertion Sort
template <typename Item>
class InsertionSorter : public ContainerList<Item>{
private:
    //Generic Swap
    template <typename Item2>
    void swap(Item2& a, Item2& b){
        Item2 Temp = a;
        a = b;
        b = Temp;
    }

public:
    //Constructor
    InsertionSorter():ContainerList<Item>(){}
    InsertionSorter(const List<Item>& L):ContainerList<Item>(L){}
    //Insertion Sort
    void sort(){
        std::cout << ContainerList<Item>::_data << std::endl;
        std::size_t j; //The index back tracker
        for(std::size_t i = 0; i < ContainerList<Item>::_size; i++){ //Goes through each element in list
            j = i; //Begin back tracker at the index
            while(j > 0 && ContainerList<Item>::_data[j] < ContainerList<Item>::_data[j - 1]){ //Backtrack from index, swapping if necessary
                swap(ContainerList<Item>::_data[j],ContainerList<Item>::_data[j - 1]);
                j--;
            }
        }
    }




};

#endif // INSERTIONSORTER_H
