#include "bookcatalogue.h"
//int _capacity;
//Book* _list;
//bool* _used;

//List<std::size_t>* _aTable;
//List<std::size_t>* _tTable;
//List<std::size_t>* __iTable;
//using namespace std;
std::size_t BookCatalogue::firstAvailable(){
    for(std::size_t i = 0; i < (std::size_t)_capacity; i++)
        if(isVacant(i)) return i;
    return -1;
}

void BookCatalogue::initializeList(){
    for(std::size_t i = 0; i < (std::size_t)_capacity; i++)
        _used[i] = false;
}

void BookCatalogue::addToTable(List<size_t> *table, std::string key, std::size_t index){
    std::size_t i = hash(key);
    table[i].insertH(index);
}

void BookCatalogue::removeFromTable(List<std::size_t>*  table, std::string key, std::string keyword){
    std::size_t i = hash(key);
    Iterator<std::size_t> walker = table[i].begin();
    Iterator<std::size_t> end = table[i].end();
    end++;
    while(walker != end){
        if(keyword.compare(TITLE) == 0){
            if(_list[*walker].getTitle().compare(key) == 0){
                table[i].remove(walker);
            }
        }
        else if(keyword.compare(AUTHOR) == 0){
            if(_list[*walker].getAuthor().compare(key) == 0){
                table[i].remove(walker);
            }
        }
        else if(keyword.compare(ISBN) == 0){
            if(_list[*walker].getISBN().compare(key) == 0){
                table[i].remove(walker);
            }
        }
        else{
            //WRONG KEYWORD
        }
        walker++;
    }
}

std::size_t BookCatalogue::searchTable(List<std::size_t>* table, std::string key, std::string keyword){
    std::size_t i = hash(key);
    List<std::size_t> L = table[i];
    Iterator<std::size_t> walker = L.begin();
    Iterator<std::size_t> end = L.end();
    end++;
    while(walker != end){
        if(keyword.compare(TITLE) == 0){
            if(_list[*walker].getTitle().compare(key) == 0){
                return *walker;
            }
        }
        else if(keyword.compare(AUTHOR) == 0){
            if(_list[*walker].getAuthor().compare(key) == 0){
                return *walker;
            }
        }
        else if(keyword.compare(ISBN) == 0){
            if(_list[*walker].getISBN().compare(key) == 0){
                return *walker;
            }
        }
        else{
            //WRONG KEYWORD
        }
        walker++;
    }
    return -1;
}

std::size_t BookCatalogue::hash(std::string key){
    int sum = 0;
    for(std::size_t i = 0; i < key.length(); i++)
        sum += key[i];
    return (std::size_t) (sum % _capacity);
}

bool BookCatalogue::isVacant(std::size_t index) const{
    return !_used[index];
}

BookCatalogue::BookCatalogue(int capacity){
    _capacity = capacity;
    _list = new Book[_capacity];
    _used = new bool[_capacity];
    _aTable = new List<std::size_t>[_capacity];
    _tTable = new List<std::size_t>[_capacity];
    _iTable = new List<std::size_t>[_capacity];
    initializeList();
}

BookCatalogue::BookCatalogue(const BookCatalogue& Other){
    _capacity = Other._capacity;
    _list = new Book[_capacity];
    _used = new bool[_capacity];
    copy(Other._list,_list,_capacity);
    copy(Other._used,_used,_capacity);
    copy(Other._tTable,_tTable,_capacity);
    copy(Other._aTable,_aTable,_capacity);
    copy(Other._iTable,_iTable,_capacity);
    initializeList();
}

BookCatalogue& BookCatalogue::operator =(const BookCatalogue& Other){
    _capacity = Other._capacity;
    _list = new Book[_capacity];
    _used = new bool[_capacity];
    copy(Other._list,_list,_capacity);
    copy(Other._used,_used,_capacity);
    _aTable = Other._aTable;
    _tTable = Other._tTable;
    _iTable = Other._iTable;
    initializeList();
    return *this;
}

BookCatalogue::~BookCatalogue(){
    delete[] _list;
    delete[] _used;
}

bool BookCatalogue::addBook(const Book& B){
    std::size_t index = firstAvailable();
    if(index == (std::size_t)-1) return false;
    _list[index] = B;
    _used[index] = true;
    addToTable(_tTable,B.getTitle(),index);
    addToTable(_aTable,B.getAuthor(),index);
    addToTable(_iTable,B.getISBN(),index);
    return true;
}

bool BookCatalogue::removeBook(const Book& B){
    std::size_t i = hash(B.getTitle());
    List<std::size_t> L = _tTable[i];
    Iterator<std::size_t> walker = L.begin();
    Iterator<std::size_t> end = L.end();
    bool success = false;
    end++;
    while(walker != end){
        if(_list[*walker] == B){
//            delete &_list[*walker];
            _used[*walker] = false;
            success = true;
            break;
        }
        walker++;
    }
    if(!success) return false;
//    Book* bPtr = searchBook(B.getTitle(),TITLE);
//    if(!bPtr) return false;
//    delete bPtr;
//    _used
    removeFromTable(_aTable,B.getAuthor(),AUTHOR);
    removeFromTable(_tTable,B.getTitle(),TITLE);
    removeFromTable(_iTable,B.getISBN(),ISBN);
    return true;
}

Book* BookCatalogue::searchBook(std::string key, std::string keyword){
    std::size_t i;
    if(keyword.compare(TITLE) == 0){
        i = searchTable(_tTable,key,keyword);

    }
    else if(keyword.compare(AUTHOR) == 0){
        i = searchTable(_tTable,key,keyword);
    }
    else if(keyword.compare(ISBN) == 0){
        i = searchTable(_tTable,key,keyword);
    }
    else{
        //WRONG KEYWORD
    }
    if(i == (std::size_t)-1) return nullptr;
    return &_list[i];
}

void BookCatalogue::print(std::string keyword){
    List<std::size_t>* table;
    if(keyword.compare(TITLE) == 0){
        table = _tTable;
//        cout << _tTable[0] << endl;
    }
    else if(keyword.compare(AUTHOR) == 0){
        table = _aTable;
    }
    else if(keyword.compare(ISBN) == 0){
        table = _iTable;
    }
    else{
        //WRONG KEYWORD
    }
    for(std::size_t i = 0; i < (std::size_t)_capacity; i++){
        Iterator<std::size_t> walker = table[i].begin();
        Iterator<std::size_t> end = table[i].end();
        end++;
        while(walker != end){
            std::cout << "{";
            std::cout << _list[*walker];
            std::cout << "}|\n";
            walker++;
        }
    }
    std::cout << std::endl;
}

std::ostream& operator <<(std::ostream& out, const BookCatalogue& Other){
    for(std::size_t i = 0; i < (std::size_t)Other._capacity; i++){
        out << "{";
        if(Other.isVacant(i)) out << "EMPTY";
        else out << Other._list[i];
        out << "}|\n";
    }
    return out;
}
