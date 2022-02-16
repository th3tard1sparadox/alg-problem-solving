#include <iostream>
#include <string>

using namespace std;

int (*dp)[8];
int (*priestsPref)[8];
int m;

string results[] = {"NNN", "NNY", "NYN", "NYY", "YNN", "YNY", "YYN", "YYY"};

int flipStone(int stones, int stone) {
    int temp = stones;
    switch(stone) {
    case 0:
        return temp ^ 1UL << 0;
    case 1:
        return temp ^ 1UL << 1;
    case 2:
        return temp ^ 1UL << 2;
    }
    return temp;
}

int vote(int stones, int priest) {
    // all priests have voted
    if(priest == m) {
        return stones;
    }

    // if we already have a best case with this vote
    if(dp[priest][stones] != -1) {
        return dp[priest][stones];
    }

    int outcome1 = vote(flipStone(stones, 0), priest+1);
    int outcome2 = vote(flipStone(stones, 1), priest+1);
    int outcome3 = vote(flipStone(stones, 2), priest+1);

    int like1 = priestsPref[priest][outcome1];
    int like2 = priestsPref[priest][outcome2];
    int like3 = priestsPref[priest][outcome3];


    if(like1 >= like3 && like2 >= like3) {
        dp[priest][stones] = outcome3;
        return outcome3;
    }
    if(like1 >= like2 && like3 >= like2) {
        dp[priest][stones] = outcome2;
        return outcome2;
    }
    dp[priest][stones] = outcome1;
    return outcome1;
}

int main() {
    int n;
    cin >> n;

    for(int i = 0; i < n; i++) {
        cin >> m;
        dp = new int[m + 1][8];
        fill(dp[0], dp[0] + (m + 1) * 8, -1);
        priestsPref = new int[m][8];
        for(int pri = 0; pri < m; pri++) {
            for(int cas = 0; cas < 8; cas++) {
                cin >> priestsPref[pri][cas];
            }
        }
        int res = vote(0b000, 0);
        cout << results[res] << endl;
        delete[] dp;
        delete[] priestsPref;
    }

    return 0;
}
