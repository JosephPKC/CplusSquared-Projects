#ifndef BOOK_H
#define BOOK_H
#include <iostream>
class Book{
private:
    std::string _title;
    std::string _isbn;
    std::string _author; //Last, First Middle
public:
    Book(std::string title = "", std::string author = "", std::string isbn = "");

    std::string getTitle() const;
    std::string getAuthor() const;
    std::string getISBN() const;

    ~Book(){
        std::cout << "DESTROYING\n";
    }

    void setTitle(std::string title);
    void setAuthor(std::string author);
    void setISBN(std::string isbn);

    friend int operator %(const Book& Source, int modifier);
    friend std::ostream& operator <<(std::ostream& out, const Book& Source);

};

#endif // BOOK_H
