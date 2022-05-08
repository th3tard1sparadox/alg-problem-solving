#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;

double edge(int x1, int x2, int y1, int y2) {
    int a, b;
    a = x1 - x2;
    b = y1 - y2;
    return a*a+b*b; // would sqrt here but would create problems when comparing
}

int main() {
    int cases;
    cin >> cases;
    for(int i = 0; i < cases; i++) {
        int x1, y1, x2, y2, x3, y3;
        cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
        cout << "Case #" << i + 1 << ": ";
        if((x1 == x2 && y1 == y2) ||
           (x1 == x3 && y1 == y3) ||
           (x2 == x3 && y2 == y3) ||
           (x1 == x2 && x2 == x3) ||
           (y1 == y2 && y2 == y3) ||
           x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2) == 0) {
            cout << "not a ";
        } else {
            double e1, e2, e3;
            e1 = edge(x1, x2, y1, y2);
            e2 = edge(x3, x2, y3, y2);
            e3 = edge(x3, x1, y3, y1);
            if(e1 == e2 || e1 == e3 || e2 == e3) {
                cout << "isosceles ";
            } else {
                cout << "scalene ";
            }

            vector<double> lengths = {e1, e2, e3};
            sort(lengths.begin(), lengths.end());

            if(lengths[0] + lengths[1] == lengths[2]) {
                cout << "right ";
            } else if(lengths[0] + lengths[1] > lengths[2]) {
                cout << "acute ";
            } else {
                cout << "obtuse ";
            }
        }
        cout << "triangle\n";
    }
}
