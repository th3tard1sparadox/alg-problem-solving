/**
 * @file primesieve.cpp
 * @author Annie Wång (annwa858@student.liu.se)
 * @brief implements the sieve of eratosthenes. The time complexity
          of it is O(nloglogn).
 * @date 2022-05-01
 */
#include <iostream>
#include <vector>
#include <cmath>
#include <utility>

using namespace std;

// the sieve of eratosthenes.
pair<vector<bool>, int> bm(int n) {
    vector<bool> b(n, true);
    b[0] = false;
    b[1] = false;

    int count = 0;
    for(int i = 2; i < n; i++) {
        if(b[i]) {
            count++;
            for(int j = 2; j * i < n; j++) {
                b[i*j] = false;
            }
        }
    }

    return {b, count};
}

// the main loop.
int main() {
    int n;
    int cases;
    cin >> n;
    cin >> cases;
    pair<vector<bool>, int> p = bm(n + 1);
    cout << p.second << "\n";
    vector<bool> b = p.first;
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
