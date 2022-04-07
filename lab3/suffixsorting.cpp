/**
 * @file suffixsorting.cpp
 * @author Annie Wång (annwa858@student.liu.se)
 * @brief an implementation of a suffixArray construction and index retreival.
 *        The implementation is based on this paper: https://web.stanford.edu/class/cs97si/suffix-array.pdf
 *        where the timecomplexity is more thoroughly explained. The implementation
 *        is in short that we sort according to the first character then 
 *        the 2 first, then the 4 first etc.. This is done by using the
 *        "value" of the character as a rank to sort according to. The timecomplexity
 *        for the construction of the array is O(nlognlogn) where nlogn 
 *        comes from the standard sorting and logn from the implementation 
 *        of the algorithm. If a radixsort were to be used instead of the standard 
 *        sort (quicksort) a complexity of O(nlogn) would be reached.
 * @date 2022-04-07
 */

#include <iostream>
#include <string>
#include <vector>
#include <bits/stdc++.h>
#include <cstring>

using namespace std;

// each suffix care about its starting index and its current and next rank.
struct suffix {
    int index;
    int rank[2];
};

// class implementing the suffix array.
class suffixArray {
    vector<int> array;

private:
    // how we compare two suffixes, first based on current rank then next rank.
    static int suffixCmp(struct suffix first, struct suffix second) {
        if(first.rank[0] == second.rank[0]) {
            return (first.rank[1] < second.rank[1] ? 1 : 0);
        } else {
            return (first.rank[0] < second.rank[0] ? 1 : 0);
        }
    }

public:
    // constructor implementing the construction of a suffix array.
    suffixArray(string s) {
        int n = s.length();

        // set up char* instead of string to save memory.        
        char* text = new char[n + 1];
        strcpy(text, s.c_str());

        struct suffix suffixes[n];

        for(int i = 0; i < n; i++) {
            suffixes[i].index = i;
            suffixes[i].rank[0] = text[i];
            suffixes[i].rank[1] = ((i + 1) < n) ? (text[i + 1]) : -1;
        }

        sort(suffixes, suffixes+n, suffixCmp);

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
            sort(suffixes, suffixes+n, suffixCmp);
        }

        for(int i = 0; i < n; i++) {
            array.push_back(suffixes[i].index);
        }

        // memory management.
        delete[] text;
    }

    int getSuffix(int i) {
        return array[i];
    }
};


int main() {
    // C++ i/o speedup.
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    // read input.
    string s;
    int n;
    while(getline(cin, s)) {
        suffixArray suffArr(s);
        cin >> n;
        int query;
        for(int i = 0; i < n; i++) {
            cin >> query;
            cout << suffArr.getSuffix(query) << " ";
        }
        cout << endl;
        getline(cin, s);
    }

    return 0;
}