
#include <iostream>
#include <string>

using namespace std;

int main() {
    int nrCases;
    cin >> nrCases;

    for (int i = 0; i < nrCases; i++) {
        int nrDistances;
        cin >> nrDistances;
        string path;
        int height = 0;
        for (int j = 0; j < nrDistances; j++) {
            int dj;
            cin >> dj;
            if (height - dj < 0) {
                height += dj;
                path += 'U';
            } else {
                height -= dj;
                path += 'D';
            }
        }
        if (height != 0) {
            path = "IMPOSSIBLE";
        }
        cout << path << endl;
    }
    return 0;
}