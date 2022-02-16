/**
 * @file fenwick.cpp
 * @author Annie Wång (annwa858@student.liu.se)
 * @brief implementation of a fenwick tree where all time complexities are 
 *        O(logn).
 * @date 2022-02-16
 */
#include <iostream>

using namespace std;

/**
 * @brief Get the sum of the tree from a certain index.
 * 
 * @param tree the fenwick tree.
 * @param i from what index do we wanna sum.
 * @return long the sum.
 */
long getSum(long tree[], long i) {
    long sum = 0;

    while(i > 0) {
        sum += tree[i];
        // get next index (index to the parent).
        i -= i & (-i);
    }

    return sum;
}

/**
 * @brief add some value to a certain index of the tree.
 * 
 * @param tree the fenwick tree.
 * @param n the length of the tree.
 * @param i what index we want to update.
 * @param val what we want to add.
 */
void updateTree(long tree[], long n, long i, long val) {
    i = i + 1;

    while(i <= n) {
        tree[i] += val;
        // get next index (index to the parent).
        i += i & (-i);
    }
}

/**
 * @brief Create a Fenwick Tree.
 * 
 * @param n size of the tree.
 * @return long* the tree.
 */
long *createFenwickTree(long n) {
    long *tree = new long[n + 1];
    for(long i = 1; i < n; i++) {
        // everything starts with value 10.
        tree[i] = 0;
    }

    return tree;
}

int main() {
    // io still slow.
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    // read start of data.
    long n;
    long q;
    cin >> n;
    cin >> q;

    // create our tree.
    long *fenwickTree = createFenwickTree(n);

    // read rest of data and handle different operations.
    char op;
    long val1;
    long val2;
    for(long i = 0; i < q; i++) {
        cin >> op;
        cin >> val1;
        if(op == '+') {
            cin >> val2;
            updateTree(fenwickTree, n, val1, val2);
        } else if(op == '?') {
            cout << getSum(fenwickTree, val1) << "\n";
        }
    }

    return 0;
}