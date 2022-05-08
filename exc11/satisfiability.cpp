#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

vector<string> split(const string & s) {
    vector<string> res;
    stringstream ss(s);
    string item;
    while(getline(ss, item, ' ')) {
        if(item != "v") {
            res.push_back(item);
        }
    }
    return res;
}

bool satisfiable(const vector<int> & clause, const vector<int> & assignments) {
    for(auto & l : clause) {
        if(l >= 1) {
            if(assignments[l] == 1) {
                return true;
            } else if (assignments[l] == 0) {
                continue;
            } else {
                return true;
            }
        } else {
            if(assignments[-l] == 1) {
                continue;
            } else if (assignments[-l] == 0) {
                return true;
            } else {
                return true;
            }
        }
    }
    return false;
}

bool all_sat(const vector<vector<int>> & clauses, const vector<int> & assignments) {
    for(auto & c : clauses) {
        if(!satisfiable(c, assignments)) {
            return false;
        }
    }
    return true;
}

bool DPLL(const vector<vector<int>> & clauses, vector<int> & assignments, int index) {
    if(index == assignments.size()) {
        return all_sat(clauses, assignments);
    }

    assignments[index] = 1;
    bool f = true;
    if(!all_sat(clauses, assignments)) {
        f = false;
    } else {
        f = DPLL(clauses, assignments, index + 1);
    }
    assignments[index] = 0;
    bool s = true;
    if(!all_sat(clauses, assignments)) {
        s = false;
    } else {
        s = DPLL(clauses, assignments, index + 1);
    }
    assignments[index] = -1;
    return f || s;
}

int main() {
    int cases;
    cin >> cases;
    for(int i = 0; i < cases; i++) {
        int n, m;
        cin >> n >> m;
        cin.ignore();
        vector<int> literals(n + 1, -1);
        vector<vector<int>> clauses;
        for(int j = 0; j < m; j++) {
            vector<int> clause;
            string input;
            getline(cin, input);
            vector<string> items = split(input);
            for(auto & item : items) {
                if(item != "v") {
                    bool neg = false;
                    if(item[0] == '~') {
                        neg = true;
                        item.erase(0, 2);
                    } else {
                        item.erase(0, 1);
                    }
                    int index = stoi(item);
                    if(neg) {
                        clause.push_back(-index);
                    } else {
                        clause.push_back(index);
                    }
                }
            }
            clauses.push_back(clause);
        }
        if(DPLL(clauses, literals, 0)) {
            cout << "satisfiable\n";
        } else {
            cout << "unsatisfiable\n";
        }
    }
}
