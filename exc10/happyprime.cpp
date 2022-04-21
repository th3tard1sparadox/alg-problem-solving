#include <iostream>
#include <vector>
#include <cmath>
#include <utility>
#include <string>
#include <unordered_set>

using namespace std;

vector<bool> bm(int n) {
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

    return b;
}

vector<long long> split(long long m) {
    string s = to_string(m);
    vector<long long> v;
    for(string::size_type i = 0; i < s.size(); i++) {
        v.push_back(((char)s[i]) - '0');
    }
    return v;
}

bool reduce(long long m, unordered_set<long long> v) {
    long long res = m;
    while(v.count(res) < 1) {
        v.emplace(res);
        long long tmp = 0;
        for(auto & i : split(res)) {
            tmp += i * i;
        }
        res = tmp;
        if(res == 1)
            return true;
        }

    return false;
}

int main() {
    int P;
    cin >> P;
    vector<bool> ps = bm(10001);
    for(int i = 0; i < P; i++) {
        long long K, m;
        cin >> K >> m;
        cout << K << " " << m;
        bool prime = true;
        if(!ps[m]) {
            prime = false;
        }
        bool happy = false;
        if(prime) {
            happy = reduce(m, {});
        }
        if(!happy) {
            cout << " NO\n";
        } else {
            cout << " YES\n";
        }
    }
}
