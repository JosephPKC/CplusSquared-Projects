#ifndef MERGESORTER_H
#define MERGESORTER_H
#include "ContainerList.h"
template <typename Item>
class MergeSorter:public ContainerList<Item>{
private:
    std::size_t length(const List<Item>& L){
        int i = 0;
        if(L.Empty()) return i;
        Iterator<Item> walker = L.begin();
        Iterator<Item> end = L.end();
        end++;
        while(walker != end){
            i++;
            walker++;
        }
        return i;
    }

    List<Item> mergeSort(List<Item> L){
        if(length(L) <= 1) return L;
        std::size_t middle = length(L) / 2;
        List<Item> Left;
        List<Item> Right;
        for(std::size_t i = 0; i < middle; i++)
            Left.insertE(L[i]);
        for(std::size_t i = middle; i < length(L); i++)
            Right.insertE(L[i]);
        Left = mergeSort(Left);
        Right = mergeSort(Right);
        if(*Left.end() <= *Right.begin()){
            Left += Right;
            return Left;
        }
        List<Item> Result = merge(Left,Right);
        return Result;
    }
    List<Item> merge(List<Item>& L, List<Item>& R){
        List<Item> Result;
        while((length(L) > 0) && (length(R) > 0)){
            if(*L.begin() <= *R.begin()){
                Result.insertE(*L.begin());
                L.deleteAt(L.begin());
            }
            else{
                Result.insertE(*R.begin());
                R.deleteAt(R.begin());
            }
        }
        if(length(L) > 0)
            Result += L;
        if(length(R) > 0)
            Result += R;
        return Result;
    }

public:
    MergeSorter():ContainerList<Item>(){}
    void sort(){
        //If the size is 1 or 0, then it is already sorted
        //else:
        //Find the middle index of the list
        //split the list into two smaller lists (a new recursive function(list, begin, end))
        //Now in the smaller lists do the same.....
        //If there is only one element, then it is sorted
        //If there is two elements, then swap so that it may be sorted
        //If there are no elements then ???
        //Once the left and rights are sorted, check which one is bigger
        //Merge the left and right and go up one level
        ContainerList<Item>::_data = mergeSort(ContainerList<Item>::_data);
    }

};


#endif // MERGESORTER_H
