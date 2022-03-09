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

    void addEdge(int x, int y, int t0, int P, int d) {
        edges[x].push_back({t0, P, d, y});
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
                        if(!visited[n[3]]) {
                            int nextt = 0;
                            if(-curr[0] < n[0]) {
                                nextt = n[0];
                            } else if(n[1] == 0) {
                                continue;
                            } else if((-curr[0] - n[0]) % n[1] == 0){
                                nextt = -curr[0];
                            } else {
                                nextt = n[1] * (((-curr[0] - n[0])/n[1]) + 1) + n[0];
                            }

                            if(path[n[3]].first > nextt + n[2] || path[n[3]].first == -1) {
                                path[n[3]] = {nextt + n[2], curr[1]};
                            }
                            queue.push({-nextt - n[2], n[3]});
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
        int t0;
        int P;
        int d;
        for(int i = 0; i < edges; i++) {
            cin >> x >> y >> t0 >> P >> d;
            g.addEdge(x, y, t0, P, d);
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
