/**
 * @file shortestpath2.cpp
 * @author Annie Wång (annwa858@student.liu.se)
 * @brief an implementation of dijkstra's algorithm modified from shortestpath1
 *        which calculates the path rom a single startingpoint to all other
 *        nodes where paths are only passable during certain timeslots. The
 *        complexity is O(elogv) where v are the verticies and e are the edges.
 * @date 2022-03-11
 */
#include <iostream>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

/**
 * Graph class saves the edges in a vector where vertex x has all its neighbors
 * listed in the edges vector under edges[x].
 *
 * findPaths implements the modified dijkstra's.
 */
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

    // save all information in the edges.
    void addEdge(int x, int y, int t0, int P, int d) {
        edges[x].push_back({t0, P, d, y});
    }

    // returns a vector with the length from start and the parent vertex saved
    // at the index of the goal node you're looking for.
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
                            // calculating the next open timeslot.
                            int nextt = 0;
                            if(-curr[0] < n[0]) { // next timeslot is t0.
                                nextt = n[0];
                            } else if(n[1] == 0) { // P is 0 and t0 has passed.
                                continue;
                            } else if((-curr[0] - n[0]) % n[1] == 0) { // special case where we are on the next timeslot.
                                nextt = -curr[0];
                            } else { // math with integer division to round.
                                nextt = n[1] * (((-curr[0] - n[0])/n[1]) + 1) + n[0];
                            }

                            // we our time to have traversed the edge will be
                            // the next open timeslot + the time it takes to traverse.
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
        int t0;
        int P;
        int d;
        for(int i = 0; i < edges; i++) {
            cin >> x >> y >> t0 >> P >> d;
            g.addEdge(x, y, t0, P, d);
        }

        int goal;
        vector<pair<long, int>> paths = g.findPaths(start);
        // output works same as shortestpath1.
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
