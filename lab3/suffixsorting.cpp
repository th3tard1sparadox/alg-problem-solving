#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct suffix {
    int index;
    string suff;
};

int compSuff(struct suffix first, struct suffix second) {
    return first.suff.compare(second.suff) < 0 ? 1 : 0;
}

vector<int> buildArray(string text, int n) {
    struct suffix
}

int main() {
    // C++ i/o speedup.
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    string s;
    getline(cin, s);
    int n;
    while(cin) {
        cin >> n;
        int query;
        for(int i = 0; i < n; i++) {
            cin >> query;
        }

        getline(cin, s);
    }

    return 0;
}
