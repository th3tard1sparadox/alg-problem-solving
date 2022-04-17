/**
 * @file rationalarithmetic.cpp
 * @author Annie Wång (annwa858@student.liu.se)
 * @brief implements a class for rational numbers and overloads the operators
          +, -, *, /, <, >, <=, >=, == and !=. Class normalizes the answer of
          +, -, * and / before returning it (this includes making sure the 
          denominator is always positive). Time complexity for the operations are
          O(log(min(numerator, denominator))) because of the gcd that is used
          in the normalize function.
 * @date 2022-04-17
 */
#include <iostream>

using namespace std;

// simple gcd function. O(log(min(a, b))), see euclidean algorithm.
long long gcd(long long a, long long b) {
    if(b == 0) {
        return a;
    }
    return gcd(b, a % b);
}

// implementation of rational numbers as a class.
class RN {
public:
    // store numerator and denominator separate.
    long long numerator;
    long long denominator;

    // constructors.
    RN() : numerator(0), denominator(0) {};
    RN(long long a, long long b) : numerator(a), denominator(b) {};

    // numerical operators.
    // x1    x2    x1*y2+x2*y1
    // /  +  /  =       /
    // y1    y2       y1*y2
    RN operator+(const RN& n) const {
        RN ans((this->numerator * n.denominator) + (n.numerator * this->denominator),
               this->denominator * n.denominator);
        return ans.normalize();
    };
    // x1    x2    x1*y2-x2*y1
    // /  -  /  =       /
    // y1    y2       y1*y2
    RN operator-(const RN& n) const {
        RN ans((this->numerator * n.denominator) - (n.numerator * this->denominator),
               this->denominator * n.denominator);
        return ans.normalize();
    };
    // x1    x2    x1*x2
    // /  *  /  =    /
    // y1    y2    y1*y2
    RN operator*(const RN& n) const {
        RN ans(this->numerator * n.numerator, this->denominator * n.denominator);
        return ans.normalize();
    };
    // x1    x2    x1*y2
    // /  /  /  =    /
    // y1    y2    x2*y1
    RN operator/(const RN& n) const {
        RN ans(this->numerator * n.denominator, this->denominator * n.numerator);
        return ans.normalize();
    };

    // comparative functions.
    // we only need to compare x1*y2 and x2*y1.
    bool operator<(const RN& n) const {
        return this->numerator * n.denominator < n.numerator * this->denominator;
    };
    bool operator>(const RN& n) const {
        return this->numerator * n.denominator > n.numerator * this->denominator;
    };
    // a <= b is the same as !(a > b)
    bool operator<=(const RN& n) const {
        return !(n < *this);
    };
    // a >= b is the same as !(a < b)
    bool operator>=(const RN& n) const {
        return !(n > *this);
    };
    bool operator==(const RN& n) const {
        return this->numerator * n.denominator == n.numerator * this->denominator;
    };
    bool operator!=(const RN& n) const {
        return this->numerator * n.denominator != n.numerator * this->denominator;
    };

private:
    // normalize using gcd and make sure denominator is positive.
    RN normalize() const {
        long long a = gcd(abs(this->numerator), abs(this->denominator));
        long long num = (this->numerator / a);
        long long den = (this->denominator / a);

        if(den < 0) {
            num = -num;
            den = -den;
        }

        RN norm(num, den);
        return norm;
    };
};

int main() {
    // C++ i/o speedup.
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    // read input and answer kattis.
    long long operations;
    cin >> operations;
    for(long long i = 0; i < operations; i++) {
        long long numa;
        long long dena;
        long long numb;
        long long denb;

        char op;

        cin >> numa >> dena >> op >> numb >> denb;

        RN a(numa, dena);
        RN b(numb, denb);

        RN ans;
        if(op == '+') {
            ans = a + b;
        } else if(op == '-') {
            ans = a - b;
        } else if(op == '*') {
            ans = a * b;
        } else if(op == '/') {
            ans = a / b;
        }

        cout << ans.numerator << " / " << ans.denominator << "\n";
    }
}
