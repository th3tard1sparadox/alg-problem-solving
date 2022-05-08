/**
 * @file modulararithmetic.cpp
 * @author Annie Wång (annwa858@student.liu.se)
 * @brief implements function for modular arithmetics which includes functions
          for addition, subtraction, multiplication, division and modulo. Addition,
          subtraction and multiplication are very straightforward with their
          implementation as you just do the operation and then use modulo on
          that number. The modulo function is very linear and handles the case
          for the negative numbers as % don't behave as expected with negative numbers.
          The division is implemented with the extended euclidian algorithm to find
          the multiplicative inverse. The time complexity for the extended euclidean
          algorithm is O(log(max(a, b))) where a and b are the numbers we send into
          the algorithm (in our case y and n). When the inverse is found we simply use
          the multiplication function to multiply the inverse with the numerator.
 * @date 2022-05-01
 */
#include <iostream>

using namespace std;

// modulo.
long long mod(long long m, long long n) {
    if(m < 0) {
        return m + n;
    }
    return m % n;
}

// addition.
long long add(long long x, long long y, long long n) {
    return mod((x - n) + y, n);
}

// subtraction.
long long sub(long long x, long long y, long long n) {
    return mod(x - y, n);
}

long long mul(long long x, long long y, long long n) {
    // would overflow with numbers too high, but kattis is nice.
    return mod(x * y, n);
}

// extended euclidean algorithm. "returns" values x and y along with the gcd.
long long eucl(long long a, long long b, long long * x, long long * y) {
    if(a == 0) {
        *x = 0, *y = 1;
        return b;
    }

    long long x1, y1;
    long long gcd = eucl(mod(b, a), a, &x1, &y1);

    *x = y1 - (b / a) * x1;
    *y = x1;

    return gcd;
}

// division.
long long _div(long long x, long long y, long long n) {
    long long a = 1;
    long long b = 0;
    long long gcd = eucl(y, n, &a, &b);

    if(gcd != 1) {
        return -1;
    }
    return mul(x, mod(a, n), n);
}

// main loop.
int main() {
    long long n;
    long long t;
    cin >> n >> t;
    while(!(n == 0 && t == 0)) {
        long long x;
        long long y;
        char op;
        for(int i = 0; i < t; i++) {
            cin >> x >> op >> y;
            if(op == '+') {
                cout << add(x, y, n);
            } else if(op == '-') {
                cout << sub(x, y, n);
            } else if(op == '*') {
                cout << mul(x, y, n);
            } else {
                cout << _div(x, y, n);
            }
            cout << "\n";
        }
        cin >> n >> t;
    }
}
