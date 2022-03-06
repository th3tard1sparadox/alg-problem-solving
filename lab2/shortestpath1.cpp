#include <iostream>
#include <vector>

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
};

int main() {
    int nodes;
    cin >> nodes;
    return 0;
}
