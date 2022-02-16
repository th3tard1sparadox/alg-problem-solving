#include <iostream>
#include <queue>
#include <vector>

using namespace std;

vector<long> choppy(long nrVer, vector<long> vers) {
    vector<long> sol;
    priority_queue<long, vector<long>, greater<long>> pq;
    vector<long> data;
    vector<long> nbrs(nrVer + 1);
    for(auto & i : vers) {
        nbrs[i]++;
    }
    for(int i = 1; i < nrVer + 1; i++) {
        if(nbrs[i] == 0) {
            pq.push(i);
        }
    }

    for(auto & v : vers) {
        if(pq.empty()) {
            return {};
        }
        sol.push_back(pq.top());
        pq.pop();
        nbrs[v]--;
        if(nbrs[v] == 0) {
            pq.push(v);
        }
    }

    return sol;
}

int main() {
    long nrVer;
    cin >> nrVer;
    vector<long> vertices;
    for(long i = 0; i < nrVer; i++) {
        long v;
        cin >> v;
        vertices.push_back(v);
    }
    vector<long> sol = choppy(nrVer, vertices);
    if(sol.size() != nrVer) {
        cout << "Error";
    } else {
        for(auto & v : sol) {
            cout << v << endl;
        }
    }
    return 0;
}
