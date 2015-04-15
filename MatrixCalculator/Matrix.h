#ifndef MATRIX_H
#define MATRIX_H
#include <iostream>
//TODO:
//Find out how to do double index
//Make a generic function for the double for loop
//Get rid of the template argument (just make it double for now)
//Some special matrices:
//Zero
//Identity
//Boolean
//Wronskian
//Jacobian

//a good subclass would be vectors
enum Error{
    NONE,
    NEGATIVE,
    BOUNDS,
    MISMATCH,

};

template <typename Entry>
class Matrix{
private:
    Entry** _matrix;
    std::size_t _rows;
    std::size_t _cols;
    //Array Manipulation
    void allocate(Entry* array, std::size_t size);
    void allocate2D(Entry** array, std::size_t size, std::size_t size2D);
    void initialize(Entry* array, std::size_t size);
    void initialize2D(Entry** array, std::size_t size, std::size_t size2D);

    //Array Helpers
    bool isPartOf(std::size_t row, std::size_t col) const{
        return (errorIndex(row,col) == NONE);
    }

    //Error/Exception
    Error errorIndex(std::size_t row, std::size_t col) const{
         if((row < 0) || (col < 0)) return NEGATIVE;
         else if((row >= _rows) || (col >= _cols)) return BOUNDS;
         else return NONE;
    }
    Error errorSize(std::size_t size, std::size_t reference) const{
        if(size != reference) return MISMATCH;
        else return NONE;
    }
    Error errorMatrixSize(const Matrix<Entry>& R) const{
        Error rE = errorSize(rSize,R.rowSize());
        Error cE = errorSize(cSize,R.colSize());
        if((rE != NONE) || (cE != NONE)) return MISMATCH;
        else return NONE;
    }


    //Matrix Helpers
public:
    Matrix(std::size_t rSize, std::size_t cSize){
        //Matrix should ALWAYS be initialized
        _rows = rSize;
        _cols = cSize;
        _matrix = new Entry*[_rows];
        for(std::size_t i = 0; i < _rows; ++i)
            _matrix[i] = new Entry[_cols];
    }
    Matrix(const Matrix<Entry>& R);
    Matrix<Entry>& operator =(const Matrix<Entry>& R);
    ~Matrix();

    //Constant Functions
    //Returns the number of rows (or the size of the columns)
    std::size_t rowSize() const{
        return _rows;
    }
    //Returns the number of columns (or the size of the rows)
    std::size_t colSize() const{
        return _cols;
    }
    //Gets a COPY of  the specific entry at the row and column specified
    Entry get(std::size_t row, std::size_t col) const{
        Error E = errorIndex(row,col);
        if(E != NONE) throw E;
        return _matrix[row][col];
    }
//    //single index operator
//    Entry* operator[](std::size_t row) const{
//        return _matrix[row];
//    }
//    //double index operator
//    Entry operator [](std::size_t col) const{
//        return _matrix[row][col];
//    }
    //Prints the matrix to the ostream
    void print(std::ostream& out) const{
        out << *this << endl;
//        for(std::size_t r = 0; r < _rows; ++r){
//            for(std::size_t c = 0; c < _cols; ++c)
//                out << _matrix[r][c] << "|";
//            out << endl;
//        }
//        out << endl;
    }
    //Search for the specified item, updates the row and col if found, if not then just returns a false
    bool search(std::size_t& row, std::size_t& col, const Entry& item) const{
        for(std::size_t r = 0; r < _rows; ++r){
            for(std::size_t c = 0; c < _cols; ++c){
                if(_matrix[r][c] == item){
                    row = r;
                    col = c;
                    return true;
                }
            }
        }
        return false;
    }

    //2D Array Operations
//    //Single non constant index
//    Entry*& operator [](std::size_t row){
//        return _matrix[row];
//    }
//    //Double non consant index
//    Entry& operator [](std::size_t row, std::size_t col){
//        return _matrix[row][col];
//    }
    //Sets a specific row and column with the item
    void set(std::size_t row, std::size_t col, const Entry& item){
        Error E = errorIndex(row,col);
        if(E != NONE) throw E;
        _matrix[row][col] = item;
    }
    //Searches the matrix for the first instance of the item(searches from top->down, left->right)
    Entry* search(const Entry& item){
        std::size_t row = -1, col = -1;
        if(search(row,col,item))
            return &_matrix[row][col];
        else return nullptr;
    }
    //resizes the matrix (initializes the new rows/columns to default item constructor, or deletes them if smaller
    bool resize(std::size_t row, std::size_t col);
    bool removeRow(std::size_t row);
    bool removeCol(std::size_t col);
    bool addRow(std::size_t row);
    bool addCol(std::size_t col);
    //Resets all of the entries to the default item constructor
    void clear();
    friend std::ostream& operator <<(std::ostream& out, const Matrix<Entry> R){
        for(std::size_t r = 0; r < _rows; ++r){
            for(std::size_t c = 0; c < _cols; ++c)
                out << _matrix[r][c] << "|";
            out << endl;
        }
        return out;
    }

    void replaceRow(std::size_t row, Entry* rowE);
    void replaceCol(std::size_t col, Entry* colE);

    //Matrix Operations
    //Adds two matrices together (NOTE: They MUST be the same size)
    Matrix<Entry>& add(const Matrix<Entry>& R){
        Error E = errorMatrixSize(R);
        if(E != NONE) throw E;
        Matrix<Entry> Result(_rows,_cols);
        for(std::size_t r = 0; r < _rows; ++r){
            for(std::size_t c = 0; c < _cols; ++c){
                Result.set(r,c,get(r,c) + R.get(r,c));
            }
        }
        return Result;
    }
    //Subtracts two matrices (NOTE: They MUST be the same size)
    Matrix<Entry>& subtract(const Matrix<Entry>& R){
        return add(R.negate());
    }
    //Multiplies each entry in the matrix by -1
    Matrix<Entry>& negate(){
        return multiply(-1);
    }
    //Multiplies each entry in the matrix by the scalar s
    Matrix<Entry>& multiply(double s){
        Matrix<Entry>& Result(*this);
        for(std::size_t r = 0; r < _rows; ++r){
            for(std::size_t c = 0; c < _cols; ++c){
                Result.set(r,c,get(r,c) * s);
            }
        }
        return Result;
    }

    Matrix<Entry>& multiply(const Matrix<Entry>& R);
    Matrix<Entry>& power(double exponent);
    Entry trace();
    Matrix<Entry>& transpose();
    bool equals(const Matrix<Entry>& R);
    Matrix<Entry>& submatrix(std::size_t sRow, std::size_t sCol, std::size_t eRow, std::size_t eCol);
    Matrix<Entry>& inverse();
    Entry determinant();
    Entry* mainDiagonal();
    Entry* getRows();
    Entry* getCols();

    //Category Functions
    bool isDiagonal();
    bool isTriangular();
    bool isSymmetric();
    bool isOrthogonal(); //?

    //Special Category Functions
    bool isHermitian();
    bool isMarkov();
    bool isHessenberg();
    bool isBoolean();

    //Eigenvalues and Eigenvectors
    Entry* eigenvalues();
    Matrix<Entry>* eigenvectors();

    //Special Operations
    Matrix<Entry>& reduce();
    Matrix<Entry>& reduceRREF();
    std::size_t rank();
    std::size_t dimension();
    Matrix<Entry>& colSpace();
    Matrix<Entry>& rowSpace();
    Matrix<Entry>& nullSpace();
    //kernel??
    //decomposition??
    //linear independence
    //spanning
};

#endif // MATRIX_H
