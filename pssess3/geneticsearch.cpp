#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>

using namespace std;

// creating the partial match table based on a pattern.
vector<long long> partialMatchTable(string & pattern) {
    int l = pattern.length();
    vector<long long> table(l, 0);
    long long pos = 1;
    long long candidateIndex = 0;

    table[0] = 0;
    while(pos < pattern.length()) {
        if(pattern[pos] == pattern[candidateIndex]) {
            candidateIndex++;
            table[pos] = candidateIndex;
            pos++;
        } else {
            if(candidateIndex != 0) {
                candidateIndex = table[candidateIndex - 1];
            } else {
                table[pos] = 0;
                pos++;
            }
        }
    }

    return table;
}

// implements Knuth-Morris-Pratts algorithm and returns the indexes of where a
// pattern match is found.
long long find(string & pattern, string & text) {
    long long textIndex = 0;
    long long patternIndex = 0;
    long long count = 0;
    vector<long long> matchTable = partialMatchTable(pattern);

    while(textIndex < text.length()) {
        if(pattern[patternIndex] == text[textIndex]) {
            textIndex++;
            patternIndex++;
        }

        if(patternIndex == pattern.length()) {
                count++;
                patternIndex = matchTable[patternIndex - 1];
        } else if(textIndex < text.length() && pattern[patternIndex] != text[textIndex]) {
            if(patternIndex != 0) {
                patternIndex = matchTable[patternIndex - 1];
            } else {
                textIndex++;
            }
        }
    }

    return count;
}

long long type2(string & S, string & L) {
    long long count = 0;
    unordered_set<string> substrs;
    for(int i = 0; i < (int) S.length(); i++) {
        string tmp = S;
        tmp.erase(tmp.begin()+i);
        if(substrs.count(tmp) == 0) {
            substrs.insert(tmp);
            count += find(tmp, L);
        }
    }
    return count;
}

long long type3(string & S, string & L) {
    long long count = 0;
    unordered_set<string> substrs;
    string letters = "AGCT";
    for(int i = 0; i < (int) S.length() + 1; i++) {
        for(int j = 0; j < (int) letters.length(); j++) {
            char c;
            if(j == 0) {
                c = 'A';
            } else if(j == 1) {
                c = 'G';
            } else if(j == 2) {
                c = 'C';
            } else {
                c = 'T';
            }
            string tmp = S;
            tmp.insert(tmp.begin()+i, c);
            if(substrs.count(tmp) == 0) {
                substrs.insert(tmp);
                count += find(tmp, L);
            }
        }
    }
    return count;
}

int main() {
    string S, L;
    cin >> S;
    while(S != "0") {
        cin >> L;
        long long t1 = find(S, L);
        long long t2 = type2(S, L);
        long long t3 = type3(S, L);
        cout << t1 << " " << t2 << " " << t3 << endl;
        cin >> S;
    }
}
