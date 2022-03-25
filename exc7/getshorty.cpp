#include <iostream>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

int main() {
    cout << fixed;
    cout << setprecision(4);

    int intersections;
    int corridors;
    cin >> intersections >> corridors;
    while(intersections + corridors != 0) {
        int x;
        int y;
        long double f;
        vector<vector<pair<long double, int>>> edges(intersections);
        for(int e = 0; e < corridors; e++) {
            cin >> x >> y >> f;
            edges[x].push_back({f, y});
            edges[y].push_back({f, x});
        }

        vector<long double> sizeAt(intersections, 0.0);
        vector<bool> visited(intersections, false);

        priority_queue<pair<long double, int>> queue;
        queue.push({1.0, 0});
        sizeAt[0] = 1.0;

        while(queue.size() > 0) {
            int currV = queue.top().second;
            long double currF = queue.top().first;
            queue.pop();
            if(!visited[currV]) {
                visited[currV] = true;

                vector<pair<long double, int>> neighs = edges[currV];
                for(auto & n : neighs) {
                    if(!visited[n.second]) {
                        if(sizeAt[n.second] < currF * n.first) {
                            sizeAt[n.second] = currF * n.first;
                        }
                        queue.push({currF * n.first, n.second});
                    }
                }
            }
        }
        cout << sizeAt[intersections - 1] << "\n";
        cin >> intersections >> corridors;
    }
    return 0;
}
