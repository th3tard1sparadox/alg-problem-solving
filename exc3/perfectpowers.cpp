#include <iostream>
#include <bits/stdc++.h>
#include <set>
#include <math.h>

using namespace std;

int perfect2electricbogaloo(long double x) {
    bool negative = false;
    if(x < 0) {
        negative = true;
        x = abs(x);
    }
    float delta = 0.00001;
    // log2(x)=p*log2(b), largest p when b smallest (2).
    long double largestPossibleP = (int)floor(log2(x));
    for(long long i = largestPossibleP; i > 0; i--) {
        long double root = pow(x, 1.0/i);
        if(pow(round(root), i) == x) {
            if(!negative || (negative && i % 2 != 0)) {
                return i;
            }
        }
    }
    return 1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    long double x;
    while(cin >> x) {
        if(x == 0)
            break;
        cout << perfect2electricbogaloo(x) << '\n';
    }
    return 0;
}