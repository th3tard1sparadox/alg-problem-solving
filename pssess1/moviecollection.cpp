#include <iostream>

using namespace std;

int main() {
    int n;
    cin >> n;
    int m;
    int r;
    for(int j = 0; j < n; j++) {
        cin >> m;
        cin >> r;

        int ind[m + 1];
        for(int i = 1; i < m + 1; i++) {
            ind[i] = i;
        }

        int mr;
        for(int i = 0; i < r; i++) {
            cin >> mr;
            cout << ind[mr] - 1 << " ";
            for(int k = 1; k < m + 1; k++) {
                if(ind[k] < ind[mr]) {
                    ind[k]++;
                }
            }
            ind[mr] = 1;
        }
        cout << "\n";
    }

    return 0;
}
