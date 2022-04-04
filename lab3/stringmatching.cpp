/**
 * @file stringmatching.cpp
 * @author Annie Wång (annwa858@student.liu.se)
 * @brief implements Knuth-Morris-Pratts algorithm for pattern matching in a
 *        string. The complexity of the algorithm is O(p + t) where p is the
 *        length of the pattern and t is the length of the string it is
 *        searching within. The algorithm consists of two "parts", a partial
 *        match table and the search. The table is constructed based on the
 *        pattern and has a complexity of O(p) where p is the length of the
 *        pattern.
 * @date 2022-04-01
 */
#include <iostream>
#include <string>
#include <vector>

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
vector<long long> find(string & pattern, string & text) {
    long long textIndex = 0;
    long long patternIndex = 0;
    vector<long long> positions = {};
    vector<long long> matchTable = partialMatchTable(pattern);

    while(textIndex < text.length()) {
        if(pattern[patternIndex] == text[textIndex]) {
            textIndex++;
            patternIndex++;
        }

        if(patternIndex == pattern.length()) {
                positions.push_back(textIndex - patternIndex);
                patternIndex = matchTable[patternIndex - 1];
        } else if(textIndex < text.length() && pattern[patternIndex] != text[textIndex]) {
            if(patternIndex != 0) {
                patternIndex = matchTable[patternIndex - 1];
            } else {
                textIndex++;
            }
        }
    }

    return positions;
}

int main() {
    // C++ i/o speedup.
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    string pattern;
    string text;
    getline(cin, pattern);
    getline(cin, text);
    while(cin) { // look for eof.
        vector<long long> positions = find(pattern, text);
        for(auto & p : positions) {
            cout << p << " ";
        }
        cout << "\n";
        getline(cin, pattern);
        getline(cin, text);
    }
}
