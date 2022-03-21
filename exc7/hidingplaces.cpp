#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <bits/stdc++.h>

using namespace std;

vector<pair<int, int>> neigh(pair<int, int> pos) {
    vector<pair<int, int>> n;
    if(pos.second - 2 >= 0) {
        if(pos.first - 1 >= 0) {
            n.push_back({pos.first - 1, pos.second - 2});
        }
        if(pos.first + 1 < 8) {
            n.push_back({pos.first + 1, pos.second - 2});
        }
    }
    if(pos.second + 2 < 8) {
        if(pos.first - 1 >= 0) {
            n.push_back({pos.first - 1, pos.second + 2});
        }
        if(pos.first + 1 < 8) {
            n.push_back({pos.first + 1, pos.second + 2});
        }
    }
    if(pos.first - 2 >= 0) {
        if(pos.second - 1 >= 0) {
            n.push_back({pos.first - 2, pos.second - 1});
        }
        if(pos.second + 1 < 8) {
            n.push_back({pos.first - 2, pos.second + 1});
        }
    }
    if(pos.first + 2 < 8) {
        if(pos.second - 1 >= 0) {
            n.push_back({pos.first + 2, pos.second - 1});
        }
        if(pos.second + 1 < 8) {
            n.push_back({pos.first + 2, pos.second + 1});
        }
    }

    return n;
}

vector<vector<int>> bfs(pair<int, int> start) {
    vector<vector<int>> grid(8, vector<int>(8, -1));
    grid[start.second][start.first] = 0;

    queue<pair<int, int>> queue;
    queue.push(start);

    pair<int, int> curr;
    while(!queue.empty()) {
        curr = queue.front();
        queue.pop();

        vector<pair<int, int>> neighbors = neigh(curr);
        for(auto & n : neighbors) {
            if(grid[n.second][n.first] == -1) {
                grid[n.second][n.first] = grid[curr.second][curr.first] + 1;
                queue.push(n);
            }
        }
    }

    return grid;
}

pair<int, vector<string>> findLongest(vector<vector<int>> grid) {
    map<int, char> xVal = {{0, 'a'}, {1, 'b'}, {2, 'c'}, {3, 'd'},
                           {4, 'e'}, {5, 'f'}, {6, 'g'}, {7, 'h'}};
    int longest = 0;
    vector<string> lPos;
    for(int y = 7; y >= 0; y--) {
        for(int x = 0; x < 8; x++) {
            if(grid[y][x] > longest) {
                longest = grid[y][x];
                string pos = "";
                pos += xVal[x];
                pos += ('0' + y + 1);
                lPos = {pos};
            } else if(grid[y][x] == longest) {
                string pos = "";
                pos += xVal[x];
                pos += ('0' + y + 1);
                lPos.push_back(pos);
            }
        }
    }

    return {longest, lPos};
}

int main() {
    map<char, int> xVal = {{'a', 1}, {'b', 2}, {'c', 3}, {'d', 4},
                           {'e', 5}, {'f', 6}, {'g', 7}, {'h', 8}};
    int cases;
    cin >> cases;
    vector<vector<int>> grid;
    pair<int, vector<string>> hP;
    string start;
    for(int i = 0; i < cases; i++) {
        cin >> start;
        grid = bfs({xVal[start[0]] - 1, start[1] - '0' - 1});
        hP = findLongest(grid);
        cout << hP.first;
        for(auto & p : hP.second) {
            cout << " " << p;
        }
        cout << "\n";
    }
}
