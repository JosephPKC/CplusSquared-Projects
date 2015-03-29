#include "book.h"

Book::Book(std::string title = "", std::string author = "", std::string isbn = ""){
    _title = title;
    _author = author;
    _isbn = isbn;
}

std::string Book::getTitle() const{
    return _title;
}

std::string Book::getAuthor() const{
    return _author;
}

std::string Book::getISBN() const{
    return _isbn;
}

void Book::setTitle(std::string title){
    _title = title;
}

void Book::setAuthor(std::string author){
    _author = author;
}

void Book::setISBN(std::string isbn){
    _isbn = isbn;
}

int operator %(const Book& Source, int modifier) const{
    return (int)Source._title + (int)Source._author + (int)Source._isbn % modifier;
}

std::ostream& operator <<(std::ostream& out, const Book& Source){
    out << "\"" << Source._title << "\"; " << Source._author << "; " << Source._isbn;
    return out;
}
