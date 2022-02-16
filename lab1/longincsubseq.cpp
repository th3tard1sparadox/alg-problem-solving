#include <iostream>
#include <math.h>

using namespace std;

int findLongest(int *seq, int len, int *s) {
    int p[len];
    int m[len + 1];

    int l = 0;
    for(int i = 0; i < len; i++) {
        int low = 1;
        int high = l + 1;
        while(low < high) {
            int middle = low + floor((high - low) / 2);
            if(seq[m[middle]] < seq[i]) {
                low = middle + 1;
            } else {
                high = middle;
            }
        }
        int newL = low;

        p[i] = m[newL - 1];
        m[newL] = i;

        if(newL > l) {
            l = newL;
        }
    }

    int k = m[l];
    for(int i = l - 1; i >= 0; i--) {
        s[i] = k;
        k = p[k];
    }
    return l;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int len;
    int s[100000];
    
    while(cin >> len) {
        int seq[len];
        for(int i = 0; i < len; i++) {
            cin >> seq[i];
        }
        int l = findLongest(seq, len, s);
        cout << l << "\n";
        for(int i = 0; i < l; i++) {
            cout << s[i] << " ";
        }
        cout << "\n";
    }

    return 0;
}