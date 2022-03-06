#include <iostream>
#include <utility>
#include <queue>
#include <vector>

using namespace std;

vector<pair<int, int>> neigh(pair<int, int> &pos, vector<vector<char>> board, int w, int h) {
    vector<pair<int, int>> neighs;
    pair<int, int> n;
    if(pos.first > 0) { // left
        if(board[pos.second][pos.first - 1] == 'T')
            return {};
        if(board[pos.second][pos.first - 1] != '#') {
            n.first = pos.first - 1;
            n.second = pos.second;
            neighs.push_back(n);
        }            
    }
    if(pos.first < w - 1) { // right
        if(board[pos.second][pos.first + 1] == 'T')
            return {};
        if(board[pos.second][pos.first + 1] != '#') {
            n.first = pos.first + 1;
            n.second = pos.second;
            neighs.push_back(n);
        }            

    }
    if(pos.second > 0) { // up
        if(board[pos.second - 1][pos.first] == 'T')
            return {};
        if(board[pos.second - 1][pos.first] != '#') {
            n.first = pos.first;
            n.second = pos.second - 1;
            neighs.push_back(n);
        }            

    }
    if(pos.second < h - 1) { // down
        if(board[pos.second + 1][pos.first] == 'T')
            return {};
        if(board[pos.second + 1][pos.first] != '#') {
            n.first = pos.first;
            n.second = pos.second + 1;
            neighs.push_back(n);
        }            

    }

    return neighs;
}

int bfs(pair<int, int> &pos, vector<vector<char>> board, int w, int h) {
    int gold = 0;

    queue<pair<int, int>> q;
    vector<pair<int, int>> seen;
    q.push(pos);
    pair<int, int> curr;
    vector<pair<int, int>> n;
    while(!q.empty()) {
        curr = q.front();
        q.pop();
        bool beenSeen = false;
        for(auto & i : seen) {
            if(curr == i) {
                beenSeen = true;
                break;
            }
        }
        if(beenSeen)
            continue;

        seen.push_back(curr);
        if(board[curr.second][curr.first] == 'G') {
            gold++;
        }
        n = neigh(curr, board, w, h);
        for(auto & p : n) {
            q.push(p);
        }
    }

    return gold;
}

int main() {
    int w;
    int h;
    cin >> w >> h;

    vector<vector<char>> board;
    pair <int, int> player;
    char el;
    for(int y = 0; y < h; y++) {
        vector<char> row;
        for(int x = 0; x < w; x++) {
            cin >> el;
            row.push_back(el);
            if(el == 'P') {
                player.first = x;
                player.second = y;
            }
        }
        board.push_back(row);
    }

    cout << bfs(player, board, w, h) << endl;

    return 0;
}