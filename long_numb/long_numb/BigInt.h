#pragma once
#include <iostream>
#include <vector>
#include <iomanip>
#include <string>

using namespace std;

class BigInt {
private:
    static const int WIDTH = 4;     // Width of each digit

    static const int BASE = 10000; // велика основа
    vector<int> digits; // масив цифр

public:

    BigInt(long long x = 0) { // конструктор з цілим числом
        while (x > 0) {
            digits.push_back(x % BASE);
            x /= BASE;
        }
    }

   

    void trim() { // видалити лідінг-зеро
        while (digits.size() > 1 && digits.back() == 0) {
            digits.pop_back();
        }
    }

    BigInt operator+(const BigInt& b) const { // операція додавання
        BigInt c;
        int carry = 0;
        for (int i = 0; i < max(digits.size(), b.digits.size()) || carry; i++) {
            if (i < digits.size())
                carry += digits[i];
            if (i < b.digits.size())
                carry += b.digits[i];
            c.digits.push_back(carry % BASE);
            carry /= BASE;
        }
        return c;
    }
    BigInt operator%(const BigInt& other) const {
        BigInt dividend = *this;
        BigInt divisor = other;
        BigInt quotient, remainder;

        // Normalize divisor to have the same number of digits as dividend
        int numZeroes = dividend.digits.size() - divisor.digits.size();
        for (int i = 0; i < numZeroes; ++i)
            divisor.digits.push_back(0);

        for (int i = dividend.digits.size() - 1; i >= 0; --i) {
            remainder.digits.insert(remainder.digits.begin(), dividend.digits[i]);
            int q = 0;
            while (divisor <= remainder) {
                remainder = remainder- divisor;
                ++q;
            }
            quotient.digits.insert(quotient.digits.begin(), q);
        }

        // Remove leading zeroes from remainder
        while (remainder.digits.size() > 1 && remainder.digits.back() == 0)
            remainder.digits.pop_back();

        if (remainder.digits[0] == 0) {
            BigInt zero(0);
            return zero;
        }

        return remainder;
    }
    BigInt operator-(const BigInt& b) const { // операція віднімання
        BigInt c;
        int carry = 0;
        for (int i = 0; i < digits.size(); i++) {
            int x = digits[i] - carry;
            if (i < b.digits.size()) x -= b.digits[i];
            if (x < 0) {
                x += BASE;
                carry = 1;
            }
            else {
                carry = 0;
            }
            c.digits.push_back(x);
        }
        c.trim();
        return c;
    }

    BigInt operator*(const BigInt& b) const { // операція множення
        BigInt c;
        c.digits.resize(digits.size() + b.digits.size());
        for (int i = 0; i < digits.size(); i++) {
            int carry = 0;
            for (int j = 0; j < b.digits.size() || carry; j++) {
                long long x = carry + c.digits[i + j] + 1LL * digits[i] * (j < b.digits.size() ? b.digits[j] : 0);
                carry = x / BASE;
                c.digits[i + j] = x % BASE;
            }
        }
        c.trim();
        return c;
    }
    BigInt operator/(const BigInt& b) const { // операція ділення
        BigInt c;
        c.digits.resize(digits.size());
        BigInt r = 0;
        for (int i = digits.size() - 1; i >= 0; i--) {
            r = r * BASE + digits[i];
            int q = 0;
            if (r >= b) {
                int left = 1, right = BASE - 1;
                while (left <= right) {
                    int mid = (left + right) / 2;
                    if (b * mid <= r) {
                        q = mid;
                        left = mid + 1;
                    }
                    else {
                        right = mid - 1;
                    }
                }
                r = r - b * q;
            }
            c.digits[i] = q;
        }
        c.trim();
        return c;
    }

    BigInt operator<<(int k) const { // операція зсуву вліво
        BigInt c;
        c.digits.resize(digits.size() + k);
        for (int i = 0; i < digits.size(); i++) {
            c.digits[i + k] = digits[i];
        }
        return c;
    }


    BigInt operator>>(int k) const { // операція зсуву вправо
        BigInt c;
        if (k >= digits.size()) {
            c.digits.push_back(0);
        }
        else {
            for (int i = k; i < digits.size(); i++) {
                c.digits.push_back(digits[i]);
            }
        }
        return c;
    }

    friend std::ostream& operator<<(std::ostream& os, const BigInt& num) {
        os << (num.digits.empty() ? 0 : num.digits.back());

        for (int i = num.digits.size() - 2; i >= 0; --i) {
            os.width(WIDTH);
            os.fill('0');
            os << num.digits[i];
        }

        return os;
    }

    bool operator!=(const BigInt& b) const {
        return !(*this == b);
    }

    bool operator!=(const int& b) const {
        BigInt l_other(b);
        return !(*this == l_other);
    }

    bool operator==(const BigInt& b) const {
        return digits == b.digits;
    }



    bool operator>=(const BigInt& b) const {
        if (this->digits.size() >= b.digits.size()) {
            return true;
        }
        if (this->digits.size() < b.digits.size()) {
            return false;
        }

        // Compare digits from most significant to least significant
        for (int i = this->digits.size() - 1; i >= 0; --i) {
            if (this->digits[i] > b.digits[i]) {
                return true;
            }
            if (this->digits[i] < b.digits[i]) {
                return false;
            }
        }

        // Numbers are equal
        return false;
    }

    bool operator<=(const BigInt& b) const {
        if (digits.size() != b.digits.size())
            return digits.size() < b.digits.size();

        for (int i = digits.size() - 1; i >= 0; --i) {
            if (digits[i] != b.digits[i])
                return digits[i] < b.digits[i];
        }

        return true;
    }

    // Addition assignment operator
    BigInt& operator+=(const BigInt& other) {
        *this = *this + other;
        return *this;
    }

    // Subtraction assignment operator
    BigInt& operator-=(const BigInt& other) {
        *this = *this - other;
        return *this;
    }

    // Multiplication assignment operator
    BigInt& operator*=(const BigInt& other) {
        *this = *this * other;
        return *this;
    }

    // Division assignment operator
    BigInt& operator/=(const BigInt& other) {
        *this = *this / other;
        return *this;
    }

    bool operator>(const BigInt& other) const {
        if (this->digits.size() > other.digits.size()) {
            return true;
        }
        if (this->digits.size() < other.digits.size()) {
            return false;
        }

        // Compare digits from most significant to least significant
        for (int i = this->digits.size() - 1; i >= 0; --i) {
            if (this->digits[i] > other.digits[i]) {
                return true;
            }
            if (this->digits[i] < other.digits[i]) {
                return false;
            }
        }

        // Numbers are equal
        return false;
    }
};
