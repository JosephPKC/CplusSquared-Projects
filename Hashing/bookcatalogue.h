#ifndef BOOKCATALOGUE_H
#define BOOKCATALOGUE_H
#include <iostream>
#include "List.h"
#include "book.h"

//Keywords
static const std::string TITLE = "title";
static const std::string AUTHOR = "author";
static const std::string ISBN = "isbn";

class BookCatalogue{
private:
    int _capacity; //The number of books that can be stored
    Book* _list; //The list of books
    bool* _used; //Knows which indeces of the list are used

    List<std::size_t>* _aTable; //Hashtable for author
    List<std::size_t>* _tTable; //Hashtable for title
    List<std::size_t>* _iTable; //Hashtable for isbn

    //Gets the first available (ie not used) index in the list
    std::size_t firstAvailable();
    //Initializes the boolean array
    void initializeList();
    //Adds the index to the table// It finds the index of the table by hashing the key
    void addToTable(List<std::size_t> *table, std::string key, std::size_t index);
    //Removes the element from the table found by hashing the key//The keyword determines what kind of key it is
    void removeFromTable(List<std::size_t> *table, std::string key, std::string keyword);
    //Searches the table for the key
    std::size_t searchTable(List<std::size_t>* table, std::string key, std::string keyword);
    //Hashes the key (modulus the capacity)
    std::size_t hash(std::string key);
    //Checks if the index is vacant
    bool isVacant(std::size_t index) const;
    //Copies the array from source to destination using the length of the source
    //Assumes that there is enough memory allocated
    template <typename Type>
    void copy(Type* source, Type* dest, std::size_t sourceLen){
        for(std::size_t i = 0; i < sourceLen; i++){
            dest[i] = source[i];
        }
    }
public:
    //Constructor
    BookCatalogue(int capacity = 0);
    //Big Three
    BookCatalogue(const BookCatalogue& Other);
    BookCatalogue& operator =(const BookCatalogue& Other);
    ~BookCatalogue();
    //Adds a Book to the list AND updates the three tables and the boolean array
    bool addBook(const Book& B);
    //Removes the book from the list AND removes it from the tables and the boolean array
    bool removeBook(const Book& B);
    //Searches for the book using the key (author, title, or isbn) and the keyword
    Book* searchBook(std::string key, std::string keyword);
    //Prints the specific table using the keyword
    void print(std::string keyword);
    //Prints the list of books with no regard to the tables
    friend std::ostream& operator <<(std::ostream& out, const BookCatalogue& Other);
};

#endif // BOOKCATALOGUE_H
