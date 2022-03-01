#include <iostream>

using namespace std;

int main() {
    int n;
    int l;
    cin >> n;
    cin >> l;

    int drawers[l + 1];
    for(int i = 0; i < l + 1; i++) {
        drawers[i] = -1;
    }

    int obj[n][2];

    for(int i = 0; i < n; i++) {
        int a;
        int b;
        cin >> a;
        cin >> b;

        obj[i][0] = a;
        obj[i][1] = b;

        if(drawers[a] == -1) {
            drawers[a] = i;
        } else if(drawers[b] == -1) {
            drawers[b] = i;
        }

    }
}
