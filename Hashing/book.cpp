#include "book.h"

Book::Book(std::string title, std::string author, std::string isbn){
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

int operator %(const Book& Source, int modifier){
//    return
}

std::ostream& operator <<(std::ostream& out, const Book& Source){
    out << "\"" << Source._title << "\"; " << Source._author << "; " << Source._isbn;
    return out;
}

bool operator ==(const Book& Left, const Book& Right){
    if(Left.getAuthor().compare(Right.getAuthor()) == 0){
        if(Left.getTitle().compare(Right.getTitle()) == 0){
            if(Left.getISBN().compare(Right.getISBN()) == 0){
                return true;
            }
        }
    }
    return false;
}

bool operator !=(const Book& Left, const Book& Right){
    return Left == Right;
}
