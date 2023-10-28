#include "ComplexNum.h"

ComplexNumber::ComplexNumber(double a, double b) :a_{a}, b_{b}
{}

ComplexNumber::ComplexNumber(const ComplexNumber& other) :a_{other.a_}, b_{other.b_}
{}

ComplexNumber::~ComplexNumber()
{}

ComplexNumber ComplexNumber::operator+(const ComplexNumber& other){
	ComplexNumber res;
	res.a_ = a_ + other.a_;
	res.b_ = b_ + other.b_;

	return res;
}

ComplexNumber ComplexNumber::operator-(const ComplexNumber& other){
	ComplexNumber res;
	res.a_ = a_ - other.a_;
	res.b_ = b_ - other.b_;

	return res;
}

ComplexNumber ComplexNumber::operator*(double k){
	ComplexNumber res;
	res.a_ = k * a_;
	res.b_ = k * b_;

	return res;
}

double ComplexNumber::square() const{
	return(sqrt(a_ * a_ + b_ * b_));
}

bool ComplexNumber::operator<(const ComplexNumber& other) const{
	return square() < other.square();
}

std::ostream& operator<<(std::ostream& o, const ComplexNumber& comp){
	o<< comp.a_ << "+" << "(" << comp.b_ << ")i" << std::endl;

	return o;
}
