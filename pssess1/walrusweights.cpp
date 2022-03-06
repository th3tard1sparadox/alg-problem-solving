#include <iostream>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

int sack(int capacity, vector<vector<int>> &objects) {
    // this is our solution matrix (don't mind the name "array").
    vector<vector<int>> sol_array(objects.size() + 1, vector<int>(capacity + 1));

    // iterate through the matrix.
    for(int i = 0; i < objects.size() + 1; i++) {
        for(int j = 0; j < capacity + 1; j++) {
            // we cannot put any items in if we don't have any or capacity is 0.
            if(i == 0 || j == 0) {
                sol_array[i][j] = {0};
            } else if(objects[i - 1][1] <= j) { // if we can fit this item into the current weight, try to put it in.
                // If it is more valueable to put this item into the knapsack (and possibly discard some objects), put it in, else don't.
                if(objects[i - 1][0] + sol_array[i - 1][j - objects[i - 1][1]] > sol_array[i - 1][j]) {
                    sol_array[i][j] = objects[i - 1][0] + sol_array[i - 1][j - objects[i - 1][1]];
                } else {
                    sol_array[i][j] = sol_array[i - 1][j];
                }
            } else { // if we cannot fit anything new into our knapsack.
                sol_array[i][j] = sol_array[i - 1][j];
            }
        }
    }

    return sol_array[objects.size()][capacity];
}

int closest(int plates[], int size, int max) {
    int optimal = 0;
    int optimal_dist = max;
    vector<int> sums = {0};

    for(int i = 0; i < size; i++) {
        int weight = plates[i];
        vector<int> newSums;
        for(int j = 0; j < sums.size(); j++) {
            int sum = sums[j];


            newSums.push_back(sum);
            int newSum = sum + weight;
            int dist = abs(max - newSum);
            if(newSum <= max) {
                newSums.push_back(newSum);
                if(dist < optimal_dist) {
                    optimal = newSum;
                    optimal_dist = dist;
                }
            } else if(dist < optimal_dist || (dist == optimal_dist && newSum > optimal)) {
                optimal = newSum;
                optimal_dist = dist;
                newSums.push_back(newSum);
            }
        }
        sums = newSums;
    }
    return optimal;
}

int closestSum(int plates[], int size, int max) {
    set<int> s;

    int firstSum = plates[0];
    s.insert(plates[0]);

    int minDist = abs(plates[0] - max);

    int sum = firstSum;
    for(int i = 1; i < size; i++) {
        firstSum += plates[i];

        auto it = s.lower_bound(firstSum - max);
        if(it == s.begin()) {
            int diff = *it;
            if(abs((firstSum - diff) - max) < minDist) {
                minDist = abs((firstSum - diff) - max);
                sum = firstSum - diff;
            }
        } else if(it != s.end()) {
            int diff = *it;

            if(abs((firstSum - diff) - max) < minDist) {
                minDist = abs((firstSum - diff) - max);
                sum = firstSum - diff;
            }

            it--;
            diff = *it;

            if(abs((firstSum - diff) - max) < minDist) {
                minDist = abs((firstSum - diff) - max);
                sum = firstSum - diff;
            }
        } else {
            if(abs(firstSum - max) < minDist) {
                minDist = abs(firstSum - max);
                sum = firstSum;
            }
        }
        s.insert(firstSum);
    }

    return sum;
}

int main() {
    // read the input.
    int capacity = 1000;
    int plates;
    cin >> plates;
    int w;
    vector<vector<int>> objects;
    for(int i = 0; i < plates; i++) {
        cin >> w;
        objects.push_back({w, w, i});
    }
    int sol = sack(capacity, objects);
    if(sol < capacity) {
        int high = abs(2*capacity - sol);
        if(sack(high, objects) == high) {
            sol = high;
        }
    }
    cout << sol;
}
