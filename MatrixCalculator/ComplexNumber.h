#ifndef COMPLEXNUMBER_H
#define COMPLEXNUMBER_H

class ComplexNumber{
private:
    double _real;
    double _imaginary;
public:
    ComplexNumber(double real = 0.0, double imaginary = 0.0);

    double getReal() const;
    double getImaginary() const;

    void setReal(double real);
    void setImaginary(double imaginary);

    ComplexNumber& add(const ComplexNumber& R);
    ComplexNumber& subtract(const ComplexNumber& R);
    ComplexNumber& multiply(const ComplexNumber& R);
    ComplexNumber& divide(const ComplexNumber& R);
    ComplexNumber& conjugate();
    ComplexNumber& power(double exp);
    double modulus();
    friend bool operator ==(const ComplexNumber& L, const ComplexNumber& R);
    friend ComplexNumber& operator +(const ComplexNumber& L, const ComplexNumber& R);
    friend
    //add
    //subtract
    //multiply
    //divide
    //conjugate
    //power
    //
};

#endif // COMPLEXNUMBER_H
