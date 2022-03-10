#include <iostream>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

class Graph {
    vector<vector<int>> edges;
    int v;

public:
    Graph(int v) {
        this->v = v;
    }

    void addEdge(int x, int y, int w) {
        edges.push_back({w, x, y});
    }

    vector<long> findPaths(int start) {
        vector<long> dist(v);

        for(int i = 0; i < v; i++) {
            dist[i] = LONG_MAX;
        }
        dist[start] = 0;

        for(int i = 0; i <= v; i++) {
            for(auto & e : edges) {
                if(dist[e[1]] != LONG_MAX && dist[e[1]] + e[0] < dist[e[2]]) {
                    dist[e[2]] = dist[e[1]] + e[0];
                }
            }
        }

        for(int i = 0; i <= v; i++) {
            for(auto & e : edges) {
                if(dist[e[1]] != LONG_MAX && (dist[e[1]] == LONG_MIN || dist[e[1]] + e[0] < dist[e[2]])) {
                    dist[e[2]] = LONG_MIN;
                }
            }
        }

        return dist;
    }
};

int main() {
    int nodes;
    int edges;
    int queries;
    int start;
    cin >> nodes >> edges >> queries >> start;
    while(!(nodes == 0 && edges == 0 && queries == 0 && start == 0)) {
        Graph g(nodes);
        int x;
        int y;
        int w;
        for(int i = 0; i < edges; i++) {
            cin >> x >> y >> w;
            g.addEdge(x, y, w);
        }

        int goal;
        vector<long> paths = g.findPaths(start);
        for(int i = 0; i < queries; i++) {
            cin >> goal;
            long dist = paths[goal];
            if(dist == LONG_MAX) {
                cout << "Impossible\n";
            } else if(dist == LONG_MIN) {
                cout << "-Infinity\n";
            } else {
                cout << dist << "\n";
            }
        }

        cin >> nodes >> edges >> queries >> start;
    }
    return 0;
}
