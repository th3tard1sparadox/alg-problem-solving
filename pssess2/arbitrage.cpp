#include <iostream>
#include <vector>
#include <string>
#include <bits/stdc++.h>
#include <map>

using namespace std;

class Graph {
    vector<vector<double>> edges;
    int v;

public:
    Graph(int v) {
        this->v = v;
    }

    void addEdge(int x, int y, double w) {
        edges.push_back({w, (double)x, (double)y});
    }

    vector<double> findPaths(int start) {
        vector<double> dist(v);

        for(int i = 0; i < v; i++) {
            dist[i] = (double)LONG_MAX;
        }
        dist[start] = 0;

        for(int i = 0; i <= v; i++) {
            for(auto & e : edges) {
                if(dist[(int)e[1]] != (double)LONG_MAX && dist[(int)e[1]] + e[0] < dist[(int)e[2]]) {
                    dist[(int)e[2]] += dist[(int)e[1]] + e[0];
                }
            }
        }

        for(int i = 0; i <= v; i++) {
            for(auto & e : edges) {
                if(dist[(int)e[1]] != (double)LONG_MAX && (dist[(int)e[1]] == (double)LONG_MIN || dist[(int)e[1]] + e[0] < dist[(int)e[2]])) {
                    dist[(int)e[2]] = (double)LONG_MIN;
                }
            }
        }

        return dist;
    }
};

int main() {
    int currAm;
    cin >> currAm;
    while(currAm != 0) {
        map<string, int> curr;
        for(int i = 0; i < currAm; i++) {
            string c;
            cin >> c;
            curr[c] = i;
        }

        int ratesAm;
        cin >> ratesAm;
        Graph g(ratesAm);
        for(int i = 0; i < ratesAm; i++) {
            string from;
            string to;
            string rateSt;
            cin >> from >> to >> rateSt;

            int pos = rateSt.find(":");
            string rFrS = rateSt.substr(0, pos);
            string rToS = rateSt.substr(pos + 1, rateSt.find(":", pos + 1) - pos - 1);
            double rateFr = (double)stoi(rFrS);
            double rateTo = (double)stoi(rToS);

            // x y w
            cout << rateTo/rateFr << endl;
            g.addEdge(curr[from], curr[to], rateTo/rateFr);
        }

        vector<double> paths = g.findPaths(0);
        bool arb = false;
        for(auto & d : paths) {
            if(d == (double)LONG_MIN) {
                arb = true;
                break;
            }
        }
        if(arb) {
            cout << "Arbitrage\n";
        } else {
            cout << "Ok\n";
        }

        cin >> currAm;
    }
}
