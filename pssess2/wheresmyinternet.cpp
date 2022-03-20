#include <iostream>
#include <math.h>
#include <vector>
#include <bits/stdc++.h>
#include <iomanip>

using namespace std;

class CyFinder {
    int* parent;
    int* rank;

public:
    CyFinder(int n) {
        parent = new int[n];
        rank = new int[n];

        for(int i = 0; i < n; i++) {
            parent[i] = i;
            rank[i] = 1;
        }
    }

    ~CyFinder() {
        delete[] parent;
        delete[] rank;
    }

    int find(int i) {
        if(parent[i] == i) {
            return i;
        }

        return parent[i] = find(parent[i]);
    }

    void unite(int x, int y) {
        int s1 = find(x);
        int s2 = find(y);

        if(s1 != s2) {
            if(rank[s1] < rank[s2]) {
                parent[s1] = s2;
                rank[s2] += rank[s1];
            } else {
                parent[s2] = s1;
                rank[s1] += rank[s2];
            }
        }
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int verticies;
    int edges;
    cin >> verticies;
    cin >> edges;
    vector<vector<int>> edg = {};
    CyFinder s(verticies);
    for(int j = 0; j < edges; j++) {
        int x;
        int y;
        cin >> x;
        cin >> y;
        edg.push_back({x, y});
        s.unite(x - 1, y - 1);
    }

    int count = 0;
    for(int i = 0; i < verticies; i++) {
        if(s.find(0) != s.find(i)) {
            count++;
            cout << i + 1 << "\n";
        }
    }
    if(count == 0) {
        cout << "Connected\n";
    }
}
