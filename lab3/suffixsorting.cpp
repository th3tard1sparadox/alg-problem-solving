#include <iostream>
#include <string>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

struct suffix {
    int index;
    string suff;
};

int compSuff(struct suffix first, struct suffix second) {
    return first.suff.compare(second.suff) < 0 ? 1 : 0;
}

vector<int> buildArray(string & text, int n) {
    struct suffix suffixes[n];

    for(int i = 0; i < n; i++) {
        suffixes[i].index = i;
        suffixes[i].suff = text.substr(i);
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
    getline(cin, s);
    cout << "string is: " << s << endl;
    int sLen = s.length();
    int n;
    while(cin) {
        cout << "string is: " << s << endl;
        vector<int> suffArr = buildArray(s, sLen);
        cout << "string is: " << s << endl;
        cin >> n;
        cout << "n is: " << n << endl;
        cout << "string is: " << s << endl;
        int query;
        for(int i = 0; i < n; i++) {
            cin >> query;
            cout << suffArr[query] << " ";
        }
        cout << endl;

        getline(cin, s);
        sLen = s.length();
    }

    return 0;
}
