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
            parent[i] = -1;
            rank[i] = 1;
        }
    }

    int find(int i) {
        if(parent[i] == -1) {
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

class Graph {
    vector<vector<double>> edges;
    double v;

public:
    Graph(double v) {
        this->v = v;
    }

    void addEdge(double x, double y, double w) {
        edges.push_back({w, x, y});
    }

    double kruskals() {
        sort(edges.begin(), edges.end());
        CyFinder s((int)v);
        double cost = 0.0;
        for(auto & edge : edges) {
            double w = edge[0];
            double x = edge[1];
            double y = edge[2];

            if(s.find(x) != s.find(y)) {
                s.unite(x, y);
                cost += w;
            }
        }
        return cost;
    }
};


double cal_dist(pair<double, double> p1, pair<double, double> p2) {
    double dx = p1.first - p2.first;
    double dy = p1.second - p2.second;
    return sqrt(dx * dx + dy * dy);
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int cases;
    cin >> cases;
    int islands_am;
    cout << fixed;
    for(int j = 0; j < cases; j++) {
        cin >> islands_am;
        Graph g(islands_am);
        pair<double, double> islands[islands_am];
        for(int i = 0; i < islands_am; i++) { // lmao i for island
            pair<double, double> coord;
            cin >> coord.first;
            cin >> coord.second;
            islands[i] = coord;
            for(int j = 0; j < i; j++) {
                double dist = cal_dist(islands[j], coord);
                // cout << "dist from " << j << " to " << i << " is " << dist << endl;
                g.addEdge(i, j, dist);
            }
        }
        cout << setprecision(9) << g.kruskals() << "\n";
    }
}
