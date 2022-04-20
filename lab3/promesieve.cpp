#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

vector<bool> bm(int n) {
    vector<bool> b;
    for(int i = 0; i < n; i++) {
        cout << i << endl;
        b.push_back(true);
    }
    b[0] = false;
    b[1] = false;
    cout << "hello" << endl;
    for(int i = 2; i < n; i++) {
        if(b[i]) {
            for(int j = 1; j < floor(n / i); j++) {
                cout << i*j << endl;
                b[i*j] = false;
            }
        }
    }
    return b;
}

int main() {
    int n;
    int cases;
    cin >> n;
    cin >> cases;
    cout << n << cases << endl;
    vector<bool> b = bm(n);
    for(int i = 0; i < cases; i ++) {
        int x;
        cin >> x;
        if(b[x]) {
            cout << 1 << "\n";
        } else {
            cout << 0 << "\n";
        }
    }
}
