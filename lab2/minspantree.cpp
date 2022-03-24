/**
 * @file minspantree.cpp
 * @author Annie Wång (annwa858@student.liu.se)
 * @brief implements kruskal's algotithm for finding minimum spanning trees
 *        with unionfind as cycle detection. Complexity is O(eloge) where e is
 *        edges. This it it's complexity as we first sort the vectors, and then
 *        we just iterate through them. Sorting is done in O(nlogn) time and
 *        iterating is O(n), so them combined are O(nlogn + n) = O(nlogn).
 * @date 2022-03-11
 */
#include <iostream>
#include <math.h>
#include <vector>
#include <bits/stdc++.h>
#include <iomanip>

using namespace std;

/**
 * simple union find.
 */
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

/**
 * Graph implements kruskal's. saves edges in vector.
 */
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

    // returns the edges which are used in the minimum spanning tree.
    pair<long, vector<vector<int>>> kruskals() {
        pair<long, vector<vector<int>>> sol;
        vector<vector<int>> minTree;

        sort(edges.begin(), edges.end());
        CyFinder s((int)v);
        long cost = 0;
        for(auto & edge : edges) {
            int w = edge[0];
            int x = edge[1];
            int y = edge[2];

            // if they have the same parent they are in a cycle.
            if(s.find(x) != s.find(y)) {
                minTree.push_back({x, y});
                s.unite(x, y);
                cost += w;
            }
        }
        // add cost and tree to the solution.
        sol.first = cost;
        sol.second = minTree;
        return sol;
    }
};

/**
 * not very smart way to check of the tree is validly spanning, aka if the
 * graph was disjoint.
 */
bool validSpTree(Graph g, int v, vector<vector<int>> tree) {
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
    // io optimizations just in case cause (not really necessary with this
    // problem).
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    // read io.
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

        // quick check just to see that we actually can make a spanning tree.
        if(edges >= verticies - 1) {
            pair<long, vector<vector<int>>> solution = g.kruskals();
            vector<vector<int>> minTree = solution.second;
            long cost = solution.first;
            // output.
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
