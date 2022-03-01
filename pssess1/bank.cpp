#include <iostream>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

int main() {
    long long n;
    long long t;
    cin >> n >> t;

    vector<vector<int>> ppl;

    int ci;
    int ti;
    for(int i = 0; i < n; i++) {
        cin >> ci >> ti;
        ppl.push_back({-ci, ti});
    }

    sort(ppl.begin(), ppl.end());

    for(int i = 0; i < n; i++) {
        cout << ppl[i][0] << " " << ppl[i][1] << endl;
    }

    long sum = 0;
    int time = 0;
    for(int i = 0; i < n; i++) {
        if(ppl[i][1] <= time) {
            sum -= ppl[i][0];
        }
        time++;
    }

    cout << sum;

    return 0;
}
