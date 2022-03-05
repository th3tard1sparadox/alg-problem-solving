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

    vector<vector<long>> kruskals() {
        vector<vector<long>> minTree;
        sort(edges.begin(), edges.end());
        CyFinder s((int)v);
        long cost = 0;
        for(auto & edge : edges) {
            int w = edge[0];
            int x = edge[1];
            int y = edge[2];

            if(s.find(x) != s.find(y)) {
                minTree.push_back({x, y});
                s.unite(x, y);
                cost += w;
            }
        }
        minTree.insert(minTree.begin(), {cost});
        return minTree;
    }
};

bool validSpTree(Graph g, int v, vector<vector<long>> tree) {
    bool cov[v];
    for(int i = 0; i < v; i++) {
        cov[i] = false;
    }

    for(auto & e : tree) {
        cov[e[0]] = true;
        cov[e[1]] = true;
    }

    for(int i = 0; i < v; i++) {
        if(!cov[i]) {
            return false;
        }
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int verticies;
    int edges;
    cin >> verticies;
    cin >> edges;
    while(!(verticies == 0 && edges == 0)) {
        Graph g(verticies);
        for(int j = 0; j < edges; j++) {
            int x;
            int y;
            int w;
            cin >> x;
            cin >> y;
            cin >> w;
            if(x < y) {
                g.addEdge(x, y, w);
            } else {
                g.addEdge(y, x, w);
            }
        }

        if(edges >= verticies - 1) {
            vector<vector<long>> minTree = g.kruskals();
            long cost = minTree.front()[0];
            minTree.erase(minTree.begin());
            if(validSpTree(g, verticies, minTree)) {
                cout << cost << "\n";
                sort(minTree.begin(), minTree.end());
                for(auto & edge : minTree) {
                    cout << edge[0] << " " << edge[1] << "\n";
                }
            } else {
                cout << "Impossible" << "\n";
            }
        } else {
            cout << "Impossible" << "\n";
        }

        cin >> verticies;
        cin >> edges;
    }
}
