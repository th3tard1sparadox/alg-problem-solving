/**
 * TODO: comment.
 */

#include <iostream>
#include <string>
#include <vector>
#include <bits/stdc++.h>
#include <cstring>

using namespace std;

enum Type {naive, mem, full};

struct suffixF {
    int index;
    int rank[2];
};

struct suffixN {
    int index;
    char* suff;
};

int compSuffF(struct suffixF first, struct suffixF second) {
    if(first.rank[0] == second.rank[0]) {
        return (first.rank[1] < second.rank[1] ? 1 : 0);
    } else {
        return (first.rank[0] < second.rank[0] ? 1 : 0);
    }
}

int compSuffN(struct suffixN first, struct suffixN second) {
    return strcmp(first.suff, second.suff) < 0 ? 1 : 0;
}

vector<int> buildArrayFull(char* text, int n) {
    struct suffixF suffixes[n];

    for(int i = 0; i < n; i++) {
        suffixes[i].index = i;
        suffixes[i].rank[0] = text[i];
        suffixes[i].rank[1] = ((i + 1) < n) ? (text[i + 1]) : -1;
    }

    sort(suffixes, suffixes+n, compSuffF);

    int indexes[n];

    for(int i = 4; i < 2 * n; i = i * 2) {
        int rank = 0;
        int prevRank = suffixes[0].rank[0];
        suffixes[0].rank[0] = rank;
        indexes[suffixes[0].index] = 0;

        for(int j = 1; j < n; j++) {
            if(suffixes[j].rank[0] == prevRank && suffixes[j].rank[1] == suffixes[j - 1].rank[1]) {
                prevRank = suffixes[j].rank[0];
                suffixes[j].rank[0] = rank;
            } else {
                prevRank = suffixes[j].rank[0];
                suffixes[j].rank[0] = ++rank;
            }
            indexes[suffixes[j].index] = j;
        }

        for(int j = 0; j < n; j++) {
            int nextIndex = suffixes[j].index + i / 2;
            suffixes[j].rank[1] = (nextIndex < n) ? suffixes[indexes[nextIndex]].rank[0] : -1;
        }
        sort(suffixes, suffixes+n, compSuffF);
    }

    vector<int> suffArr;
    for(int i = 0; i < n; i++) {
        suffArr.push_back(suffixes[i].index);
    }

    return suffArr;
}

vector<int> buildArrayNaive(char* text, int n) {
    struct suffixN suffixes[n];

    for(int i = 0; i < n; i++) {
        suffixes[i].index = i;
        suffixes[i].suff = (text+i);
    }

    sort(suffixes, suffixes+n, compSuffN);

    vector<int> suffArr;
    for(int i = 0; i < n; i++) {
        suffArr.push_back(suffixes[i].index);
    }

    return suffArr;
}

vector<int> buildArrayMap(string & s, int sLen) {
    map<string, int> m;
    vector<int> suffArr;
    
    string subS = "";
    for(int i =  sLen - 1; i >= 0; i--) {
        subS = s[i] + subS;
        m[subS] = i;
    }

    for(auto suffPos : m) {
        suffArr.push_back(suffPos.second);
    }
    return suffArr;
}

int main() {
    // C++ i/o speedup.
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    Type implementation = full;
    string s;
    int n;
    while(getline(cin, s)) {
        int sLen = s.length();
        if(implementation == naive) {
            char* newS = new char[sLen + 1];
            strcpy(newS, s.c_str());
            vector<int> suffArr = buildArrayNaive(newS, sLen);
            cin >> n;
            int query;
            for(int i = 0; i < n; i++) {
                cin >> query;
                cout << suffArr[query] << " ";
            }
            cout << endl;
            delete[] newS;
        } else if(implementation == mem) {
            vector<int> suffArr = buildArrayMap(s, sLen);
            cin >> n;
            int query;
            for(int i = 0; i < n; i++) {
                cin >> query;
                cout << suffArr[query] << " ";
            }
            cout << endl;
        } else if(implementation == full) {
            char* newS = new char[sLen + 1];
            strcpy(newS, s.c_str());
            vector<int> suffArr = buildArrayFull(newS, sLen);
            cin >> n;
            int query;
            for(int i = 0; i < n; i++) {
                cin >> query;
                cout << suffArr[query] << " ";
            }
            cout << endl;
            delete[] newS;
        }
        getline(cin, s);
    }

    return 0;
}