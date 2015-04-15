#ifndef MATRIXCALCULATOR_H
#define MATRIXCALCULATOR_H
#include <iostream>
//Questions
//Should I make the Matrix class responsible for its operations
//Or should I make the calculator do that
//Better way might be to make the matrix class responsible for everything
//and the calculator will just calculate things using the matrix functions

//Also create a complex class for complex numbers
//Add/Substract
//Multiply/Divide
//Conjugate
//etc...
template <typename Element>
struct Matrix{
    Element** _matrix;
    std::size_t _row;
    std::size_t _col;
    Matrix(std::size_t rSize, std::size_t cSize){
        _matrix = new Element*[rSize];
        for(std::size_t index = 0; index < rSize; ++index){
            _matrix[index] = new Element[cSize];
        }
        _row = rSize;
        _col = cSize;
    }
};

struct ZeroMatrix:public Matrix<double>{
    ZeroMatrix(std::size_t rSize, std::size_t cSize):Matrix<double>(rSize,cSize){
        for(std::size_t i = 0; i < rSize; ++i){
            for(std::size_t j = 0; j < cSize; ++j){
                _matrix[i][j] = 0.0;
            }
        }
    }
};

struct IdentityMatrix:public ZeroMatrix<double>{
    IdentityMatrix(std::size_t size):ZeroMatrix(size,size) {
        for(std::size_t i = 0; i < size; ++i){
            _matrix[i][i] = 1.0;
        }
    }
};
//Special Matrix
//Wronskian
//Jacobian
//Binary Matrix/Boolean Matrix
//

//Best used with double, float, int, long, ...
//For everything else, the addition and multiplication must be defined (+,*)
//Addition should be Value + Value
//Multiplication should be both Value * Value and c * Value, Value * c, where c is some other object
template <typename Value>
class MatrixCalculator{
private:
public:
    //Addition
    //Subtraction
    //Scalar multiplication
    //Matrix multiplication
    //Trace
    //Transpose
    //Equality
    //Submatrix
    //Inverse
    //Determinant
    //Is Diagonal, Triangular, Symmetrical, Orthogonal
    //Eigenvalues and Eigenvectors
    //Rank, Dimension
    //Reduce to REF, RREF
    //Col, Row, Null Space
    //Kernel
  //Decomposition
    //Is Hermitian, Markov, Hessenberg, etc.
};

#endif // MATRIXCALCULATOR_H
