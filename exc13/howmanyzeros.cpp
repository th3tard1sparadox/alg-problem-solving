#include <iostream>

using namespace std;

long long zeros_up_to(long long x) {
    if(x == 0) {
        return 1;
    }
    long long count = 0;
    while(x) {
        if(x % 10 == 0) {
            count += 1;
        }
        x = x / 10;
    }
    return count;
}

long long zeros(long long m, long long n) {
    // base cases
    if(m > n) {
        return 0;
    }
    if(n < 10) {
        if(m == 0) {
            return 1;
        }
        return 0;
    }
    if(m == 0) {
        return 1 + zeros(10, n);
    }
    if(m < 10) {
        return zeros(10, n);
    }

    long long count = 0;

    if(n - m <= 10) {
        for(int i = m; i < n + 1; i++) {
            count += zeros_up_to(i);
        }
        return count;
    }

    while(m % 10) {
        count += zeros_up_to(m);
        m += 1;
    }

    while(n % 10) {
        count += zeros_up_to(n);
        n -= 1;
    }

    count += zeros(m / 10, (n / 10) - 1) * 10;
    count += n / 10 - m / 10 + zeros_up_to(n);

    return count;
}

int main() {
    long long m, n;
    cin >> m >> n;
    while(true) {
        if(m == -1 && n == -1) {
            break;
        }
        cout << zeros(m, n) << "\n";
        cin >> m >> n;
    }
}
