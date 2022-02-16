/**
 * @file intervalcover.cpp
 * @author Annie Wång (annwa858@student.liu.se)
 * @brief solution to the quite well known interval cover problem, where you
 *        have to cover one interval with one or more other intervals. This
 *        solution is O(nlogn) because of the sort that has to be made, but
 *        would be O(n) it the data was already sorted.
 * @date 2022-01-31
 */

#include <iostream>
#include <vector>
#include <limits>
#include <bits/stdc++.h>

using namespace std;

/**
 * main solving part is a greedy solution where you always choose the interval 
 * that coveres the furthest while still covering all that is uncovered to the
 * left.
 * 
 * @param interval the interval that needs to be covered.
 * @param intervals a vector of all the potential intervals for covering the 
 *                  main interval.
 * @return vector<int> vector of the indexes of the intervals used to cover the
 *                     main interval.
 */
vector<int> coverage(vector<double> &interval, vector<vector<double>> &intervals) {
    // where we will put our solution.
    vector<int> sol;

    // if we don't have any intervals to use we exit with empty vector.
    if(intervals.size() == 0)
        return {};

    // sort the intervals first on starting point and them on ending point.
    sort(intervals.begin(), intervals.end());
    // add a buffer interval.
    intervals.push_back({numeric_limits<double>::max(), numeric_limits<double>::lowest(), -1.0f});

    // set the longest interval found to really small and it's index to -1.
    double longest = numeric_limits<double>::lowest();
    int longestInd = -1;
    // iterate through all intervals.
    for(int i = 0; i < intervals.size(); i++) {
        // if the startingpoint of our interval covers the left most uncovered
        // point, it isn't our buffer and it is the longest we've found so far
        // set it to the longest.
        if(intervals[i][0] <= interval[0] && intervals[i][2] >= 0) {
            if(intervals[i][1] > longest) {
                longest = intervals[i][1];
                longestInd = intervals[i][2];
            }
        } else { // we now know we've found the longest that cover the first point.
            // if it is the first interval in the vector, no intervals can cover the left most point.
            if(i == 0)
                return {};

            // add the longest found interval to the solution and shrink the 
            // interval that needs to be covered.
            interval[0] = longest;
            sol.push_back((int)longestInd);

            // if the interval is is fully covered, we break the loop.
            if(longest >= interval[1]) {
                break;
            }
            
            // if the interval we're looking at now cover from where the last 
            // longest left of, it is the new longest element. If not there
            // will be an uncovered hole which is why we exit with an empty
            // vector.
            if(intervals[i][0] <= interval[0]) {
                longest = intervals[i][1];
                longestInd = intervals[i][2];
            } else {
                return {};
            }
        }
    }
    // if interval is still not fully covered we exit with an empty vector.
    if(longest < interval[1]) {
        return {};
    }
    // valid solution found.
    return sol;
}

int main() {
    // read input.
    double ints;
    double inte;
    vector<double> interval;
    int nrIntervals;
    while(cin >> ints >> inte) {
        interval = {ints, inte};
        cin >> nrIntervals;
        vector<vector<double>> intervals;
        for(int i = 0; i < nrIntervals; i++) {
            double lower;
            double upper;
            cin >> lower >> upper;
            intervals.push_back({lower, upper, (double)i});
        }
        // run solution.
        vector<int> sol = coverage(interval, intervals);
        // output the answer.
        if(sol.size() == 0) {
            cout << "impossible\n";
        } else {
            cout << sol.size() << endl;
            for(double x : sol) {
                cout << (int)x << " ";
            }
            cout << endl;
        }
    }
}