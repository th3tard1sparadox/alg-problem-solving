/**
 * This is not a final version as this is too slow and naive.
 * TODO: make fast.
 */

#include <iostream>
#include <string>
#include <vector>
#include <bits/stdc++.h>
#include <cstring>

using namespace std;

// class Suffix {
    // int index;
    // string suff;
// }

struct suffix {
    int index;
    char* suff;
};

int compSuff(struct suffix first, struct suffix second) {
    return strcmp(first.suff, second.suff) < 0 ? 1 : 0;
}

vector<int> buildArray(char* text, int n) {
    struct suffix suffixes[n];

    for(int i = 0; i < n; i++) {
        suffixes[i].index = i;
        suffixes[i].suff = (text+i);
    }

    sort(suffixes, suffixes+n, compSuff);

    vector<int> suffArr(n);
    for(int i = 0; i < n; i++) {
        suffArr[i] = suffixes[i].index;
    }

    return suffArr;
}

int main() {
    // C++ i/o speedup.
    // ios::sync_with_stdio(false);
    // cin.tie(NULL);
    // cout.tie(NULL);

    string s;
    int n;
    while(getline(cin, s)) {
        int sLen = s.length();
        char* newS = new char[sLen + 1];
        strcpy(newS, s.c_str());
        vector<int> suffArr = buildArray(newS, sLen);
        cin >> n;
        int query;
        for(int i = 0; i < n; i++) {
            cin >> query;
            cout << suffArr[query] << " ";
        }
        cout << endl;
        delete[] newS;
        getline(cin, s);
    }

    return 0;
}
