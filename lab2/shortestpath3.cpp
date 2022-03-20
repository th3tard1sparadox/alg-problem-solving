/**
 * @file shortestpath3.cpp
 * @author Annie Wång (annwa858@student.liu.se)
 * @brief an implementation of bellman-ford's algorithm which calculates the
 *        shorthest path from a single startingpoint to all other nodes in a
 *        graph containing negative weights. Complexity is O(ev) where e are
 *        edges and v verticies.
 * @date 2022-03-11
 */
#include <iostream>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

/**
 * Graph class saves edges in a vector.
 *
 * findPath implements bellman-ford's.
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

    // returns a vector containing the length from start to each node and their
    // parent in the path.
    vector<pair<long, int>> findPaths(int start) {
        vector<pair<long, int>> dist(v);

        // initialize all distances and parents.
        for(int i = 0; i < v; i++) {
            dist[i] = {LONG_MAX, -1};
        }
        dist[start] = {0, start};

        // relax the distances v (verticies) times.
        for(int i = 0; i <= v; i++) {
            for(auto & e : edges) {
                if(dist[e[1]].first != LONG_MAX && dist[e[1]].first + e[0] < dist[e[2]].first) {
                    dist[e[2]] = {dist[e[1]].first + e[0], e[1]};
                }
            }
        }

        // set all paths containing or adjecent to a negative cycle to
        // impossible.
        for(int i = 0; i <= v; i++) {
            for(auto & e : edges) {
                if(dist[e[1]].first != LONG_MAX && (dist[e[1]].first == LONG_MIN || dist[e[1]].first + e[0] < dist[e[2]].first)) {
                    dist[e[2]] = {LONG_MIN, e[1]};
                }
            }
        }

        return dist;
    }
};

int main() {
    // read io.
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

        // find paths and output.
        int goal;
        vector<pair<long, int>> paths = g.findPaths(start);
        for(int i = 0; i < queries; i++) {
            cin >> goal;
            long dist = paths[goal].first;
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
