#include <iostream>

using namespace std;

long long mod(long long m, long long n) {
    if(m < 0) {
        return m + n;
    }
    return m % n;
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

// x mod n = a
// x mod m = b
long long CR(long long a, long long n, long long b, long long m) {
    long long K = n * m;
    long long x1 = 1;
    long long x2 = 0;

    // a * b = a * (2k + d) = 2 * (a * k) + a * d
    long long dm = 0;
    if(m % 2 != 0) {
        dm = 1;
    }
    long long km = (m - dm) / 2;
    long long x = ((2 * a * km) % K + (a * dm) % K);
    long long e = eucl(m, n, &x1, &x2);
    e = x1;
    long long de = 0;
    if(e % 2 != 0) {
        de = 1;
    }
    long long ke = (e - de) / 2;
    long long res = ((2 * x * ke) % K + (x * de) % K);

    x1 = 1;
    x2 = 0;

    long long dn = 0;
    if(n % 2 != 0) {
        dn = 1;
    }
    long long kn = (n - dn) / 2;
    x = ((2 * b * kn) % K + (b * dn) % K);
    e = eucl(n, m, &x1, &x2);
    e = x1;
    de = 0;
    if(e % 2 != 0) {
        de = 1;
    }
    ke = (e - de) / 2;
    res += ((2 * x * ke) % K + (x * de) % K);

    return (res % K);
}

int main() {
    int t;
    cin >> t;
    long long a, n, b, m;
    for(int i = 0; i < t; i++) {
        cin >> a >> n >> b >> m;
        long long x = CR(a, n, b, m);
        cout << x << " " << n * m << "\n";
    }
}
