// for anyone reading this code, please don't write code that looks like this, I am very tired and just want it to work.

#include <iostream>
#include <string>

using namespace std;

bool backwards(string & s, const string & suff, int sLen, int diff) {
    for(int i = sLen - 1; i > -1; i--) {
        if(suff[i - diff] == '*') {
            break;
        }
        if(s[i] == '0') {
            s[i] = suff[i - diff];
        } else if(s[i] != suff[i - diff]) {
            return false;
        }
    }
    return true;
}

bool forward(string & s, const string & suff, int sLen, int suffPos) {
    for(int i = suffPos; i < sLen; i++) {
        if(suff[i - suffPos] == '*') {
            return backwards(s, suff, sLen, sLen - (int) suff.length());
        }
        if(s[i] == '0') {
            s[i] = suff[i - suffPos];
        } else if(s[i] != suff[i - suffPos]) {
            return false;
        }
    }
    return true;
}

int main() {
    int cases;
    cin >> cases;
    int totLen, suffixes;
    for(int i = 0; i < cases; i++) {
        cin >> totLen >> suffixes;
        string originalString(totLen, '0');
        int pos;

        bool ok = true;
        string suffix;
        for(int j = 0; j < suffixes; j++) {
            cin >> pos >> suffix;
            if(ok) {
                ok = forward(originalString, suffix, totLen, pos - 1);
            }
        }

        if(originalString.find("0") != string::npos) {
            ok = false;
        }

        if(ok) {
            cout << originalString << "\n";
        } else {
            cout << "IMPOSSIBLE\n";
        }
    }

    return 0;
}