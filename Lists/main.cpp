#include <iostream>
#include "ListTools.h"
#include "stack.h"
#include "iterator.h"
#include "List.h"
#include "Queue.h"
#include "SortedList.h"
#include "UniqueList.h"
#include "UniqueSortedList.h"
#include "Frequency.h"
using namespace std;

void testListTools();


int main()
{
    srand(time(NULL));
//    testListTools();
    Frequency<int> F;
    F.insert(1);
    F.insert(1);
    for(int i = 0; i < 10; i++) F.insert(i);
    cout << F << endl;
    cout << F[2] << endl;
    Frequency<int> G;
    for(int i = 0; i < 20; i += 2) G.insert(i);
    cout << G << endl;
    F += 3;
    cout << F << endl;
    F += G;
    cout << F << endl;
    cout << G << endl;

    return 0;
}

void testListTools(){
    /*print is given to be working completely*/
    Node<int>* head; Node<int>* found; Node<int>* holder;
    Node<int>* notInList; Node<int>* result; Node<int>* empty = NULL;
    Node<int>* removal; Node<int>* holder2; Node<int>* holder3;
    int deleter;
    cout << "<--- Creating and Testing Node--->" << endl;{
    head = new Node<int>(10,NULL);
    cout << "This is head(10,NULL): " << *head << endl;
    head->item = 50;
    cout << "This is head->item = 50: " << *head << endl;
    cout << endl;}

    cout << "<---Testing swap--->" << endl;{
    int a = 10, b = 20;
    cout << "These are the values a,b: " << a << " " << b << endl;
    ltf::swap(a,b);
    cout << "After swapping a,b: " << a << " " << b << endl;
    cout << endl;}

    cout << "<---Testing end--->" << endl;{
    head->next = new Node<int>(100,new Node<int>(150,new Node<int>(200,NULL)));
    cout << "This is the list: "; ltf::print(head);
    cout << "This is the end node: " << *ltf::end(head) << endl;
    cout << endl;}

    cout << "<---Testing search with custom start--->" << endl;{
    cout << "This is the list: "; ltf::print(head);
    found = ltf::search(head,150,1);
    cout << "Searching for 150 starting at index 1: " <<
            (found ? "Found it" : "Not found") << endl;
    found = ltf::search(head,150,4);
    cout << "Searching for 150 starting at index 4: " <<
         (found ? "Found it" : "Not found") << endl;
    found = ltf::search(head,99,0);
    cout << "Searching for 99 starting at index 0: " <<
         (found ? "Found it" : "Not found") << endl;
    cout << endl;}

    cout << "<---Testing search with default start--->" << endl;{
    cout << "This is the list: "; ltf::print(head);
    found = ltf::search(head,150);
    cout << "Searching for 150 starting from beginning: " <<
         (found ? "Found it" : "Not found") << endl;
    found = ltf::search(head,101);
    cout << "Searching for 101 starting from beginning: " <<
         (found ? "Found it" : "Not found") << endl;
    cout << endl;}

    cout << "<---Testing reverse--->" << endl;{
    cout << "This is the list: "; ltf::print(head);
    ltf::reverse(head);
    cout << "This is the reversed list: "; ltf::print(head);
    cout << endl;}

    cout << "<---Testing reverse new--->" << endl;{
    cout << "This is the list: "; ltf::print(head);
    holder = ltf::reverseNew(head);
    cout << "This is the new reversed list: "; ltf::print(holder);
    cout << "This is the original list: "; ltf::print(head);
    cout << endl; destroy(head);}

    destroy(head); //Reset head
    cout << "<---Testing insertHead--->" << endl;{
    cout << "This is the list: "; ltf::print(head);
    for(int i = 0; i < 10; i++) insertHead(head,i);
    cout << "This is the updated list(0-9): "; ltf::print(head);
    cout << endl;}

    cout << "<---Testing insertBefore--->" << endl;{
    cout << "This is the list: "; ltf::print(head);
    insertBefore(head,head,50);
    cout << "This is the list after inserting 50 before head: "; ltf::print(head);
    insertBefore(head,ltf::search(head,5),50);
    cout << "This is the list after inserting 50 before search(5): "; ltf::print(head);
    insertBefore(head,ltf::end(head),50);
    cout << "This is the list after inserting 50 before end: "; ltf::print(head);
    notInList = new Node<int>(9999,NULL);
    result = insertBefore(head,notInList,50);
    cout << "This is the list after inserting 50 before a node not in list: ";
    if(result) ltf::print(head); else cout << "Not in List" << endl;
    insertBefore(empty,empty,50);
    cout << "This is the list after inserting 50 into an empty list: ";
    if(result) ltf::print(head); else cout << "Empty List" << endl;
    cout << endl;}

    cout << "<---Testing insertAfter--->" << endl;{
    cout << "This is the list: "; ltf::print(head);
    insertAfter(head,head,150);
    cout << "This is the list after inserting 150 after head: "; ltf::print(head);
    insertAfter(head,ltf::search(head,5),150);
    cout << "This is the list after inserting 150 after search(5): "; ltf::print(head);
    insertAfter(head,ltf::end(head),150);
    cout << "This is the list after inserting 150 after end: "; ltf::print(head);
    result = insertAfter(head,notInList,150);
    cout << "This is the list after inserting 150 after a node not in list: ";
    if(result) ltf::print(head); else cout << "Not in List" << endl;
    insertAfter(empty,empty,50);
    cout << "This is the list after inserting 50 into an empty list: ";
    if(result) ltf::print(head); else cout << "Empty List" << endl;
    cout << endl;}

    selectionSort(head); //Sort the list before testing
    cout << "<---Testing insertSorted--->" << endl;{
    cout << "This is the list: "; ltf::print(head);
    insertSorted(head,220);
    cout << "This is the list after inserting 220: "; ltf::print(head);
    insertSorted(empty,50);
    cout << "This is the list after inserting 50 into an empty list: ";
    if(result) ltf::print(head); else cout << "Empty List" << endl;
    cout << endl;}

    cout << "<---Testing insertEnd--->" << endl;{
    cout << "This is the list: "; ltf::print(head);
    insertEnd(head,28);
    cout << "This is the list after inserting 28: "; ltf::print(head);
    insertEnd(empty,50);
    cout << "This is the list after inserting 50 into an empty list: ";
    if(result) ltf::print(head); else cout << "Empty List" << endl;
    cout << endl;}

    cout << "<---Testing removeHead--->" << endl;{
    cout << "This is the list: "; ltf::print(head);
    removeHead(head);
    cout << "This is the list after removing head: "; ltf::print(head);
    cout << endl;}

    cout << "<---Testing removeNode--->" << endl;{
    cout << "This is the list: "; ltf::print(head);
    removal = removeNode(head,head); delete removal;
    cout << "This is the list after removing head: "; ltf::print(head);
    removal = removeNode(head,ltf::search(head,5)); delete removal;
    cout << "This is the list after removing search(5): "; ltf::print(head);
    removal = removeNode(head,ltf::end(head)); delete removal;
    cout << "This is the list after removing end: "; ltf::print(head);
    removal = removeNode(head,notInList); if(removal) delete removal;
    cout << "This is the list after removing node not in list: ";
    if(result) ltf::print(head); else cout << "Not in List" << endl;
    removal = removeNode(empty,empty); if(removal) delete removal;
    cout << "This is the list after removing an empty list: ";
    if(result) ltf::print(head); else cout << "Empty List" << endl;
    cout << endl;}

    cout << "<---Testing deleteNode at Node--->" << endl;{
    cout << "This is the list: "; ltf::print(head);
    deleteNode(head,head);
    cout << "This is the list after deleting head: "; ltf::print(head);
    deleteNode(head,ltf::search(head,50));
    cout << "This is the list after deleting search(50): "; ltf::print(head);
    deleteNode(head,ltf::end(head));
    cout << "This is the list after deleting end: "; ltf::print(head);
    int deleter = deleteNode(head,notInList);
    cout << "This is the list after deleting node not in list: ";
    if(deleter != NULL) ltf::print(head); else cout << "Not in List" << endl;
    deleteNode(empty,empty);
    cout << "This is the list after deleting an empty list: ";
    if(deleter != NULL) ltf::print(head); else cout << "Empty List" << endl;
    cout << endl;}

    cout << "<--Testing deleteNode at item--->" << endl;{
    cout << "This is the list: "; ltf::print(head);
    deleteNode(head,150);
    cout << "This is the list after deleting 150: "; ltf::print(head);
    deleter = deleteNode(head,999);
    cout << "This is the list after deleting 999(Not int List): ";
    if(deleter != NULL) ltf::print(head); else cout << "Not int List" << endl;
    deleteNode(empty,empty);
    cout << "This is the list after deleting an empty list: ";
    if(deleter != NULL) ltf::print(head); else cout << "Empty List" << endl;
    cout << endl;}

    cout << "<---Testing at--->" << endl;{
    cout << "This is the list: "; ltf::print(head);
    cout << "This is the element at index 3: " << at(head,3) << endl;
    cout << endl;}

    cout << "<---Testing atP--->" << endl;{
    cout << "This is the list: "; ltf::print(head);
    cout << "This is the element at index 5: " << *atP(head,5) << endl;
    cout << "This is at a negative index -1: ";
            if(atP(head,-1)) cout << *atP(head,-1) << endl;
            else cout << "Index Out of Bounds" << endl;
    cout << "This is at a >size index 99: ";
            if(atP(head,99)) cout << *atP(head,99) << endl;
            else cout << "Index Out of Bounds" << endl;
    cout << endl;}

    cout << "<---Testing count--->" << endl;{
    cout << "This is the list: "; ltf::print(head);
    cout << "This is the size: " << count(head) << endl;
    cout << endl;}

    cout << "<---Testing deleteRepeats--->" << endl;{
    cout << "This is the list: "; ltf::print(head);
    deleteRepeats(head);
    cout << "This is the delete-repeated list: "; ltf::print(head);
    cout << endl;}

    copy(head,holder);
    for(int i = 0; i < count(holder); i++) insertSorted(head,at(holder,i));
    destroy(holder);
    cout << "<---Testing deleteRepeatsNew--->" << endl;{
    cout << "This is the list: "; ltf::print(head);
    holder = deleteRepeatsNew(head);
    cout << "This is the new delete-repeated list: "; ltf::print(holder);
    cout << "This is the original list: "; ltf::print(head);
    cout << endl; destroy(holder);}

    shuffle(head);
    cout << "<---Testing selectionSort--->" << endl;{
    cout << "This is the list: "; ltf::print(head);
    selectionSort(head);
    cout << "This is the sorted list: "; ltf::print(head);
    cout << endl;}

    shuffle(head);
    cout << "<---Testing selectionSortNew--->" << endl;{
    cout << "This is the list: "; ltf::print(head);
    holder = selectionSortNew(head);
    cout << "This is the new sorted list: "; ltf::print(holder);
    cout << "This is the original list: "; ltf::print(head);
    cout << endl; destroy(holder);}

    cout << "<---Testing shuffle--->" << endl;{
    cout << "This is the list: "; ltf::print(head);
    shuffle(head);
    cout << "This is the shuffled list: "; ltf::print(head);
    cout << endl;}

    cout << "<---Testing copy--->" << endl;{
    cout << "This is the list: "; ltf::print(head);
    copy(head,holder);
    cout << "This is the copied list: "; ltf::print(holder);
    cout << endl; destroy(holder);}

    cout << "<---Testing merge--->" << endl;{
    cout << "This is the list: "; ltf::print(head);
    for(int i = 0; i < 25; i += 2) insertHead(holder,i);
    cout << "This is the second list: "; ltf::print(holder);
    holder2 = merge(head,holder);
    cout << "This is the merged list: "; ltf::print(holder2);
    cout << endl; destroy(holder); destroy(holder2);}

    cout << "<---Testing mergeUnique--->" << endl;{
    cout << "This is the list: "; ltf::print(head);
    for(int i = 0; i < 25; i += 2) insertHead(holder,i);
    cout << "This is the second list: "; ltf::print(holder);
    holder2 = mergeUnique(head,holder);
    cout << "This is the merged unique list: "; ltf::print(holder2);
    cout << endl; destroy(holder); destroy(holder2);}

    cout << "<---Testing split--->" << endl;{
    cout << "This is the list: "; ltf::print(head);
    holder3 = NULL; copy(head,holder3);
    split(head,holder,holder2,4);
    cout << "This is the split list at index 4: "; ltf::print(holder);
    cout << "This is the split list at index 4: "; ltf::print(holder2);
    cout << endl; destroy(holder); destroy(holder2); copy(holder3,head);}

    cout << "<---Testing splitItem--->" << endl;{
    cout << "This is the list: "; ltf::print(head);
    copy(head,holder3);
    splitItem(head,holder,holder2,50);
    cout << "This is the split list at item 50: "; ltf::print(holder);
    cout << "This is the split list at item 50: "; ltf::print(holder2);
    cout << endl; destroy(holder); destroy(holder2); copy(holder3,head);}

    cout << "<---Testing splitNode--->" << endl;{
    cout << "This is the list: "; ltf::print(head);
    copy(head,holder3);
    splitNode(head,holder,holder2,ltf::search(head,150));
    cout << "This is the split list at search(150): "; ltf::print(holder);
    cout << "This is the split list at search(150): "; ltf::print(holder2);
    cout << endl; destroy(holder); destroy(holder2); copy(holder3,head);}

    cout << "<---Testing append--->" << endl;{
    cout << "This is the list: "; ltf::print(head);
    for(int i = 0; i < 10; i++) insertHead(holder,i*i);
    cout << "This is the second list: "; ltf::print(holder);
    append(head,holder);
    cout << "This is the appended list: "; ltf::print(holder);
    cout << endl; destroy(holder);}

    cout << "<---Testing appendNew--->" << endl;{
    cout << "This is the list: "; ltf::print(head);
    for(int i = 0; i < 10; i++) insertHead(holder,i*i);
    cout << "This is the second list: "; ltf::print(holder);
    holder2 = appendNew(head,holder);
    cout << "This is the new appended list: "; ltf::print(holder2);
    cout << "This is the original list: "; ltf::print(head);
    cout << "This is the original second list: "; ltf::print(holder);
    cout << endl; destroy(holder); destroy(holder2);}

    cout << "<---Testing subtract--->" << endl;{
    cout << "This is the list: "; ltf::print(head);
    for(int i = 0; i < 10; i++) insertHead(holder,i);
    cout << "This is the second list: "; ltf::print(holder);
    holder2 = subtract(head,holder);
    cout << "This is the subtracted list: "; ltf::print(holder2);
    cout << endl; destroy(holder); destroy(holder2);}

    cout << "<---Testing deleteInstanceOf--->" << endl;{
    cout << "This is the list: "; ltf::print(head);
    deleteInstanceOf(head,50);
    cout << "This is the list after deleting every instane of 50: "; ltf::print(head);
    cout << endl;}

    cout << "<---Testing deleteRepeatsOf--->" << endl;{
    cout << "This is the list: "; ltf::print(head);
    deleteRepeatsOf(head,4);
    cout << "This is the list after deleting repeats of 4: "; ltf::print(head);
    cout << endl;}

    cout << "<---Testing deleteRepeatsOf Node--->" << endl;{
    cout << "This is the list: "; ltf::print(head);
    holder = deleteRepeatsOfNew(head,150);
    cout << "This is the new list after deleting repeats of 150: "; ltf::print(holder);
    cout << "This is the original list: "; ltf::print(head);
    cout << endl; destroy(holder);}

    cout << "<---Testing index--->" << endl;{
    cout << "This is the list: "; ltf::print(head);
    cout << "This is the index at search(7): " << index(head,ltf::search(head,7)) << endl;
    cout << endl;}

    cout << "<---Testing destroy--->" << endl;{
    cout << "This is the list: "; ltf::print(head);
    destroy(head);
    if(!head) cout << "List is destroyed" << endl;
    cout << endl;}

    for(int i = 0; i < 10; i++) insertHead(head,i*2 + 3);
    cout << "<---Testing min--->" << endl;{
    cout << "This is the list: "; ltf::print(head);
    cout << "This is the minimum of the list: " << *min(head) << endl;
    cout << endl;}

    cout << "<---Testing max--->" << endl;{
    cout << "This is the list: "; ltf::print(head);
    cout << "This is the maximum of the list: " << *max(head) << endl;
    cout << endl;}

    cout << "<---Testing previousNode--->" << endl;{
    cout << "This is the list: "; ltf::print(head);
    cout << "This is before search(3): " << *previousNode(head,ltf::search(head,3)) << endl;
    cout << endl;}

    cout << "<---Testing isNodeInList--->" << endl;{
    cout << "This is the list: "; ltf::print(head);
    cout <<  (isNodeInList(head,notInList)? "Node is in List":"Node not in List") << endl;
    cout << endl;}

    cout << "<---Testing isEmpty--->" << endl;{
    cout << "This is the list: "; ltf::print(head);
    cout << (isEmpty(head)?"Empty":"Not Empty") << endl;
    cout << endl;}
}


