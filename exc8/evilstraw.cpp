#include <iostream>
#include <string>

using namespace std;

long long countSwaps(string & text) {
    long long swaps = 0;
    long long fi = 0; // forwards
    long long bi = text.size() - 1; // backwards

    while(fi <= bi) {
        if(text[fi] != text[bi]) {
            long long ifi = fi + 1; // forwards
            long long ibi = bi - 1; // backwards
            long long last = ibi;
            bool found = false;

            while(ifi <= last) {
                if(text[fi] == text[ibi]) {
                    while(text[fi] != text[bi]) {
                        char temp = text[ibi];
                        text[ibi] = text[ibi + 1];
                        text[ibi + 1] = temp;
                        swaps++;
                        ibi++;
                        found = true;
                    }
                    break;
                } else if(text[bi] == text[ifi]) {
                    while(text[fi] != text[bi]) {
                        char temp = text[ifi];
                        text[ifi] = text[ifi - 1];
                        text[ifi - 1] = temp;
                        swaps++;
                        ifi--;
                        found = true;
                    }
                    break;
                }
                ifi++;
                ibi--;
            }
            if(!found) {
                return -1;
            }
        }
        fi++;
        bi--;
    }

    return swaps;
}

int main() {
    long long cases;
    cin >> cases;

    for(long long i = 0; i < cases; i++) {
        string text;
        cin >> text;
        long long swaps = countSwaps(text);
        if(swaps == -1) {
            cout << "Impossible\n";
        } else {
            cout << swaps << "\n";
        }
    }

    return 0;
}
