#include <iostream>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

class Graph {
    vector<vector<vector<int>>> edges;
    int v;

public:
    Graph(int v) {
        this->v = v;
        for(int i = 0; i < v; i++) {
            edges.push_back({{-1}});
        }
    }

    void addEdge(int x, int y, int w) {
        edges[x].push_back({w, y});
    }

    vector<pair<long, int>> findPaths(int start) {
        vector<pair<long, int>> path(v);
        bool visited[v];
        for(int i = 0; i < v; i++) {
            visited[i] = false;
            path[i] = {-1, -1};
        }

        priority_queue<vector<int>> queue;
        queue.push({0, start});
        path[start] = {0, start};

        vector<int> curr;
        while(queue.size() > 0) {
            curr = queue.top();
            queue.pop();
            if(!visited[curr[1]]) {
                visited[curr[1]] = true;

                vector<vector<int>> neighs = edges[curr[1]];
                for(auto & n : neighs) {
                    if(n[0] != -1) {
                        if(!visited[n[1]]) {
                            if(path[n[1]].first > -curr[0] + n[0] || path[n[1]].first == -1) {
                                path[n[1]] = {-curr[0] + n[0], curr[1]};
                            }
                            queue.push({curr[0] - n[0], n[1]});
                        }
                    }
                }
            }
        }
        return path;
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
        vector<pair<long, int>> paths = g.findPaths(start);
        for(int i = 0; i < queries; i++) {
            cin >> goal;
            long dist = paths[goal].first;
            if(dist != -1) {
                cout << dist << "\n";
            } else {
                cout << "Impossible\n";
            }
        }

        cin >> nodes >> edges >> queries >> start;
    }
    return 0;
}
