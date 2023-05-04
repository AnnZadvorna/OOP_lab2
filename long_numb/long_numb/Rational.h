#include <iostream>


template <typename T>

class Rational {
private:
    T numerator;
    T denominator;

public:

    Rational() : numerator(0), denominator(1) {}
    Rational(T n, T d) : numerator(n), denominator(d) {
        if (denominator == 0) {
            throw std::invalid_argument("Denominator cannot be zero");
        }
    }

    // Copy constructor
    Rational(const Rational& other) {
        numerator = other.numerator;
        denominator = other.denominator;
    }

    // Assignment operator
    Rational& operator=(const Rational& other) {
        numerator = other.numerator;
        denominator = other.denominator;
        return *this;
    }

    // Addition
    Rational operator+(const Rational& other) const {
        T n = numerator * other.denominator + other.numerator * denominator;
        T d = denominator * other.denominator;
        return Rational(n, d);
    }

    // Subtraction
    Rational operator-(const Rational& other) const {
        T n = numerator * other.denominator - other.numerator * denominator;
        T d = denominator * other.denominator;
        return Rational(n, d);
    }

    // Multiplication
    Rational operator*(const Rational& other) const {
        T n = numerator * other.numerator;
        T d = denominator * other.denominator;
        return Rational(n, d);
    }
    // Division
    Rational operator/(const Rational& other) const {
        if (other.numerator == 0) {
            throw std::invalid_argument("Division by zero");
        }
        T n = numerator * other.denominator;
        T d = denominator * other.numerator;
        return Rational(n, d);
    }

    // Conversion to double
    operator double() const {
        return static_cast<double>(numerator) / static_cast<double>(denominator);
    }
    // Output operator
    friend std::ostream& operator<<(std::ostream& os, const Rational& r) {
        os << r.numerator << "/" << r.denominator;
        return os;
    }

    // Input operator
    friend std::istream& operator>>(std::istream& is, Rational& r) {
        T n, d;
        char c;
        is >> n >> c >> d;
        if (c != '/') {
            is.setstate(std::ios::failbit);
            return is;
        }
        r = Rational(n, d);
        return is;
    }
    Rational<T>& operator-=(const Rational<T>& other) {
        numerator = (numerator * other.denominator) - (other.numerator * denominator);
        denominator *= other.denominator;
        return *this;
    }

    // Compound assignment: Division
    Rational<T>& operator/=(const Rational<T>& other) {
        numerator *= other.denominator;
        denominator *= other.numerator;
        return *this;
    }
    bool operator>(const Rational<T>& other) const {
        // Multiply cross products to compare
        return (numerator * other.denominator) > (other.numerator * denominator);
    }

    // Left shift operator for the numerator and denominator
    Rational<T> shiftLeft(int shift) const {
        T shiftedNum = numerator << shift;
        T shiftedDenom = denominator << shift;
        return Rational<T>(shiftedNum, shiftedDenom);
    }

    // Right shift operator for the numerator and denominator
    Rational<T> shiftRight(int shift) const {
        T shiftedNum = numerator >> shift;
        T shiftedDenom = denominator >> shift;

        if (shiftedDenom == 0) {
            return Rational<T>(0, 1);
        }

        return Rational<T>(shiftedNum, shiftedDenom);
    }

private:
    // Reduce the fraction to lowest terms
    void reduce() {
        if (numerator != 0) {
            T gcd = findGCD(numerator, denominator);
            numerator = numerator / gcd;
            denominator = denominator / gcd;
        }
    }

    // Find the greatest common divisor of two numbers
    T findGCD(T a, T b) const {
        bool bnot0 = 0;
        while (b != 0) {
            bnot0 = (b != 0);
            T temp = b;
            b = a % b;
            a = temp;
        }
        return a;
    }
};
