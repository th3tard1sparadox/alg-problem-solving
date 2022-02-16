/**
 * @file unionfind.cpp
 * @author Annie Wång (annwa858@student.liu.se)
 * @brief contains a disjoint set class which implements a unionfind algorithm.
 *        The complexity of the find function is O(logn) for both unionizing
 *        two itemsets and checking if two items are in the same set.
 * @date 2022-02-03
 */
#include <iostream>

using namespace std;

/**
 * implementation of disjoint set. Each element n will have an array of parents
 * and rank (which is the "height" of it's position in the parent tree).
 *
 * contains functions for creating new set (used in constructor), function for
 * finding what set an element is a part of, function for comparing if two
 * elements are contained in the same set, and _union which unionizes the sets
 * which two elements are contained in.
 */
class DisjointSet {
    int *rank, *parent, n;

public:
    // constructor initialize n items.
    DisjointSet(int n) {
        rank = new int[n];
        parent = new int[n];
        this->n = n;
        createSet();
    }

    // create n different sets containing 1 item each.
    void createSet() {
        for(int i = 0; i < n; i++) {
            parent[i] = i;
            rank[i] = 1;
        }
    }

    // finds the set containing x. Will shorten the parent path directly to
    // root to shorten future checks.
    int find(int x) {
        int root = x;
        while(root != parent[root]) {
            root = parent[root];
        }
        return root;
    }

    // just prettier to call function in main than to do compare.
    bool same(int x, int y) {
        return find(x) == find(y);
    }

    // unionize set containting x and set containing y.
    void _union(int x, int y) {
        // will automatically shorten the parent path to make it faster.
        int xSet = find(x);
        int ySet = find(y);

        // if they are already in the same set, don't do anything.
        if(xSet == ySet)
            return;

        // put the set with lower rank under the set with higher rank. Increase
        // rank of set with higher rank.
        if(rank[xSet] < rank[ySet]) {
            parent[xSet] = ySet;
            rank[y] += rank[x];
        } else {
            parent[ySet] = xSet;
            rank[x] += rank[y];
        }
    }
};

int main() {
    // C++ slow i/o, optimize it a bit.
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    // read data.
    unsigned int N;
    cin >> N;
    unsigned int Q;
    cin >> Q;

    // create our disjoint set.
    DisjointSet S(N);

    // immediately preform operations on our disjoint set.
    char op;
    unsigned int a;
    unsigned int b;
    for(int i = 0; i < Q; i++) {
        cin >> op;
        cin >> a;
        cin >> b;
        if(op == '=') {
            S._union(a, b);
        } else if (op == '?') {
            if(S.same(a, b)) {
                cout << "yes\n";
            } else {
                cout << "no\n";
            }
        }
    }
}
