/* testing my code, don't mind me */
#include <iostream>

using namespace std;

long long mod(long long m, long long n) {
    if(m < 0) {
        return m + n;
    }
    return m % n;
}

long long add(long long x, long long y, long long n) {
    return mod((x - n) + y, n);
}

long long sub(long long x, long long y, long long n) {
    return mod(x - y, n);
}

long long mul(long long x, long long y, long long n) {
    // hur overflowar jag inte här????
    return mod(x * y, n);
}

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

long long _div(long long x, long long y, long long n) {
    long long a = 1;
    long long b = 0;
    long long gcd = eucl(y, n, &a, &b);

    if(gcd != 1) {
        return -1;
    }
    return mul(x, mod(a, n), n);
}

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
