#include "HTable.h"

#include <iostream>
using namespace std;
void testHashTable();


/* Book Object: Title, Author, ISBN
 * A List of Book Objects
 * Three HashTables: One for Author, One for ISBN, One for Title
 * To find a book via any of those: Enter the value, hash the value and check the appropriate table
 * (continued) the index from the hashing of the table will point to the book object in the list
 * FUNCTIONS:
 * Menu
 * SearchList (Title, Author, or ISBN)
 * AddBook to List
 * Hash key (Title, Author, or ISBN)
 * Print the List Based on Order (Title, Author, or ISBN)
 * Add to HashTables for new Books
 * Remove Book from List
 */
int main()
{
    //testHashTable();


    return 0;
}

void testHashTable(){
    HTable<int> H(16);
    Encode<int> keyer;
    H.insert(1);
    cout << keyer(1) << endl;
    cout << H << endl;
    H.insert(2);
    cout << keyer(2) << endl;
    cout << H << endl;
    H.remove(H.key(2));
    cout << H << endl;
    H.insert(1);
    cout << H << endl;
}
