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

    vector<vector<int>> getNeigh(int x) {
        vector<vector<int>> neigh;
        for(auto & e : edges) {
            if(e[1] == x) {
                neigh.push_back({e[0], e[2]});
            }
        }
        return neigh;
    }

    long findPath(int start, int goal, int nodes) {
        priority_queue<vector<int>> queue;
        bool visited[nodes];

        for(int i = 0; i < nodes; i++) {
            visited[i] = false;
        }

        queue.push({0, start});

        vector<int> curr;
        while(queue.size() > 0) {
            curr = queue.top();
            queue.pop();
            if(!visited[curr[1]]) {
                visited[curr[1]] = true;

                if(curr[1] == goal) {
                    return -curr[0];
                }

                vector<vector<int>> neighs = getNeigh(curr[1]);
                for(auto & n : neighs) {
                    if(!visited[n[1]]) {
                        queue.push({curr[0] - n[0], n[1]});
                    }
                }
            }
        }
        return -1;
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
        for(int i = 0; i < queries; i++) {
            cin >> goal;
            long dist = g.findPath(start, goal, nodes);
            if(dist >= 0) {
                cout << dist << "\n";
            } else {
                cout << "Impossible\n";
            }
        }

        cin >> nodes >> edges >> queries >> start;
    }
    return 0;
}
