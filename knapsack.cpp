/**
 * @file knapsack.cpp
 * @author Annie Wång (annwa858@student.liu.se)
 * @brief solution to the well known knapsack-problem, solution is 
 *        O(n*capacity) and uses DP.
 * @date 2022-01-31
 */

#include <iostream>
#include <vector>

using namespace std;

/**
 * main solving part builds a matrix where the "y"-axis represents having the 
 * objects at that index and the "x"-axis increasing the weight capacity 1 step
 * at a time. In each index of this matrix we now calculate what our maximal
 * value at that capacity with given objects using the value from the index 
 * before.
 * 
 * @param capacity the capacity of the knapsack.
 * @param objects vector of vectors (could have used pairs here) containing the
 *                objects value (index 0) and weight (index 1).
 * @return vector<int> vector of the indexes of the chosen items.
 */
vector<int> sack(int capacity, vector<vector<int>> &objects) {
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

    // our answer.
    vector<int> ans;
    // the maximal value possible.
    int value = sol_array[objects.size()][capacity];
    // the capacity of the knapsack.
    int capLeft = capacity;
    // iterate through the items to find which were used to get maximal value.
    for(int i = objects.size(); i > 0 && value > 0; i--) {
        // if the maximal value is still reached at current index, the item might not have been used.
        if(value == sol_array[i - 1][capLeft]) {
            continue;
        }
        // we only get here after the value changed, meaning the last index i was used in solution.
        ans.push_back(i - 1);
        // update the maximal value as we picked something out of the knapsack.
        value = value - objects[i - 1][0];
        // update what capacity we are looking for in the knapsack.
        capLeft = capLeft - objects[i - 1][1];
    }

    return ans;
}

int main() {
    // read the input.
    int capacity;
    int cases;
    while(cin >> capacity >> cases) {
        vector<vector<int>> objects;
        for(int i = 0; i < cases; i++) {
            int value;
            cin >> value;
            int weight;
            cin >> weight;
            objects.push_back({value, weight, i});
        }
        // run the solution.
        vector<int> sol = sack(capacity, objects);
        // output the answer.
        cout << sol.size() << endl;
        for(int i = 0; i < sol.size(); i++) {
            cout << sol[i] << " ";
        }
        cout << endl;
    }

}