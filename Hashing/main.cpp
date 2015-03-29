#include "HTable.h"
#include "book.h"
#include <iostream>
using namespace std;

struct StringCode{
    int operator ()(string value){
        int code = 0;
        for(int i = 0; i < value.length(); i++){
            code += value[i];
        }
        return code;
    }
};
template <typename strCode>
struct BookPtrCode{
    strCode S;
    int operator ()(Book* value){
        return S(value->getAuthor()) + S(value->getTitle()) + S(value->getISBN());
    }
};

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
//void addBook(Book** masterList, size_t size, const Book& B);
//void addTable(Book* table, size_t size, string detail);
//size_t firstAvailable(Book** masterList, size_t size);
//template <typename Hash>
//size_t hashKey(string detail, Hash H);
//template <typename ptr>
//void initialize(ptr* array, size_t size);




const int CAPACITY = 32; //capacity of array
const int MAX = 50; //size of the input string

int main(){




    return 0;
}




char menu(){
    char choice;
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
    return choice;
}


void testHashTable(){
    HTable<int,int> H(16);
    Encode<int> keyer;
    H.insert(1,1);
    cout << keyer(1) << endl;
    cout << H << endl;
    H.insert(2,2);
    cout << keyer(2) << endl;
    cout << H << endl;
    H.remove(H.key(2));
    cout << H << endl;
    H.insert(1,1);
    cout << H << endl;
}

void prog(){
    //Declare variables
    char order;
//    string author, title, isbn; //Details of the book
    char a[MAX];
    char t[MAX];
    char i[MAX];
    Book* masterList[CAPACITY]; //List or array?
//    Book* B;
    HTable<string,Book*,StringCode,BookPtrCode<StringCode> > aTable(CAPACITY);
    HTable<string,Book*,StringCode,BookPtrCode<StringCode> > tTable(CAPACITY);
    HTable<string,Book*,StringCode,BookPtrCode<StringCode> > iTable(CAPACITY);
    for(int i = 0; i < CAPACITY; i++){
        masterList[i] = nullptr;
    }
    while(true){
        cout << "ATABLE: " << aTable << endl;
        switch(menu()){
            case 'A': //Add a book
            case 'a':{
            cin.ignore();
                cin.getline(t,MAX);
                cout << "GOT TITLE: " << t << endl;
                cin.getline(a,MAX);
                cout << "GOT AUTHOR: " << a << endl;
                cin.getline(i,MAX);
                cout << "GOT ISBN: " << i << endl;

                string author(a), title(t), isbn(i);
//                cin >> title >> author >> isbn;

//                B = new Book(title,author,isbn);
                Book* B = new Book(title,author,isbn);
                cout << "CREATED BOOK: " << B << endl;
                size_t index = addBook(masterList,CAPACITY,B);
                cout << "ADDED BOOK" << endl;
                addTable(aTable,author,masterList[index]);
                cout << "ADDED TO AUTHOR TABLE" << endl;
                addTable(tTable,title,masterList[index]);
                cout << "ADDED TO TITLE TABLE" << endl;
                addTable(iTable,isbn,masterList[index]);
                cout << "ADDED TO ISBN TABLE" << endl;
                //add book to list
                //add details to tables
                cout << aTable << endl;
                break;
            }
            case 'R':
            case 'r':{
                cin >> order; //which one to search by
                //Depending on the choice, hash the choice
                //Search the hash result in the arrays for the pointer to the list
                //remove
                break;
            }
            case 'S':
            case 's':{
                cin.ignore();
                cin >> order;
                cin.ignore();
                Book* found;
                if(order == 't'){
                    cin.getline(t,MAX);
                    string title(t);
                    found = search(tTable,title,choice);
                    cout << "SEARCHED TITLES" << endl;
                }
                else if(order == 'a'){
                    cin.getline(a,MAX);
                    string author(a);
                    cout << aTable << endl;
                    found = search(aTable,author,choice);
                    cout << "SEARCHED AUTHORS" << endl;
                }
                else if(order == 'i'){
                    cin.getline(i,MAX);
                    string isbn(i);
                    found = search(iTable,isbn,choice);
                    cout << "SEARCHED ISBNS" << endl;
                }
                else{} //Invalid

                if(!found) //some error of not found
                    cout << "Not found" << endl;
                else cout << *found << endl;
                break;
            }
            case 'P':
            case 'p':{
                cin >> order;
                if(order == 't') print(tTable);
                else if(order == 'a') cout << aTable << endl;
                else if(order == 'i') print(iTable);
                else {}//error
                break;
            }
            case 'X':
            case 'x':{
                exit(1);
                break;
            }
            case '1':{ //Secret Menu
                    testHashTable();
                    break;
            }
            default:{
                //Invalid
            }
        }
        cout << "ACTUAL ARRAY: " << endl;
        for(int i = 0; i < CAPACITY; i++){
            if(masterList[i]) cout << masterList[i];
            else cout << "VACANT";
            cout << ", ";
        }
        cout << endl;
    }


}
