#ifndef COMPLEXNUM_H
#define COMPLEXNUM_H

#include <cmath>
#include <iostream>

class ComplexNumber{
private:
   double a_;
   double b_;

public:
   ComplexNumber(double a = 0, double b = 0);
   ~ComplexNumber();
   ComplexNumber(const ComplexNumber& other);

   ComplexNumber operator+(const ComplexNumber& other);
   ComplexNumber operator-(const ComplexNumber& other);
   ComplexNumber operator*(double k);
   
   double square() const;
   bool operator<(const ComplexNumber& other) const;

   friend std::ostream& operator<<(std::ostream& o, const ComplexNumber& comp);

};

#endif
