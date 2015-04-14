#ifndef MERGESORTER_H
#define MERGESORTER_H
#include "ContainerList.h"
//Merge sorts the list
template <typename Item>
class MergeSorter:public ContainerList<Item>{
private:
    //List length


    //MergeSorts the List (Recursive Function)
    List<Item> mergeSort(List<Item> L){
        if(L.length() <= 1) return L; //If the list has 1 or no elements, then it is sorted
        std::size_t middle = L.length() / 2; //Find the middle index
        List<Item> Left;
        List<Item> Right;
        for(std::size_t i = 0; i < middle; i++) //Separate into Left and Right
            Left.insertE(L[i]);
        for(std::size_t i = middle; i < L.length(); i++)
            Right.insertE(L[i]);
        Left = mergeSort(Left); //Merge Sort the Left and Right
        Right = mergeSort(Right);
        if(*Left.end() <= *Right.begin()){ //Merge Left and Right back to together
            Left += Right; //Since both Left and Right are sorted by now, Right.begin should have the
            return Left; //smallest in Right and Left.end should have the largest in Left
        }                //By appending them, the entire thing should be sorted
        List<Item> Result = merge(Left,Right); //If not we have to merge them carefully
        return Result;
    }
    //Merges two lists together so that it is sorted
    List<Item> merge(List<Item>& L, List<Item>& R){
        List<Item> Result;
        while((L.length() > 0) && (R.length() > 0)){ //Go through both lists until one of them ends
            if(*L.begin() <= *R.begin()){ //Move one value of the list to the other
                Result.insertE(*L.begin());
                L.deleteAt(L.begin());
            }
            else{
                Result.insertE(*R.begin());
                R.deleteAt(R.begin());
            }
        }
        if(L.length() > 0) //For the remaining elements
            Result += L;
        if(R.length() > 0)
            Result += R;
        return Result;
    }

public:
    MergeSorter():ContainerList<Item>(){}
    MergeSorter(const List<Item>& L):ContainerList<Item>(L){}
    //Sorts, just calls mergesort
    void sort(){
        ContainerList<Item>::_data = mergeSort(ContainerList<Item>::_data);
    }

};


#endif // MERGESORTER_H
