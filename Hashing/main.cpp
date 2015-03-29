#include "HTable.h"
#include "book.h"
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

char menu();
bool addBook(List<Book> masterList, const Book& B);
bool addTable(HTable<Book> table, string value);
bool removeBook(List<Book> masterList, const Book& B);
bool removeTable(HTable<Book> table, const Book& B);
int hashKey(int key);
Book* search(HTable<Book> table, const Book& B);
void print(HTable<Book> table);

const int CAPACITY = 32;
int main()
{
    //testHashTable();
    char choice;
    string author, title, isbn;
    List<Book> masterList;
    HTable<Book> titleTable(CAPACITY);
    HTable<Book> authorTable(CAPACITY);
    HTable<Book> isbnTable(CAPACITY);
    switch(menu()){
    case 'A': //Add a book
    case 'a':{
        cin >> title >> author >> isbn;
        Book B(title,author,isbn);
        addBook(masterList,B);
        addTable(titleTable,title);
        addTable(authorTable,author);
        addTable(isbnTable,isbn);
        break;
    }
    }

    return 0;
}

char menu(){
    cout << "(A)dd book to the Master List(Title, Author, ISBN)\n"
         << "(R)emove book from the Master List\n"
         << "   -(a) to remove by author\n"
         << "   -(t) to remove by title\n"
         << "   -(i) to remove by isbn\n"
         << "(S)earch for a book in the Master List\n"
         << "   -(a) to search by author\n"
         << "   -(t) to search by title\n"
         << "   -(i) to search by isbn\n"
         << "(P)rint the Master List\n";
    cin >> choice;
}

bool addBook(List<Book> masterList, const Book& B){
    masterList.insertE(B);
}

bool addTable(HTable<Book> table, string value){
    table
}

bool removeBook(List<Book> masterList, const Book& B);
bool removeTable(HTable<Book> table, const Book& B);
int hashKey(int key){
    return Hash(CAPACITY);
}

Book* search(HTable<Book> table, const Book& B);
void print(HTable<Book> table);

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
