#include <iostream>

using namespace std;

long long gcd(long long a, long long b) {
    if(b == 0) {
        return a;
    }
    return gcd(b, a % b);
}

int main() {
    int cases;
    cin >> cases;

    for(int i = 0; i < cases; i++) {
        long long a, b, c;
        cin >> a >> b >> c;

        long long g = gcd(a, b);
        if(c % g == 0) {
            cout << "Yes\n";
        } else {
            cout << "No\n";
        }
    }
}
