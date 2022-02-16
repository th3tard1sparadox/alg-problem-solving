#include <iostream>
#include <vector>
#include <cmath>
#include <bits/stdc++.h>

using namespace std;

/* Angi smol child calculator */
unsigned long long angi(unsigned long long candy, unsigned long long n, vector<unsigned long long> &wishes) {
    sort(wishes.begin(), wishes.end());
    reverse(wishes.begin(), wishes.end());
    wishes.push_back(0);

    unsigned long long anger = 0;
    bool last = false;
    for(int i = 0; i < wishes.size() - 1; i++) {
        if(i == wishes.size() - 2)
            last = true;

        unsigned long long diff;
        diff = min((unsigned long long)ceil((float)candy / (float)(i + 1)), wishes[i] - wishes[i + 1]);
        if(diff == 0)
            continue;
        for(int j = 0; j <= i; j++) {
            if(candy >= diff){
                wishes[j] -= diff;
                candy -= diff;
            } else {
                wishes[j] -= candy;
            }
            if(candy == 0)
                break;
        }
        if(candy == 0)
            break;
    }

    /*
    for (auto & w : wishes) {
        cout << w << " ";
    }
    cout << endl;
    */

    for(auto & wish : wishes) {
        anger += pow(wish, 2);
    }

    return anger;
    /*
    unsigned long long desire = accumulate(wishes.begin(), wishes.end(), 0); // Sort of what is left of the desired candy
    unsigned long long desire_left = desire - m;
    unsigned long long kids_left = n;

    for(auto & wish : wishes) {
        // Choose to give the smallest amount of candy that we can "justify"
        unsigned long long best_amount = min(wish, (unsigned long long)floor(desire_left / kids_left));
        anger += pow(best_amount, 2);
        desire_left -= best_amount;
        kids_left--;
    }

    return anger;
    */
}

int main() {
    // m = candies, n = children
    unsigned long long m;
    unsigned long long n;
    vector<unsigned long long> wishes;
    cin >> m;
    cin >> n;
    for(int i = 0; i < n; i++) {
        unsigned long long wish;
        cin >> wish;
        wishes.push_back(wish);
    }

    cout << angi(m, n, wishes);
}