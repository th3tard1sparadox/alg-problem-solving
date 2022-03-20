#include <iostream>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

class Graph {
    vector<vector<pair<double, int>>> edges;
    int v;

public:
    Graph(int v) {
        this->v = v;
        for(int i = 0; i < v; i++) {
            edges.push_back({{-1, -1}});
        }
    }

    void addEdge(int x, int y, double w) {
        edges[x].push_back({w, y});
    }

    vector<pair<double, int>> findPaths(int start) {
        vector<pair<double, int>> path(v);
        bool visited[v];
        for(int i = 0; i < v; i++) {
            visited[i] = false;
            path[i] = {-1, -1};
        }

        priority_queue<pair<double, int>> queue;
        queue.push({0, start});
        path[start] = {0, start};

        pair<double, int> curr;
        while(queue.size() > 0) {
            curr = queue.top();
            queue.pop();
            if(!visited[curr.second]) {
                visited[curr.second] = true;

                vector<pair<double, int>> neighs = edges[curr.second];
                for(auto & n : neighs) {
                    if(n.first != -1) {
                        if(!visited[n.second]) {
                            if(path[n.second].first > -curr.first + n.first || path[n.second].first == -1) {
                                path[n.second] = {-curr.first + n.first, curr.second};
                            }
                            queue.push({curr.first - n.first, n.second});
                        }
                    }
                }
            }
        }
        return path;
    }
};

int main() {
    cout << fixed;
    cout << setprecision(2);
    int nodes;
    cin >> nodes;
    while(nodes != 0) {
        map<int, int> edgeMap;
        Graph g(nodes * 2);
        int count = 0;
        for(int i = 0; i < nodes; i++) {
            int start;
            int end;
            int h;
            cin >> start >> end >> h;

            double cost = ((double)start+(double)end)*(double)h/100.0;

            if(!edgeMap.count(start)) {
                edgeMap[start] = count;
                count++;
            }
            if(!edgeMap.count(end)) {
                edgeMap[end] = count;
                count++;
            }
            start = edgeMap[start];
            end = edgeMap[end];

            g.addEdge(start, end, cost);
            g.addEdge(end, start, cost);
        }

        int start;
        int end;
        cin >> start >> end;
        start = edgeMap[start];
        end = edgeMap[end];

        vector<pair<double, int>> paths = g.findPaths(start);
        cout << paths[end].first << "\n";
        cin >> nodes;
    }

    return 0;
}
