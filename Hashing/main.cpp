#include "HTable.h"
#include <iostream>
#include "bookcatalogue.h"
using namespace std;

//struct StringCode{
//    int operator ()(string value){
//        int code = 0;
//        for(int i = 0; i < value.length(); i++){
//            code += value[i];
//        }
//        return code;
//    }
//};
//template <typename strCode>
//struct BookPtrCode{
//    strCode S;
//    int operator ()(Book* value){
//        return S(value->getAuthor()) + S(value->getTitle()) + S(value->getISBN());
//    }
//};

void testHashTable();

int main(){
    testHashTable();
    Book B[10]={Book("Biology of Plants","Raven Evert Eichhorn","1-57259-041-6"),
              Book("Magic, Witchcraft, and Religion","Arthur C. Lehmann","0-07-312269-6"),
              Book("Wheelock's Latin","Frederic M. Wheelock","978-0-06-199722-8"),
              Book("Africa in World History","Erik Gilbert","978-0-205-05399-5"),
              Book("Tastes of Paradise","Wolfgang Schivelbusch","978-0-679-74438-2"),
              Book("Aftermath: The Remnants of War","Donovan Webster","978-0-679-75153"),
              Book("The Unfinished Nation","Alan Brinkley","978-9-97-728635-4"),
              Book("Colonial Africa","Dennis Laumann","978-0-19-979639-7"),
              Book("Abina and the Important Men","Trevor R. Getz","978-0-19-984439-5"),
              Book("Republican Protesntaism in Aztlan","E.C.Orozco","978-1-90053-6-32")
             };
    BookCatalogue BC(16);
    cout << "INSERTING TEN BOOKS" << endl;
    for(int i = 0; i < 10; i++){

        BC.addBook(B[i]);
        BC.print(TITLE);
    }
    cout << "SEARCHING FOR BIOLOGY OF PLANTS" << endl;
    Book* found = BC.searchBook("Biology of Plants",TITLE);
    cout << *found << endl << endl;
    cout << "REMOVING BIOLOGY OF PLANTS" << endl;
    BC.removeBook(*found);
//    BC.removeBook(Book("Colonial Africa","Dennis Laumann","978-0-19-979639-7"));
    BC.print(TITLE);
    cout << "PRINTING VIA AUTHOR" << endl;
    BC.print(AUTHOR);
    cout << "PRINTING VIA ISBN" << endl;
    BC.print(ISBN);
    cout << BC << endl;

    return 0;
}


//char menu(){
//    char choice;
//    cout << "(A)dd book to the Master List(Title, Author, ISBN)\n"
//         << "(R)emove book from the Master List\n"
//         << "   -(a) to remove by author\n"
//         << "   -(t) to remove by title\n"
//         << "   -(i) to remove by isbn\n"
//         << "(S)earch for a book in the Master List\n"
//         << "   -(a) to search by author\n"
//         << "   -(t) to search by title\n"
//         << "   -(i) to search by isbn\n"
//         << "(P)rint the Master List\n";
//    cin >> choice;
//    return choice;
//}


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
    cout << H << endl << endl << endl;
}
